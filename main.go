package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

// Piece types
type PieceType int

const (
	Empty PieceType = iota
	Pawn
	Rook
	Knight
	Bishop
	Queen
	King
)

// Piece colors
type Color int

const (
	NoColor Color = iota
	White
	Black
)

// Piece represents a chess piece
type Piece struct {
	Type  PieceType
	Color Color
}

// Position represents a position on the board
type Position struct {
	Row int
	Col int
}

// Move represents a chess move
type Move struct {
	From Position
	To   Position
}

// ChessBoard represents the chess board
type ChessBoard struct {
	Board [8][8]Piece
}

// Game represents the chess game state
type Game struct {
	Board       ChessBoard
	CurrentTurn Color
	GameOver    bool
	Winner      Color
}

// NewGame creates a new chess game
func NewGame() *Game {
	game := &Game{
		Board:       ChessBoard{},
		CurrentTurn: White,
		GameOver:    false,
		Winner:      NoColor,
	}
	game.initializeBoard()
	return game
}

// initializeBoard sets up the initial chess position
func (g *Game) initializeBoard() {
	// Initialize empty board
	for i := 0; i < 8; i++ {
		for j := 0; j < 8; j++ {
			g.Board.Board[i][j] = Piece{Empty, NoColor}
		}
	}

	// Place white pieces
	g.Board.Board[7][0] = Piece{Rook, White}
	g.Board.Board[7][1] = Piece{Knight, White}
	g.Board.Board[7][2] = Piece{Bishop, White}
	g.Board.Board[7][3] = Piece{Queen, White}
	g.Board.Board[7][4] = Piece{King, White}
	g.Board.Board[7][5] = Piece{Bishop, White}
	g.Board.Board[7][6] = Piece{Knight, White}
	g.Board.Board[7][7] = Piece{Rook, White}
	for i := 0; i < 8; i++ {
		g.Board.Board[6][i] = Piece{Pawn, White}
	}

	// Place black pieces
	g.Board.Board[0][0] = Piece{Rook, Black}
	g.Board.Board[0][1] = Piece{Knight, Black}
	g.Board.Board[0][2] = Piece{Bishop, Black}
	g.Board.Board[0][3] = Piece{Queen, Black}
	g.Board.Board[0][4] = Piece{King, Black}
	g.Board.Board[0][5] = Piece{Bishop, Black}
	g.Board.Board[0][6] = Piece{Knight, Black}
	g.Board.Board[0][7] = Piece{Rook, Black}
	for i := 0; i < 8; i++ {
		g.Board.Board[1][i] = Piece{Pawn, Black}
	}
}

// getPieceSymbol returns the Unicode symbol for a piece
func getPieceSymbol(piece Piece) string {
	if piece.Type == Empty {
		return "·"
	}

	symbols := map[PieceType]map[Color]string{
		Pawn:   {White: "♙", Black: "♟"},
		Rook:   {White: "♖", Black: "♜"},
		Knight: {White: "♘", Black: "♞"},
		Bishop: {White: "♗", Black: "♝"},
		Queen:  {White: "♕", Black: "♛"},
		King:   {White: "♔", Black: "♚"},
	}

	return symbols[piece.Type][piece.Color]
}

// printBoard displays the current board state
func (g *Game) printBoard() {
	fmt.Println("\n    a   b   c   d   e   f   g   h")
	fmt.Println("  ┌───┬───┬───┬───┬───┬───┬───┬───┐")
	
	for i := 0; i < 8; i++ {
		fmt.Printf("%d │", 8-i)
		for j := 0; j < 8; j++ {
			piece := g.Board.Board[i][j]
			symbol := getPieceSymbol(piece)
			fmt.Printf(" %s │", symbol)
		}
		fmt.Printf(" %d\n", 8-i)
		if i < 7 {
			fmt.Println("  ├───┼───┼───┼───┼───┼───┼───┼───┤")
		}
	}
	
	fmt.Println("  └───┴───┴───┴───┴───┴───┴───┴───┘")
	fmt.Println("    a   b   c   d   e   f   g   h")
}

// parsePosition converts algebraic notation to board coordinates
func parsePosition(notation string) (Position, error) {
	if len(notation) != 2 {
		return Position{}, fmt.Errorf("invalid position format")
	}
	
	col := int(notation[0] - 'a')
	row := int(notation[1] - '1')
	
	if col < 0 || col > 7 || row < 0 || row > 7 {
		return Position{}, fmt.Errorf("position out of bounds")
	}
	
	// Convert to board coordinates (0-based, row 0 is top)
	return Position{Row: 7 - row, Col: col}, nil
}

// isValidMove checks if a move is valid
func (g *Game) isValidMove(move Move) bool {
	from := move.From
	to := move.To
	
	// Check bounds
	if from.Row < 0 || from.Row > 7 || from.Col < 0 || from.Col > 7 ||
		to.Row < 0 || to.Row > 7 || to.Col < 0 || to.Col > 7 {
		return false
	}
	
	piece := g.Board.Board[from.Row][from.Col]
	
	// Check if there's a piece at the source
	if piece.Type == Empty {
		return false
	}
	
	// Check if it's the current player's piece
	if piece.Color != g.CurrentTurn {
		return false
	}
	
	// Check if destination has own piece
	destPiece := g.Board.Board[to.Row][to.Col]
	if destPiece.Type != Empty && destPiece.Color == piece.Color {
		return false
	}
	
	// Check piece-specific move validity
	return g.isValidPieceMove(piece, from, to)
}

// isValidPieceMove checks if a specific piece can move from one position to another
func (g *Game) isValidPieceMove(piece Piece, from, to Position) bool {
	rowDiff := to.Row - from.Row
	colDiff := to.Col - from.Col
	
	switch piece.Type {
	case Pawn:
		return g.isValidPawnMove(piece, from, to, rowDiff, colDiff)
	case Rook:
		return g.isValidRookMove(from, to, rowDiff, colDiff)
	case Knight:
		return g.isValidKnightMove(rowDiff, colDiff)
	case Bishop:
		return g.isValidBishopMove(from, to, rowDiff, colDiff)
	case Queen:
		return g.isValidQueenMove(from, to, rowDiff, colDiff)
	case King:
		return g.isValidKingMove(rowDiff, colDiff)
	}
	
	return false
}

// isValidPawnMove checks if a pawn move is valid
func (g *Game) isValidPawnMove(piece Piece, from, to Position, rowDiff, colDiff int) bool {
	direction := 1
	if piece.Color == White {
		direction = -1
	}
	
	// Forward move
	if colDiff == 0 && g.Board.Board[to.Row][to.Col].Type == Empty {
		// One square forward
		if rowDiff == direction {
			return true
		}
		// Two squares forward from starting position
		if rowDiff == 2*direction && from.Row == (7-6*direction) {
			return true
		}
	}
	
	// Diagonal capture
	if abs(colDiff) == 1 && rowDiff == direction {
		destPiece := g.Board.Board[to.Row][to.Col]
		return destPiece.Type != Empty && destPiece.Color != piece.Color
	}
	
	return false
}

// isValidRookMove checks if a rook move is valid
func (g *Game) isValidRookMove(from, to Position, rowDiff, colDiff int) bool {
	// Must move in a straight line
	if rowDiff != 0 && colDiff != 0 {
		return false
	}
	
	// Check if path is clear
	return g.isPathClear(from, to)
}

// isValidKnightMove checks if a knight move is valid
func (g *Game) isValidKnightMove(rowDiff, colDiff int) bool {
	// Knight moves in L-shape
	return (abs(rowDiff) == 2 && abs(colDiff) == 1) || (abs(rowDiff) == 1 && abs(colDiff) == 2)
}

// isValidBishopMove checks if a bishop move is valid
func (g *Game) isValidBishopMove(from, to Position, rowDiff, colDiff int) bool {
	// Must move diagonally
	if abs(rowDiff) != abs(colDiff) {
		return false
	}
	
	// Check if path is clear
	return g.isPathClear(from, to)
}

// isValidQueenMove checks if a queen move is valid
func (g *Game) isValidQueenMove(from, to Position, rowDiff, colDiff int) bool {
	// Queen moves like rook or bishop
	return g.isValidRookMove(from, to, rowDiff, colDiff) || g.isValidBishopMove(from, to, rowDiff, colDiff)
}

// isValidKingMove checks if a king move is valid
func (g *Game) isValidKingMove(rowDiff, colDiff int) bool {
	// King moves one square in any direction
	return abs(rowDiff) <= 1 && abs(colDiff) <= 1
}

// isPathClear checks if the path between two positions is clear
func (g *Game) isPathClear(from, to Position) bool {
	rowStep := 0
	colStep := 0
	
	if to.Row != from.Row {
		rowStep = (to.Row - from.Row) / abs(to.Row - from.Row)
	}
	if to.Col != from.Col {
		colStep = (to.Col - from.Col) / abs(to.Col - from.Col)
	}
	
	row := from.Row + rowStep
	col := from.Col + colStep
	
	for row != to.Row || col != to.Col {
		if g.Board.Board[row][col].Type != Empty {
			return false
		}
		row += rowStep
		col += colStep
	}
	
	return true
}

// makeMove executes a move on the board
func (g *Game) makeMove(move Move) bool {
	if !g.isValidMove(move) {
		return false
	}
	
	// Move the piece
	piece := g.Board.Board[move.From.Row][move.From.Col]
	g.Board.Board[move.To.Row][move.To.Col] = piece
	g.Board.Board[move.From.Row][move.From.Col] = Piece{Empty, NoColor}
	
	// Switch turns
	if g.CurrentTurn == White {
		g.CurrentTurn = Black
	} else {
		g.CurrentTurn = White
	}
	
	// Check for game over conditions
	g.checkGameOver()
	
	return true
}

// checkGameOver checks if the game is over
func (g *Game) checkGameOver() {
	// Simple implementation - check if any king is missing
	whiteKing := false
	blackKing := false
	
	for i := 0; i < 8; i++ {
		for j := 0; j < 8; j++ {
			piece := g.Board.Board[i][j]
			if piece.Type == King {
				if piece.Color == White {
					whiteKing = true
				} else {
					blackKing = true
				}
			}
		}
	}
	
	if !whiteKing {
		g.GameOver = true
		g.Winner = Black
	} else if !blackKing {
		g.GameOver = true
		g.Winner = White
	}
}

// getCurrentPlayerName returns the name of the current player
func (g *Game) getCurrentPlayerName() string {
	if g.CurrentTurn == White {
		return "White"
	}
	return "Black"
}

// abs returns the absolute value of an integer
func abs(x int) int {
	if x < 0 {
		return -x
	}
	return x
}

// getInput gets user input from the terminal
func getInput(prompt string) string {
	fmt.Print(prompt)
	reader := bufio.NewReader(os.Stdin)
	input, _ := reader.ReadString('\n')
	return strings.TrimSpace(input)
}

func main() {
	fmt.Println("Welcome to Go Chess!")
	fmt.Println("Enter moves in algebraic notation (e.g., 'e2 e4')")
	fmt.Println("Type 'quit' to exit the game")
	fmt.Println()
	
	game := NewGame()
	
	for !game.GameOver {
		game.printBoard()
		fmt.Printf("\n%s's turn. Enter your move: ", game.getCurrentPlayerName())
		
		input := getInput("")
		
		if input == "quit" {
			fmt.Println("Thanks for playing!")
			return
		}
		
		parts := strings.Fields(input)
		if len(parts) != 2 {
			fmt.Println("Invalid input. Please enter move as 'from to' (e.g., 'e2 e4')")
			continue
		}
		
		fromPos, err1 := parsePosition(parts[0])
		toPos, err2 := parsePosition(parts[1])
		
		if err1 != nil || err2 != nil {
			fmt.Println("Invalid position format. Use algebraic notation (e.g., 'e2', 'e4')")
			continue
		}
		
		move := Move{From: fromPos, To: toPos}
		
		if game.makeMove(move) {
			fmt.Println("Move successful!")
		} else {
			fmt.Println("Invalid move. Try again.")
		}
	}
	
	game.printBoard()
	fmt.Printf("\nGame Over! %s wins!\n", game.getCurrentPlayerName())
}