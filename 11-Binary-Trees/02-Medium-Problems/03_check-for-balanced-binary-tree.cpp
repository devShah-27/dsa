// Problem:
// Given the root of a binary tree, check whether it is height-balanced.
// A binary tree is balanced if the height difference between left and right subtrees
// of every node is at most one.

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
- If the height difference is greater than one, the tree is not balanced.
- Recursively repeat the same process for all nodes.

Time Complexity: O(N^2), because height is calculated repeatedly for each node.
Space Complexity: O(N), due to recursion stack in the worst case.
========================================================
*/

// int findHeight(TreeNode *root)
// {
//     if (!root)
//         return 0;

//     return 1 + max(findHeight(root->left), findHeight(root->right));
// }

// bool isBalanced(TreeNode *root)
// {
//     if (!root)
//         return true;

//     int lHeight = findHeight(root->left);
//     int rHeight = findHeight(root->right);

//     if (abs(lHeight - rHeight) > 1)
//         return false;

//     return isBalanced(root->left) && isBalanced(root->right);
// }

/*
========================================================
OPTIMAL APPROACH

Idea:
- Calculate the height of the tree using a bottom-up recursion.
- If any subtree is unbalanced, return -1 immediately to stop further checks.
- Return the height only when the subtree is balanced.

Time Complexity: O(N), because each node is visited only once.
Space Complexity: O(N), due to recursion stack in the worst case.
========================================================
*/

int findHeight(TreeNode *root)
{
    if (!root)
        return 0;

    int lHeight = findHeight(root->left);

    // Left subtree is unbalanced.
    if (lHeight == -1)
        return -1;

    int rHeight = findHeight(root->right);

    // Right subtree is unbalanced.
    if (rHeight == -1)
        return -1;

    // Current subtree is unbalanced.
    if (abs(lHeight - rHeight) > 1)
        return -1;

    // Return height of current subtree.
    return 1 + max(lHeight, rHeight);
}

bool isBalanced(TreeNode *root)
{
    return findHeight(root) != -1;
}

int main()
{
    TreeNode *root = new TreeNode(1);

    root->left = new TreeNode(2);
    root->right = new TreeNode(3);

    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    root->left->right->right = new TreeNode(6);
    root->left->right->right->right = new TreeNode(7);

    if (isBalanced(root))
    {
        cout << "The tree is balanced." << endl;
    }
    else
    {
        cout << "The tree is not balanced." << endl;
    }

    return 0;
}