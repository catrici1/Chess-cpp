# Chess-cpp

A complete command-line chess engine written in C++ from scratch, where you play White against a Minimax + Alpha-Beta pruning AI playing Black. It also includes a standalone, mobile-friendly web port that can be played directly in your browser.

**Play online:** [https://chess-cpp.netlify.app/](https://chess-cpp.netlify.app/)

> The chess engine (`chess.cpp`) is my own work. The standalone browser port was generated with AI based directly on my C++ engine logic.

## Files

| File | What it is |
|------|------------|
| `chess.cpp` | The complete C++ game: 8x8 board representation, full move validation, check/checkmate/stalemate detection, evaluation tables, and Minimax AI with alpha-beta pruning |

## Features

- **Complete Chess Rules:** Full move validation for pawns, knights, bishops, rooks, queens, and kings, including kingside/queenside castling (`O.O` / `O.O.O`), en passant captures, and pawn promotion.
- **Legal Move Enforcement:** Automatically blocks moves that leave or place your own king in check, and detects check, checkmate, and stalemate.
- **Minimax AI with Alpha-Beta Pruning:** Searches ahead (`SEARCH_DEPTH = 3`, 4 plies total) using alpha-beta pruning to cut unpromising branches and pick the optimal move, breaking ties randomly.
- **Positional & Material Evaluation:** Evaluates board states using standard material weights (`Q=900`, `R=500`, `B=300`, `N=300`, `P=100`) combined with mirrored 8x8 piece-square tables so pieces favor active squares and king safety.
- **Cross-Platform Play:** Runs natively in any terminal via `g++` or directly in the browser on desktop and mobile without any backend server.

## How to Play

### Option 1: Play in Browser (Desktop & Mobile)

Open **[https://chess-cpp.netlify.app/](https://chess-cpp.netlify.app/)** — no installation or local server required.

- Tap or click one of your pieces to see highlighted legal moves, then tap the destination square.
- Castling: select your king, then tap `g1` or `c1`[cite: 2].
- Pawn promotion: select your desired piece from the pop-up prompt when reaching the 8th rank[cite: 2].

### Option 2: Run in Terminal (C++)

Requires `g++` with C++17 support[cite: 2]. Compile with `-O2` for optimal search speed:

```bash
g++ -std=c++17 -O2 chess.cpp -o chess
./chess
