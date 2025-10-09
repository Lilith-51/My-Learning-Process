"""
Sudoku deck generator: produce a random, fully filled 9x9 Sudoku board.

- Each row contains the numbers 1..9 exactly once
- Each column contains the numbers 1..9 exactly once
- Each 3x3 subgrid contains the numbers 1..9 exactly once
- Overall, each number 1..9 appears exactly 9 times across the 81 cells

This uses a well-known base-pattern construction for Sudoku solutions and
randomizes it via independent permutations of bands, stacks, and symbols.
This yields a uniformly random board within this construction family, which
is sufficient for generating a valid filled Sudoku deck quickly and reliably.
"""
from typing import List, Optional
import random

BASE: int = 3
SIDE: int = BASE * BASE


def _pattern(row_index: int, column_index: int) -> int:
    """Map (row, column) to an index in the symbol permutation.

    Pattern formula ensures rows, columns, and 3x3 subgrids all cycle
    appropriately to form a valid Sudoku solution base before shuffling.
    """
    return (BASE * (row_index % BASE) + row_index // BASE + column_index) % SIDE


def _shuffled_indices(group_size: int) -> List[int]:
    """Return a shuffled list of indices [0..group_size-1]."""
    return random.sample(range(group_size), k=group_size)


def generate_sudoku(seed: Optional[int] = None) -> List[List[int]]:
    """Generate a random, valid filled 9x9 Sudoku board.

    Args:
        seed: Optional random seed to make output deterministic.

    Returns:
        A 9x9 list of lists, where each inner list is a row of 9 integers in 1..9.
    """
    if seed is not None:
        random.seed(seed)

    # Randomize row and column orders by shuffling bands (groups of 3) and
    # the rows within each band; same for columns.
    row_order: List[int] = [
        band_index * BASE + in_band_index
        for band_index in _shuffled_indices(BASE)
        for in_band_index in _shuffled_indices(BASE)
    ]
    column_order: List[int] = [
        stack_index * BASE + in_stack_index
        for stack_index in _shuffled_indices(BASE)
        for in_stack_index in _shuffled_indices(BASE)
    ]

    # Randomize the mapping from pattern index to digit 1..9
    digits: List[int] = random.sample(list(range(1, SIDE + 1)), k=SIDE)

    board: List[List[int]] = []
    for row_index in row_order:
        row_values: List[int] = []
        for column_index in column_order:
            symbol_index: int = _pattern(row_index, column_index)
            row_values.append(digits[symbol_index])
        board.append(row_values)

    return board


def validate_board(board: List[List[int]]) -> bool:
    """Validate that a board satisfies Sudoku constraints.

    Returns True if valid, False otherwise.
    """
    if len(board) != SIDE or any(len(row) != SIDE for row in board):
        return False

    target_set = set(range(1, SIDE + 1))

    # Check rows
    for row in board:
        if set(row) != target_set:
            return False

    # Check columns
    for column_index in range(SIDE):
        column_values = {board[row_index][column_index] for row_index in range(SIDE)}
        if column_values != target_set:
            return False

    # Check 3x3 subgrids
    for box_row in range(0, SIDE, BASE):
        for box_col in range(0, SIDE, BASE):
            cell_values = set()
            for r in range(box_row, box_row + BASE):
                for c in range(box_col, box_col + BASE):
                    cell_values.add(board[r][c])
            if cell_values != target_set:
                return False

    return True


def print_board(board: List[List[int]]) -> None:
    """Pretty-print the Sudoku board as a 9x9 grid."""
    for row_index, row in enumerate(board):
        row_str_parts: List[str] = []
        for column_index, value in enumerate(row):
            row_str_parts.append(str(value))
            if column_index % BASE == BASE - 1 and column_index != SIDE - 1:
                row_str_parts.append("|")
        print(" ".join(row_str_parts))
        if row_index % BASE == BASE - 1 and row_index != SIDE - 1:
            print("------+-------+------")


def main() -> None:
    board = generate_sudoku()
    assert validate_board(board), "Generated board failed validation"
    print_board(board)


if __name__ == "__main__":
    main()
