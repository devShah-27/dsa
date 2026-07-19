// Problem:
// Given an integer n, place n queens on an n x n chessboard such that no two queens attack each other.
// Return all possible unique board configurations where 'Q' represents a queen and '.' represents an empty cell.

#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// BACKTRACKING APPROACH
//
// Idea:
// Place queens row by row and try every possible column in the current row.
// Before placing a queen, check whether the position is attacked by any already placed queen in the same column or diagonal.
// Backtrack after exploring each possible placement.
//
// Time Complexity: O(n! * n) approximately
// Space Complexity: O(n) recursion stack excluding output storage
// ============================================================================

// Checks whether a queen can be safely placed at the given position.
bool isPlacementPossible(vector<string> &board, int row, int col)
{
    int r = row, c = col;

    // Check vertical column attacks from previously placed queens.
    while (r >= 0)
    {
        if (board[r][c] == 'Q')
            return false;

        r--;
    }

    r = row;
    c = col;

    // Check top-left diagonal attacks.
    while (r >= 0 && c >= 0)
    {
        if (board[r][c] == 'Q')
            return false;

        r--;
        c--;
    }

    r = row;
    c = col;

    // Check top-right diagonal attacks.
    while (r >= 0 && c < board[0].size())
    {
        if (board[r][c] == 'Q')
            return false;

        r--;
        c++;
    }

    return true;
}

void recursiveNQueens(int row, int n, vector<string> &board, vector<vector<string>> &result)
{
    // All queens are successfully placed.
    if (row == n)
    {
        result.emplace_back(board);
        return;
    }

    // Try placing the queen in every column of the current row.
    for (int col = 0; col < n; col++)
    {
        if (isPlacementPossible(board, row, col))
        {
            // Place queen.
            board[row][col] = 'Q';

            // Recur for the next row.
            recursiveNQueens(row + 1, n, board, result);

            // Backtrack and remove queen.
            board[row][col] = '.';
        }
    }
}

vector<vector<string>> solveNQueens(int n)
{
    vector<vector<string>> result;

    vector<string> board;

    // Initialize an empty n x n chessboard.
    string str = "";

    for (int i = 0; i < n; i++)
        str += '.';

    for (int i = 0; i < n; i++)
        board.emplace_back(str);

    recursiveNQueens(0, n, board, result);

    return result;
}

int main()
{
    int n = 7;

    vector<vector<string>> solutions = solveNQueens(n);

    for (const auto &sol : solutions)
    {
        for (const auto &row : sol)
        {
            cout << row << endl;
        }

        cout << endl;
    }

    return 0;
}