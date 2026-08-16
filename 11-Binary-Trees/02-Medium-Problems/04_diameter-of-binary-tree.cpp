// Problem:
// Given the root of a binary tree, return the diameter of the tree.
// Diameter is the length of the longest path between any two nodes.
// The path may or may not pass through the root node.

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
BRUTE FORCE APPROACH

Idea:
- For every node, calculate the height of its left and right subtrees.
- The diameter passing through the current node is the sum of both heights.
- Recursively calculate the maximum diameter in left and right subtrees.

Time Complexity: O(N^2), because height is calculated repeatedly.
Space Complexity: O(N), due to recursion stack in the worst case.
========================================================
*/

// int findHeight(TreeNode *root)
// {
//     if (!root)
//         return 0;

//     return 1 + max(findHeight(root->left), findHeight(root->right));
// }

// int diameterOfBinaryTree(TreeNode *root)
// {
//     if (!root)
//         return 0;

//     int lH = findHeight(root->left);
//     int rH = findHeight(root->right);

//     int diameter = lH + rH;

//     return max({diameter, diameterOfBinaryTree(root->left), diameterOfBinaryTree(root->right)});
// }

/*
========================================================
OPTIMAL APPROACH

Idea:
- Calculate height of each subtree using a bottom-up recursion.
- For every node, the longest path passing through it is:
  left subtree height + right subtree height.
- Maintain the maximum diameter while calculating heights.

Time Complexity: O(N), because each node is visited only once.
Space Complexity: O(N), due to recursion stack in the worst case.
========================================================
*/

int findHeight(TreeNode *root, int &diameter)
{
    if (!root)
        return 0;

    int lH = findHeight(root->left, diameter);

    int rH = findHeight(root->right, diameter);

    // Update maximum diameter using the current node as the path junction.
    diameter = max(diameter, lH + rH);

    // Return height of current subtree.
    return 1 + max(lH, rH);
}

int diameterOfBinaryTree(TreeNode *root)
{
    int diameter = 0;

    findHeight(root, diameter);

    return diameter;
}

int main()
{
    TreeNode *root = new TreeNode(1);

    root->left = new TreeNode(2);
    root->right = new TreeNode(3);

    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    cout << "Diameter of the binary tree is: " << diameterOfBinaryTree(root) << endl;

    return 0;
}