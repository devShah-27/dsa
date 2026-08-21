// Problem:
// Given the root of a binary tree, determine whether it is a valid Binary Search Tree (BST).
// A valid BST maintains: left subtree values < node value and right subtree values > node value.
// Every subtree must also satisfy the BST property.

#include <bits/stdc++.h>
using namespace std;

struct TreeNode
{
    int data;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

// ================================================================================
// OPTIMAL APPROACH — RANGE VALIDATION USING RECURSION
//
// Idea:
// - Maintain the valid range (minimum and maximum allowed values) for every node.
// - A node must lie strictly inside this range to satisfy BST properties.
// - Update the range while moving to the left and right subtrees.
// - Use long long boundaries to handle extreme integer values safely.
//
// Time Complexity: O(N), where N is the number of nodes in the tree.
// Space Complexity: O(H), due to the recursive call stack, where H is the height.
// ================================================================================

bool helper(TreeNode *root, long long minVal, long long maxVal)
{
    if (!root)
        return true;

    if (root->data <= minVal || root->data >= maxVal)
        return false;

    bool leftAns = helper(root->left, minVal, root->data);
    bool rightAns = helper(root->right, root->data, maxVal);

    return leftAns && rightAns;
}

bool isBST(TreeNode *root)
{
    return helper(root, LLONG_MIN, LLONG_MAX);
}

int main()
{
    TreeNode *root = new TreeNode(7);
    root->left = new TreeNode(5);
    root->right = new TreeNode(10);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(6);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(15);

    cout << isBST(root) << endl;
}