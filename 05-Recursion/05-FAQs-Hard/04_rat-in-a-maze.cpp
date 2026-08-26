// Problem:
// Given an n x n grid, find all possible paths for a rat to move from the top-left cell (0,0) to the bottom-right cell (n-1,n-1).
// The rat can move in four directions: Up, Down, Left, and Right.
// Cells with value 0 are blocked and cells with value 1 are traversable.

#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// BACKTRACKING APPROACH
//
// Idea:
// Explore all possible directions from the current cell recursively.
// Mark visited cells as blocked temporarily to avoid cycles and restore them after exploring all paths from that cell.
// Store the path whenever the destination cell is reached.
//
// Time Complexity: O(4^(n*n))
// Space Complexity: O(n*n) due to recursion stack and visited tracking
// ============================================================================

void recursiveSolveMaze(int row, int col, int n, vector<vector<int>> &grid, vector<string> &result, string mazePathStr)
{
    // Stop if the current cell is blocked or already visited.
    if (grid[row][col] == 0)
        return;

    // Destination reached, store the current path.
    if (row == n - 1 && col == n - 1)
    {
        result.emplace_back(mazePathStr);
        return;
    }

    // Mark current cell as visited.
    grid[row][col] = 0;

    // Move Down.
    if (row < n - 1)
        recursiveSolveMaze(row + 1, col, n, grid, result, mazePathStr + 'D');

    // Move Right.
    if (col < n - 1)
        recursiveSolveMaze(row, col + 1, n, grid, result, mazePathStr + 'R');

    // Move Up.
    if (row > 0)
        recursiveSolveMaze(row - 1, col, n, grid, result, mazePathStr + 'U');

    // Move Left.
    if (col > 0)
        recursiveSolveMaze(row, col - 1, n, grid, result, mazePathStr + 'L');

    // Backtrack: restore the cell for other possible paths.
    grid[row][col] = 1;
}

vector<string> findPath(vector<vector<int>> &grid)
{
    int n = grid.size();

    // If starting or destination cell is blocked, no path exists.
    if (grid[0][0] == 0 || grid[n - 1][n - 1] == 0)
        return {};

    vector<string> result;

    recursiveSolveMaze(0, 0, n, grid, result, "");

    return result;
}

int main()
{
    vector<vector<int>> grid = {
        // {1, 0, 0, 0, 0},
        // {1, 1, 0, 1, 1},
        // {0, 1, 0, 0, 1},
        // {0, 1, 1, 1, 1},
        // {0, 0, 0, 1, 1}

        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 1}};

    vector<string> paths = findPath(grid);

    if (paths.size() == 0)
    {
        cout << "No path possible" << endl;
    }
    else
    {
        for (const string &path : paths)
        {
            cout << path << endl;
        }
    }

    return 0;
}