// Problem:
// Given the root of a binary tree, return all root-to-leaf paths.
// A root-to-leaf path contains all nodes from the root node to any leaf node.

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
DEPTH FIRST SEARCH (BACKTRACKING) APPROACH

Idea:
- Use DFS traversal to explore every possible root-to-leaf path.
- Maintain the current path while traversing down the tree.
- Whenever a leaf node is reached, store the current path.
- Backtrack by removing the last node before returning to the previous state.

Time Complexity: O(N * H), where N is the number of nodes and H is the height of the tree.
Space Complexity: O(H), due to recursion stack and current path storage.
========================================================
*/

void dfs(TreeNode *root, vector<vector<int>> &allPaths, vector<int> &currPath)
{
    if (!root)
        return;

    // Add current node to the path.
    currPath.push_back(root->data);

    // If current node is a leaf, store the complete root-to-leaf path.
    if (!root->left && !root->right)
    {
        allPaths.push_back(currPath);

        // Backtrack before returning.
        currPath.pop_back();

        return;
    }

    // Explore left and right subtrees.
    dfs(root->left, allPaths, currPath);

    dfs(root->right, allPaths, currPath);

    // Remove current node while backtracking.
    currPath.pop_back();
}

vector<vector<int>> allRootToLeaf(TreeNode *root)
{
    vector<vector<int>> allPaths;

    vector<int> currPath;

    dfs(root, allPaths, currPath);

    return allPaths;
}

int main()
{
    TreeNode *root = new TreeNode(1);

    root->left = new TreeNode(2);
    root->right = new TreeNode(3);

    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    vector<vector<int>> paths = allRootToLeaf(root);

    for (const auto &path : paths)
    {
        for (int val : path)
        {
            cout << val << " ";
        }

        cout << endl;
    }

    return 0;
}