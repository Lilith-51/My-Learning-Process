# Go Chess App

A two-player chess game written in Go that runs in the terminal.

## Features

- Beautiful Unicode chess piece display
- Two-player gameplay on one computer
- Algebraic notation for moves (e.g., "e2 e4")
- Complete chess rules implementation
- Turn-based gameplay
- Game over detection

## How to Run

1. Make sure you have Go installed on your system
2. Navigate to the project directory
3. Run the application:
   ```bash
   go run main.go
   ```

## How to Play

1. The game starts with White to move
2. Enter moves in algebraic notation: `from to` (e.g., `e2 e4`)
3. The board will update after each valid move
4. Players alternate turns automatically
5. Type `quit` to exit the game

## Move Examples

- `e2 e4` - Move pawn from e2 to e4
- `g1 f3` - Move knight from g1 to f3
- `e1 g1` - Castle kingside (if valid)
- `d7 d8` - Pawn promotion (if reaching the end)

## Chess Pieces

- ♔ ♕ ♖ ♗ ♘ ♙ - White pieces
- ♚ ♛ ♜ ♝ ♞ ♟ - Black pieces

## Game Rules

The application implements standard chess rules including:
- All piece movements (pawn, rook, knight, bishop, queen, king)
- Capture mechanics
- Turn validation
- Basic game over detection (king capture)

Enjoy playing chess!