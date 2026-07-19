// Problem:
// Given an n x m grid of characters and a target word, determine whether the word exists in the grid by connecting adjacent cells horizontally or vertically.
// The same cell cannot be used more than once while forming the word.

#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// BACKTRACKING APPROACH
//
// Idea:
// Start from every cell containing the first character of the word and explore all four possible directions recursively.
// Mark visited cells temporarily to avoid reusing the same cell in the current path and restore them while backtracking.
//
// Time Complexity: O(n * m * 4^L) where L is the length of the word
// Space Complexity: O(L) due to recursion stack
// ============================================================================

bool recursiveWordSearch(int idx, int M, int N, vector<vector<char>> &board, string word, int row, int col)
{
    // Current cell does not match the required character or is already visited.
    if (board[row][col] == '#' || board[row][col] != word[idx])
        return false;

    // Entire word has been matched successfully.
    if (idx == word.size() - 1)
        return true;

    // Mark the current cell as visited.
    char temp = board[row][col];
    board[row][col] = '#';

    bool ans = false;

    // Explore the left direction.
    if (col - 1 >= 0)
        ans |= recursiveWordSearch(idx + 1, M, N, board, word, row, col - 1);

    // Explore the right direction.
    if (col + 1 < M)
        ans |= recursiveWordSearch(idx + 1, M, N, board, word, row, col + 1);

    // Explore the top direction.
    if (row - 1 >= 0)
        ans |= recursiveWordSearch(idx + 1, M, N, board, word, row - 1, col);

    // Explore the bottom direction.
    if (row + 1 < N)
        ans |= recursiveWordSearch(idx + 1, M, N, board, word, row + 1, col);

    // Restore the original character for other search paths.
    board[row][col] = temp;

    return ans;
}

bool exist(vector<vector<char>> &board, string word)
{
    int N = board.size(), M = board[0].size();

    // Try starting the search from every possible cell.
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (board[i][j] == word[0])
            {
                if (recursiveWordSearch(0, M, N, board, word, i, j))
                    return true;
            }
        }
    }

    return false;
}

int main()
{
    vector<vector<char>> board = {
        {'A', 'A', 'A', 'A', 'A', 'A'},
        {'A', 'B', 'C', 'D', 'E', 'A'},
        {'A', 'B', 'C', 'D', 'F', 'A'},
        {'A', 'B', 'C', 'D', 'G', 'A'},
        {'A', 'B', 'C', 'D', 'H', 'A'},
        {'A', 'A', 'A', 'A', 'A', 'A'}};

    string word = "AAAABCDHGFEDCBA";

    if (exist(board, word))
        cout << "Word found!" << endl;
    else
        cout << "Word not found!" << endl;

    return 0;
}