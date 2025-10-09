#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>

class SudokuGenerator {
private:
    std::vector<std::vector<int>> grid;
    std::vector<int> numbers;
    std::mt19937 rng;

public:
    SudokuGenerator() : grid(9, std::vector<int>(9, 0)), numbers{1, 2, 3, 4, 5, 6, 7, 8, 9} {
        // Seed the random number generator with current time
        rng.seed(std::chrono::steady_clock::now().time_since_epoch().count());
    }

    bool isValidPlacement(int row, int col, int num) {
        // Check row
        for (int j = 0; j < 9; j++) {
            if (grid[row][j] == num) {
                return false;
            }
        }

        // Check column
        for (int i = 0; i < 9; i++) {
            if (grid[i][col] == num) {
                return false;
            }
        }

        // Check 3x3 box
        int startRow = (row / 3) * 3;
        int startCol = (col / 3) * 3;
        for (int i = startRow; i < startRow + 3; i++) {
            for (int j = startCol; j < startCol + 3; j++) {
                if (grid[i][j] == num) {
                    return false;
                }
            }
        }

        return true;
    }

    bool isValidSudoku() {
        // Check each row
        for (int i = 0; i < 9; i++) {
            std::vector<bool> seen(10, false);
            for (int j = 0; j < 9; j++) {
                if (grid[i][j] == 0 || seen[grid[i][j]]) {
                    return false;
                }
                seen[grid[i][j]] = true;
            }
        }

        // Check each column
        for (int j = 0; j < 9; j++) {
            std::vector<bool> seen(10, false);
            for (int i = 0; i < 9; i++) {
                if (grid[i][j] == 0 || seen[grid[i][j]]) {
                    return false;
                }
                seen[grid[i][j]] = true;
            }
        }

        // Check each 3x3 box
        for (int boxRow = 0; boxRow < 3; boxRow++) {
            for (int boxCol = 0; boxCol < 3; boxCol++) {
                std::vector<bool> seen(10, false);
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        int num = grid[boxRow * 3 + i][boxCol * 3 + j];
                        if (num == 0 || seen[num]) {
                            return false;
                        }
                        seen[num] = true;
                    }
                }
            }
        }

        return true;
    }

    std::vector<int> countNumbers() {
        std::vector<int> counts(10, 0); // indices 0-9, using 1-9
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (grid[i][j] != 0) {
                    counts[grid[i][j]]++;
                }
            }
        }
        return counts;
    }

    bool solve() {
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                if (grid[row][col] == 0) {
                    // Shuffle numbers for randomness
                    std::shuffle(numbers.begin(), numbers.end(), rng);
                    
                    for (int num : numbers) {
                        if (isValidPlacement(row, col, num)) {
                            grid[row][col] = num;
                            if (solve()) {
                                return true;
                            }
                            grid[row][col] = 0;
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }

    bool generateSudoku() {
        // Clear the grid first
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                grid[i][j] = 0;
            }
        }

        // Generate the Sudoku
        return solve();
    }

    void printGrid() {
        std::cout << "Generated Sudoku:\n";
        std::cout << "+" << std::string(25, '-') << "+\n";
        
        for (int i = 0; i < 9; i++) {
            if (i % 3 == 0 && i != 0) {
                std::cout << "+" << std::string(25, '-') << "+\n";
            }
            std::cout << "| ";
            for (int j = 0; j < 9; j++) {
                if (j % 3 == 0 && j != 0) {
                    std::cout << "| ";
                }
                std::cout << grid[i][j] << " ";
            }
            std::cout << "|\n";
        }
        std::cout << "+" << std::string(25, '-') << "+\n";
    }

    bool verifySudoku() {
        std::cout << "\nVerification:\n";

        // Check if it's a valid Sudoku
        bool isValid = isValidSudoku();
        std::cout << "✓ Valid Sudoku structure: " << (isValid ? "True" : "False") << "\n";

        // Check number counts
        std::vector<int> counts = countNumbers();
        bool allNine = true;
        for (int i = 1; i <= 9; i++) {
            if (counts[i] != 9) {
                allNine = false;
                break;
            }
        }
        std::cout << "✓ Each number appears exactly 9 times: " << (allNine ? "True" : "False") << "\n";

        // Check no zeros
        bool noZeros = true;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (grid[i][j] == 0) {
                    noZeros = false;
                    break;
                }
            }
            if (!noZeros) break;
        }
        std::cout << "✓ No empty cells (zeros): " << (noZeros ? "True" : "False") << "\n";

        // Check total cells
        int totalCells = 81;
        std::cout << "✓ Total cells: " << totalCells << " (should be 81)\n";

        return isValid && allNine && noZeros && totalCells == 81;
    }
};

int main() {
    std::cout << "Sudoku Generator\n";
    std::cout << std::string(50, '=') << "\n";

    SudokuGenerator generator;

    // Generate a new Sudoku
    std::cout << "Generating a random valid Sudoku...\n";
    bool success = generator.generateSudoku();

    if (success) {
        generator.printGrid();
        bool verified = generator.verifySudoku();

        if (verified) {
            std::cout << "\n✓ Successfully generated a valid Sudoku!\n";
        } else {
            std::cout << "\n✗ Generated Sudoku failed verification!\n";
        }
    } else {
        std::cout << "✗ Failed to generate a valid Sudoku\n";
    }

    return 0;
}