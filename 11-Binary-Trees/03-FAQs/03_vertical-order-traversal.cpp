// Problem:
// Given the root of a binary tree, return its vertical order traversal.
// Nodes are grouped by column from left to right, and nodes in the same column
// are ordered top-to-bottom. If nodes share the same row and column, sort by value.

#include <bits/stdc++.h>
using namespace std;

struct TreeNode
{
    int data;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

/*
========================================================
BFS + MAP APPROACH

Idea:
- Assign coordinates to every node:
  - Root starts at (row = 0, column = 0).
  - Left child moves to (row + 1, column - 1).
  - Right child moves to (row + 1, column + 1).
- Use a nested map to store nodes in sorted order:
  column -> row -> node values.
- Use multiset to automatically sort nodes having the same row and column.

Time Complexity: O(N * log(N)), due to map and multiset operations.
Space Complexity: O(N), for storing nodes and traversal queue.
========================================================
*/

vector<vector<int>> verticalTraversal(TreeNode *root)
{
    if (!root)
        return {};

    vector<vector<int>> res;

    // Stores nodes along with their (column, row) coordinates.
    queue<pair<TreeNode *, pair<int, int>>> q;

    // column -> row -> sorted node values.
    map<int, map<int, multiset<int>>> nodeMap;

    // Root position: column = 0, row = 0.
    q.push({root, {0, 0}});

    while (!q.empty())
    {
        auto currPair = q.front();
        q.pop();

        TreeNode *currNode = currPair.first;

        int val = currNode->data;

        int vertical = currPair.second.first;
        int level = currPair.second.second;

        // Store node value at its corresponding coordinate.
        nodeMap[vertical][level].emplace(val);

        // Left child moves one column left and one level down.
        if (currNode->left)
            q.push({currNode->left, {vertical - 1, level + 1}});

        // Right child moves one column right and one level down.
        if (currNode->right)
            q.push({currNode->right, {vertical + 1, level + 1}});
    }

    // Extract columns from leftmost to rightmost.
    for (auto vertical : nodeMap)
    {
        vector<int> column;

        // Extract nodes from top to bottom within each column.
        for (auto level : vertical.second)
        {
            for (int value : level.second)
            {
                column.push_back(value);
            }
        }

        res.emplace_back(column);
    }

    return res;
}

int main()
{
    TreeNode *root = new TreeNode(1);

    root->left = new TreeNode(2);
    root->right = new TreeNode(3);

    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);

    vector<vector<int>> result = verticalTraversal(root);

    cout << "Vertical Order Traversal: " << endl;

    for (const auto &col : result)
    {
        for (int num : col)
        {
            cout << num << " ";
        }

        cout << endl;
    }

    return 0;
}