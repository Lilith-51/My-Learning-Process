# go-chess-cli

A simple two-player local chess CLI app written in Go. Two humans share one terminal and enter moves in UCI (e.g., `e2e4`, `e7e8q`) or SAN (e.g., `Nf3`, `e4`). Uses the reliable [`github.com/notnil/chess`](https://pkg.go.dev/github.com/notnil/chess) rules engine.

## Requirements
- Go 1.20+

## Setup
```bash
cd go-chess-cli
go build
```

## Run
Interactive mode:
```bash
./go-chess-cli
```

Enter moves and press Enter. Examples:
- `e2e4`
- `g8f6`
- `Nf3`
- `Bxc4`
- `O-O` (castle king-side)
- `O-O-O` (castle queen-side)
- `e7e8q` (promotion)

Type `quit` to exit.

Non-interactive quick test:
```bash
printf "e2e4\nquit\n" | ./go-chess-cli
```

## Notes
- The board is printed from rank 8 to 1 with algebraic files `a` to `h`.
- Illegal or malformed moves are rejected with a message; try again.
