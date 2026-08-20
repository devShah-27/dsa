// Problem:
// Given the root of a Binary Search Tree (BST) and an integer value.
// Find and return the subtree rooted at the node containing the given value.
// If the value does not exist in the BST, return nullptr.

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
// OPTIMAL APPROACH — ITERATIVE BST SEARCH
//
// Idea:
// - Use the BST property to decide which subtree can contain the target value.
// - If target is smaller, move to the left subtree.
// - If target is larger, move to the right subtree.
// - Continue until the node is found or the search space becomes empty.
//
// Time Complexity: O(H), where H is the height of the BST.
// Space Complexity: O(1), using constant extra space.
// ================================================================================

TreeNode *searchBST(TreeNode *root, int val)
{
    while (root)
    {
        if (root->data == val)
            return root;

        root = (root->data > val) ? root->left : root->right;
    }

    return nullptr;
}

int main()
{
    TreeNode *root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(7);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);

    TreeNode *result = searchBST(root, 2);

    if (result)
        cout << "Node found with value: " << result->data << endl;
    else
        cout << "Node not found" << endl;

    return 0;
}