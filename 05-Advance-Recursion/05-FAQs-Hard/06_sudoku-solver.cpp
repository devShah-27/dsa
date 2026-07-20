// Problem:
// Given a partially filled 9x9 Sudoku board, fill the empty cells such that every row, column, and 3x3 sub-grid contains digits 1 through 9 exactly once.
// Empty cells are represented using the '.' character.

#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// BACKTRACKING APPROACH
//
// Idea:
// Find an empty cell and try placing every digit from 1 to 9.
// A digit is placed only if it satisfies Sudoku constraints for its row, column, and 3x3 sub-grid.
// If a choice leads to an invalid state, undo it and try the next digit.
//
// Time Complexity: O(9^(n*n)) in the worst case
// Space Complexity: O(n*n) due to recursion stack and board storage
// ============================================================================

// Checks whether placing a digit at the given position follows Sudoku rules.
bool isSafeToPlace(char digit, int row, int col, vector<vector<char>> &board)
{
    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;

    for (int i = 0; i < 9; i++)
    {
        // Check current column.
        if (board[i][col] == digit)
            return false;

        // Check current row.
        if (board[row][i] == digit)
            return false;

        // Check corresponding 3x3 sub-grid.
        if (board[startRow + (i / 3)][startCol + (i % 3)] == digit)
            return false;
    }

    return true;
}

bool recursiveSolveSudoku(vector<vector<char>> &board)
{
    int N = 9;

    // Find the next empty cell.
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (board[i][j] == '.')
            {
                // Try placing every possible digit.
                for (char digit = '1'; digit <= '9'; digit++)
                {
                    if (isSafeToPlace(digit, i, j, board))
                    {
                        // Place the digit.
                        board[i][j] = digit;

                        // Continue solving the remaining board.
                        if (recursiveSolveSudoku(board))
                            return true;

                        // Backtrack if this placement does not lead to a solution.
                        board[i][j] = '.';
                    }
                }

                // No digit can be placed in this cell.
                return false;
            }
        }
    }

    // All cells are filled successfully.
    return true;
}

void solveSudoku(vector<vector<char>> &board)
{
    recursiveSolveSudoku(board);
}

int main()
{
    vector<vector<char>> board = {
        {'7', '3', '6', '.', '.', '.', '.', '.', '.'},
        {'.', '9', '.', '.', '.', '.', '2', '.', '5'},
        {'5', '2', '.', '6', '.', '.', '.', '7', '3'},
        {'1', '.', '.', '7', '.', '.', '9', '.', '6'},
        {'.', '.', '.', '.', '5', '2', '7', '.', '8'},
        {'9', '7', '8', '4', '1', '6', '5', '3', '.'},
        {'.', '.', '.', '.', '.', '.', '4', '8', '.'},
        {'.', '8', '7', '1', '6', '.', '.', '.', '.'},
        {'2', '.', '.', '.', '.', '3', '6', '.', '7'}};

    solveSudoku(board);

    for (const auto &row : board)
    {
        for (char c : row)
        {
            cout << c << " ";
        }

        cout << endl;
    }

    return 0;
}