<<<<<<< HEAD
# Chess-cpp
Personal attempt at coding a chess game, including a bot.
Bot is coming, I have yet to finish the game itself. En passant is the last rule that needs to be added.
=======
# Chess GUI

Files: `chess.cpp` (yours, untouched), `server.py`, `index.html`. Needs `g++` and Python 3 only.

```
python3 server.py          # compiles chess.cpp if needed, serves on 127.0.0.1:8000
python3 server.py 9000     # optional: different port
```

Open http://127.0.0.1:8000, click a piece, then its destination.
King e1 -> g1 / c1 sends `O.O` / `O.O.O`. Type raw input in the box under the terminal if you prefer.
"New game" restarts the program. Stop the server with Ctrl+C.
>>>>>>> 68e3b75 (added the bot and fixed some bugs)
