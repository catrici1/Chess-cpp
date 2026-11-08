# Chess-cpp

A command-line chess game written in C++, where you play White against a simple bot that plays Black. There is also a small browser GUI that wraps the same program.

> The GUI (`index.html` and `server.py`) was made with Claude. The chess engine (`chess.cpp`) is my own work.

## Files

| File | What it is |
|------|------------|
| `chess.cpp` | The whole game: board, move rules, check/checkmate/stalemate, and the bot |
| `server.py` | Small local web server that runs the compiled game and streams its output to the browser |
| `index.html` | The browser GUI (clickable board) |

## What it does

- Prints the board in the terminal, with White at the bottom.
- Validates moves for every piece: pawn, knight, bishop, rook, queen and king.
- Supports castling, en passant and pawn promotion.
- Rejects any move that leaves your own king in check.
- Detects check, checkmate and stalemate.
- You play White. The bot plays Black.

### How the bot works

The bot is **greedy and looks only one move ahead**. For each legal move it scores:

- the value of the piece it would capture (queen 900, rook 500, bishop/knight 300, pawn 100);
- a small bonus or penalty from piece-square tables (pieces prefer good squares);
- a penalty if the moved piece can be captured on the destination square;
- a big bonus for checkmating the opponent.

It plays the best-scoring move and picks randomly between ties. It does not plan ahead, so it is easy to trick. A Black pawn that reaches the last row is always promoted to a queen.

## Requirements

- **A C++ compiler**: `g++` (any version that supports C++17).
- **Python 3**: only for the GUI. It uses only the standard library, so there is nothing to `pip install`.
- **A modern web browser**: only for the GUI.
- **Linux or macOS** for the GUI. `server.py` uses the Unix-only `pty` module. On Windows, use WSL.

The terminal version needs only `g++`.

## How to play

### Terminal

```
g++ -std=c++17 chess.cpp -o chess
./chess
```

Rules for input:

- Type a move as the start and end square: `e2e4`.
- Use lowercase letters `a-h` and numbers `1-8`.
- Castling: `O.O` for kingside and `O.O.O` for queenside (the letter O, with dots).
- Promotion: when your pawn reaches the last row, type `queen`, `rook`, `knight` or `bishop` (lowercase).
- Illegal moves are rejected and you can try again.
- Press `Ctrl+C` to quit.

### Browser GUI

```
python3 server.py          # compiles chess.cpp if needed, then serves the GUI
python3 server.py 9000     # optional: use a different port
```

Then open http://127.0.0.1:8000.

- Click one of your pieces, then click the square to move to.
- Click the same piece again to deselect it.
- Castling: click the king, then the castling square (`g1` or `c1`).
- Promotion: buttons for the piece appear when needed.
- The box under the terminal accepts raw input such as `e2e4`.
- **New game** restarts the program.
- Stop the server with `Ctrl+C`.

The server only listens on `127.0.0.1`, so the GUI works only on the computer running it, not on other devices.

## Still to do

- [ ] Minimax search, so the bot can think several moves ahead
- [ ] Alpha-beta pruning, to make that search fast
- [ ] Draw rules: threefold repetition, fifty-move rule, insufficient material
- [ ] Let the bot choose its promotion piece instead of always taking a queen
- [ ] A better position evaluation
- [ ] More testing and bug fixes
