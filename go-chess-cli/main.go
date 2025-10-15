package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"

	"github.com/notnil/chess"
)

func printBoard(game *chess.Game) {
	position := game.Position()
	// Print ranks 8 to 1
	for rank := 7; rank >= 0; rank-- {
		fmt.Printf("%d ", rank+1)
		for file := 0; file < 8; file++ {
			sq := chess.Square(rank*8 + file)
			piece := position.Board().Piece(sq)
			ch := "."
			if piece != chess.NoPiece {
				ch = piece.String()
			}
			fmt.Printf("%2s ", ch)
		}
		fmt.Println()
	}
	fmt.Println("   a  b  c  d  e  f  g  h")
}

func readMoveInput(reader *bufio.Reader) (string, error) {
	fmt.Print("Enter move in SAN or UCI (e.g., e2e4 or Nf3): ")
	text, err := reader.ReadString('\n')
	if err != nil {
		return "", err
	}
	return strings.TrimSpace(text), nil
}

func main() {
	game := chess.NewGame()
	reader := bufio.NewReader(os.Stdin)

	for game.Outcome() == chess.NoOutcome {
		fmt.Println()
		printBoard(game)
		fmt.Printf("Turn: %s\n", game.Position().Turn())

		mvStr, err := readMoveInput(reader)
		if err != nil {
			fmt.Printf("Error reading input: %v\n", err)
			continue
		}
		if mvStr == "quit" || mvStr == "exit" {
			fmt.Println("Exiting game.")
			return
		}

    // Try UCI first (e2e4), then long/short SAN (e2e4, Nf3, e4, etc.)
    var move *chess.Move
    var decErr error

    if len(mvStr) == 4 || len(mvStr) == 5 { // basic UCI like e2e4 or e7e8q
        move, decErr = chess.UCINotation{}.Decode(game.Position(), mvStr)
    }
    if move == nil || decErr != nil {
        move, decErr = chess.LongAlgebraicNotation{}.Decode(game.Position(), mvStr)
    }
    if move == nil || decErr != nil {
        move, decErr = chess.AlgebraicNotation{}.Decode(game.Position(), mvStr)
    }

    if decErr != nil || move == nil {
        fmt.Println("Invalid move format. Try again.")
        continue
    }

    if err := game.Move(move); err != nil {
			fmt.Printf("Illegal move: %v\n", err)
			continue
		}
	}

	printBoard(game)
	switch game.Outcome() {
	case chess.WhiteWon:
		fmt.Println("Checkmate: White wins!")
	case chess.BlackWon:
		fmt.Println("Checkmate: Black wins!")
	case chess.Draw:
		fmt.Printf("Draw: %s\n", game.Method())
	}
}
