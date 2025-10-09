import random
import copy

class SudokuGenerator:
    def __init__(self):
        self.grid = [[0 for _ in range(9)] for _ in range(9)]
        self.numbers = list(range(1, 10))
    
    def is_valid_placement(self, row, col, num):
        """Check if placing num at (row, col) is valid"""
        # Check row
        if num in self.grid[row]:
            return False
        
        # Check column
        for i in range(9):
            if self.grid[i][col] == num:
                return False
        
        # Check 3x3 box
        start_row = (row // 3) * 3
        start_col = (col // 3) * 3
        for i in range(start_row, start_row + 3):
            for j in range(start_col, start_col + 3):
                if self.grid[i][j] == num:
                    return False
        
        return True
    
    def is_valid_sudoku(self):
        """Check if the entire grid is a valid Sudoku"""
        # Check each row
        for row in self.grid:
            if len(set(row)) != 9 or 0 in row:
                return False
        
        # Check each column
        for col in range(9):
            column = [self.grid[row][col] for row in range(9)]
            if len(set(column)) != 9 or 0 in column:
                return False
        
        # Check each 3x3 box
        for box_row in range(3):
            for box_col in range(3):
                box = []
                for i in range(3):
                    for j in range(3):
                        box.append(self.grid[box_row * 3 + i][box_col * 3 + j])
                if len(set(box)) != 9 or 0 in box:
                    return False
        
        return True
    
    def count_numbers(self):
        """Count occurrences of each number (1-9) in the grid"""
        counts = {i: 0 for i in range(1, 10)}
        for row in self.grid:
            for num in row:
                if num != 0:
                    counts[num] += 1
        return counts
    
    def generate_sudoku(self):
        """Generate a valid filled Sudoku using backtracking with randomization"""
        # Shuffle numbers for randomness
        random.shuffle(self.numbers)
        
        def solve():
            for row in range(9):
                for col in range(9):
                    if self.grid[row][col] == 0:
                        # Try each number in random order
                        random.shuffle(self.numbers)
                        for num in self.numbers:
                            if self.is_valid_placement(row, col, num):
                                self.grid[row][col] = num
                                if solve():
                                    return True
                                self.grid[row][col] = 0
                        return False
            return True
        
        # Clear the grid first
        self.grid = [[0 for _ in range(9)] for _ in range(9)]
        
        # Generate the Sudoku
        if solve():
            return True
        else:
            return False
    
    def print_grid(self):
        """Print the Sudoku grid in a nice format"""
        print("Generated Sudoku:")
        print("+" + "-" * 25 + "+")
        for i, row in enumerate(self.grid):
            if i % 3 == 0 and i != 0:
                print("+" + "-" * 25 + "+")
            row_str = "| "
            for j, num in enumerate(row):
                if j % 3 == 0 and j != 0:
                    row_str += "| "
                row_str += str(num) + " "
            row_str += "|"
            print(row_str)
        print("+" + "-" * 25 + "+")
    
    def verify_sudoku(self):
        """Verify that the generated Sudoku meets all requirements"""
        print("\nVerification:")
        
        # Check if it's a valid Sudoku
        is_valid = self.is_valid_sudoku()
        print(f"✓ Valid Sudoku structure: {is_valid}")
        
        # Check number counts
        counts = self.count_numbers()
        all_nine = all(count == 9 for count in counts.values())
        print(f"✓ Each number appears exactly 9 times: {all_nine}")
        
        # Check no zeros
        no_zeros = all(all(cell != 0 for cell in row) for row in self.grid)
        print(f"✓ No empty cells (zeros): {no_zeros}")
        
        # Check total cells
        total_cells = sum(len(row) for row in self.grid)
        print(f"✓ Total cells: {total_cells} (should be 81)")
        
        return is_valid and all_nine and no_zeros and total_cells == 81

def main():
    """Main function to generate and display a Sudoku"""
    print("Sudoku Generator")
    print("=" * 50)
    
    generator = SudokuGenerator()
    
    # Generate a new Sudoku
    print("Generating a random valid Sudoku...")
    success = generator.generate_sudoku()
    
    if success:
        generator.print_grid()
        generator.verify_sudoku()
        
        print(f"\n✓ Successfully generated a valid Sudoku!")
    else:
        print("✗ Failed to generate a valid Sudoku")

if __name__ == "__main__":
    main()