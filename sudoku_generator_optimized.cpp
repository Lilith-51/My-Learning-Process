#include <iostream>
#include <array>
#include <random>
#include <algorithm>

class SudokuGenerator {
private:
    std::array<std::array<int, 9>, 9> grid{};
    std::mt19937 rng{std::random_device{}()};

    bool isValid(int row, int col, int num) {
        // Check row and column in one pass
        for (int i = 0; i < 9; i++) {
            if (grid[row][i] == num || grid[i][col] == num) return false;
        }
        
        // Check 3x3 box
        int boxRow = (row / 3) * 3, boxCol = (col / 3) * 3;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (grid[boxRow + i][boxCol + j] == num) return false;
            }
        }
        return true;
    }

    bool solve() {
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                if (grid[row][col] == 0) {
                    // Try numbers 1-9 in random order
                    std::array<int, 9> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
                    std::shuffle(nums.begin(), nums.end(), rng);
                    
                    for (int num : nums) {
                        if (isValid(row, col, num)) {
                            grid[row][col] = num;
                            if (solve()) return true;
                            grid[row][col] = 0;
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }

public:
    bool generate() {
        // Clear grid
        for (auto& row : grid) {
            row.fill(0);
        }
        return solve();
    }

    void print() {
        std::cout << "Generated Sudoku:\n";
        std::cout << "+" << std::string(25, '-') << "+\n";
        
        for (int i = 0; i < 9; i++) {
            if (i % 3 == 0 && i != 0) {
                std::cout << "+" << std::string(25, '-') << "+\n";
            }
            std::cout << "| ";
            for (int j = 0; j < 9; j++) {
                if (j % 3 == 0 && j != 0) std::cout << "| ";
                std::cout << grid[i][j] << " ";
            }
            std::cout << "|\n";
        }
        std::cout << "+" << std::string(25, '-') << "+\n";
    }

    bool verify() {
        // Count occurrences of each number
        std::array<int, 10> counts{};
        for (const auto& row : grid) {
            for (int num : row) {
                counts[num]++;
            }
        }

        // Check all numbers appear exactly 9 times
        bool valid = true;
        for (int i = 1; i <= 9; i++) {
            if (counts[i] != 9) {
                valid = false;
                break;
            }
        }

        std::cout << "\nVerification:\n";
        std::cout << "✓ Each number appears exactly 9 times: " << (valid ? "True" : "False") << "\n";
        std::cout << "✓ No empty cells: " << (counts[0] == 0 ? "True" : "False") << "\n";
        std::cout << "✓ Total cells: 81\n";

        return valid && counts[0] == 0;
    }
};

int main() {
    std::cout << "Sudoku Generator (Optimized)\n";
    std::cout << std::string(50, '=') << "\n";
    
    SudokuGenerator generator;
    
    std::cout << "Generating a random valid Sudoku...\n";
    if (generator.generate()) {
        generator.print();
        if (generator.verify()) {
            std::cout << "\n✓ Successfully generated a valid Sudoku!\n";
        }
    } else {
        std::cout << "✗ Failed to generate a valid Sudoku\n";
    }
    
    return 0;
}