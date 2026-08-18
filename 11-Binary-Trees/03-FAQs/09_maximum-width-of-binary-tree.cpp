// Problem:
// Given the root of a binary tree, return its maximum width.
// The width of a level is the distance between the leftmost and rightmost non-null nodes, including the null positions that would exist in a complete binary tree representation.

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
BFS + INDEXING APPROACH

Idea:
- Assign an index to every node as if the tree is stored in an array:
  - Root index = 0.
  - Left child index = 2 * index + 1.
  - Right child index = 2 * index + 2.
- Perform level order traversal while tracking node indices.
- The width of each level is calculated using the difference between the first and last node indices of that level.
- Normalize indices at every level to avoid integer overflow caused by large depths.

Time Complexity: O(N), where N is the number of nodes.
Space Complexity: O(N), due to the queue storing nodes.
========================================================
*/

long long int widthOfBinaryTree(TreeNode *root)
{
    if (!root)
        return 0;

    // Queue stores node and its position index.
    queue<pair<TreeNode *, int>> q;

    q.push({root, 0});

    long long int maxWidth = INT_MIN;

    while (!q.empty())
    {
        int levelSize = q.size();

        // Normalize indices to prevent overflow.
        int minIdx = q.front().second;

        int firstIdx, lastIdx;

        for (int i = 0; i < levelSize; i++)
        {
            // Relative index within the current level.
            int currIdx = q.front().second - minIdx;

            TreeNode *currNode = q.front().first;

            q.pop();

            // Store first and last node positions of this level.
            if (i == 0)
                firstIdx = currIdx;

            if (i == levelSize - 1)
                lastIdx = currIdx;

            // Assign indices to children based on complete binary tree structure.
            if (currNode->left)
                q.push({currNode->left, (2 * currIdx) + 1});

            if (currNode->right)
                q.push({currNode->right, (2 * currIdx) + 2});
        }

        // Width includes all positions between first and last nodes.
        maxWidth = max(maxWidth, (long long int)(lastIdx - firstIdx + 1));
    }

    return maxWidth;
}

int main()
{
    TreeNode *root = new TreeNode(3);

    root->left = new TreeNode(5);
    root->right = new TreeNode(1);

    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(2);

    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(8);

    root->left->right->left = new TreeNode(7);
    root->left->right->right = new TreeNode(4);

    long long int maxWidth = widthOfBinaryTree(root);

    cout << "Maximum width of the binary tree is: " << maxWidth << endl;

    return 0;
}