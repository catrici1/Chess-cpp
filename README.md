<<<<<<< HEAD
# Chess-cpp
Personal attempt at coding a chess game, including a bot.
The bot is working, I still need to add minimax, Alpha–beta pruning, probably fix some more bugs and add the draw rules.
=======
# Chess GUI made by Claude

Files: `chess.cpp` , `server.py`, `index.html`. Needs `g++` and Python 3 only.

```
python3 server.py          # compiles chess.cpp if needed, serves on 127.0.0.1:8000
python3 server.py 9000     # optional: different port
```

Open http://127.0.0.1:8000, click a piece, then its destination.
Type raw input in the box under the terminal if you prefer.
"New game" restarts the program. Stop the server with Ctrl+C.
