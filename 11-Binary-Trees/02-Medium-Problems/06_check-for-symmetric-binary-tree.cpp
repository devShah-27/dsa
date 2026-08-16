// Problem:
// Given the root of a binary tree, check whether it is symmetric around its center.
// A tree is symmetric if the left subtree is a mirror reflection of the right subtree.

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
RECURSIVE APPROACH

Idea:
- Compare the left and right subtrees of the root simultaneously.
- Two trees are mirror images if their values match and:
  left subtree's left child matches right subtree's right child,
  left subtree's right child matches right subtree's left child.

Time Complexity: O(N), where N is the number of nodes.
Space Complexity: O(H), due to recursion stack, where H is the height of the tree.
========================================================
*/

bool isSymmetricHelp(TreeNode *leftST, TreeNode *rightST)
{
    // Both nodes are NULL, so this part is symmetric.
    if (!leftST || !rightST)
        return leftST == rightST;

    // Values must match for mirror symmetry.
    if (leftST->data != rightST->data)
        return false;

    // Compare outer and inner subtree pairs.
    return isSymmetricHelp(leftST->left, rightST->right) &&
           isSymmetricHelp(leftST->right, rightST->left);
}

bool isSymmetric(TreeNode *root)
{
    if (!root)
        return true;

    return isSymmetricHelp(root->left, root->right);
}

int main()
{
    TreeNode *root = new TreeNode(1);

    root->left = new TreeNode(2);
    root->right = new TreeNode(2);

    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(4);

    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(3);

    cout << boolalpha << isSymmetric(root) << endl;

    return 0;
}