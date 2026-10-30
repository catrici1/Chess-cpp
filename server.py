#!/usr/bin/env python3
"""Tiny web GUI server: runs ./chess in a pty and streams its output via SSE."""
import codecs
import json
import os
import pty
import signal
import subprocess
import sys
import threading
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer

HERE = os.path.dirname(os.path.abspath(__file__))
SRC = os.path.join(HERE, "chess.cpp")
BIN = os.path.join(HERE, "chess")

cond = threading.Condition()  # guards `session` and every Session's fields
session = None


class Session:
    def __init__(self):
        self.text = ""    # everything the program printed, in order
        self.done = False
        self.proc = None
        self.fd = None    # pty master


def compile_if_needed():
    """Return None on success, or the compiler error text."""
    if os.path.exists(BIN) and os.path.getmtime(BIN) >= os.path.getmtime(SRC):
        return None
    try:
        r = subprocess.run(["g++", "-std=c++17", SRC, "-o", BIN],
                           capture_output=True, text=True)
    except FileNotFoundError:
        return "g++ not found. Install a C++ compiler."
    if r.returncode == 0:
        return None
    return (r.stdout + r.stderr) or "Compilation failed."


def reader(s):
    dec = codecs.getincrementaldecoder("utf-8")("replace")
    while True:
        try:
            data = os.read(s.fd, 4096)
        except OSError:  # EIO when the child closes the pty
            break
        if not data:
            break
        with cond:
            s.text += dec.decode(data)
            cond.notify_all()
    s.proc.wait()
    with cond:
        s.done = True
        fd, s.fd = s.fd, None
        cond.notify_all()
    os.close(fd)


def stop(s):
    if s and s.proc and s.proc.poll() is None:
        try:
            os.killpg(s.proc.pid, signal.SIGKILL)
        except OSError:
            pass


def start_game():
    global session
    stop(session)
    s = Session()
    err = compile_if_needed()
    if err:
        s.text = "Compilation failed:\n\n" + err
        s.done = True
    else:
        master, slave = pty.openpty()
        s.proc = subprocess.Popen([BIN], stdin=slave, stdout=slave, stderr=slave,
                                  close_fds=True, start_new_session=True)
        os.close(slave)
        s.fd = master
        threading.Thread(target=reader, args=(s,), daemon=True).start()
    with cond:
        session = s
        cond.notify_all()


def send_text(text):
    with cond:
        s = session
        if s is None or s.done or s.fd is None:
            return False
        os.write(s.fd, (text + "\n").encode())
        return True


class Handler(BaseHTTPRequestHandler):
    def log_message(self, *args):
        pass

    def reply(self, code, body=b"", ctype="text/plain"):
        self.send_response(code)
        self.send_header("Content-Type", ctype)
        self.send_header("Content-Length", str(len(body)))
        self.end_headers()
        self.wfile.write(body)

    def do_GET(self):
        if self.path in ("/", "/index.html"):
            with open(os.path.join(HERE, "index.html"), "rb") as f:
                self.reply(200, f.read(), "text/html; charset=utf-8")
        elif self.path == "/events":
            self.events()
        else:
            self.reply(404)

    def do_POST(self):
        n = int(self.headers.get("Content-Length", 0))
        body = self.rfile.read(n).decode("utf-8", "replace")
        if self.path == "/send":
            self.reply(200 if send_text(body) else 409)
        elif self.path == "/new":
            start_game()
            self.reply(200)
        else:
            self.reply(404)

    def events(self):
        self.send_response(200)
        self.send_header("Content-Type", "text/event-stream")
        self.send_header("Cache-Control", "no-cache")
        self.end_headers()
        cur, sent, exited = None, 0, False
        while True:
            out = ""
            with cond:
                if cur is not session:
                    cur, sent, exited = session, 0, False
                    out += "event: reset\ndata: 0\n\n"
                if cur is not None:
                    if len(cur.text) > sent:
                        out += "data: " + json.dumps(cur.text[sent:]) + "\n\n"
                        sent = len(cur.text)
                    if cur.done and not exited and sent == len(cur.text):
                        out += "event: exit\ndata: 0\n\n"
                        exited = True
                if not out and not cond.wait(15):
                    out = ": keepalive\n\n"
            if out:
                try:
                    self.wfile.write(out.encode())
                    self.wfile.flush()
                except OSError:
                    return


if __name__ == "__main__":
    port = int(sys.argv[1]) if len(sys.argv) > 1 else 8000
    start_game()
    srv = ThreadingHTTPServer(("127.0.0.1", port), Handler)
    srv.daemon_threads = True
    print(f"Open http://127.0.0.1:{port}")
    try:
        srv.serve_forever()
    except KeyboardInterrupt:
        stop(session)
