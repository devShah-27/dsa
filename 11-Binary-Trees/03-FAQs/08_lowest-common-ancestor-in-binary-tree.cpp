// Problem:
// Given the root of a binary tree and two nodes p and q, find their lowest common ancestor (LCA).
// The LCA is the lowest node that has both p and q as descendants.
// Return the TreeNode itself, not its value.

#include <bits/stdc++.h>
using namespace std;

struct TreeNode
{
    int data;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int val) : data(val), left(NULL), right(NULL) {}
};

/*
========================================================
RECURSIVE POSTORDER APPROACH

Idea:
- Traverse the tree recursively and search for nodes p and q.
- If the current node is either p or q, return it as a potential ancestor.
- If both left and right subtrees return non-null nodes, the current node is the lowest common ancestor.
- Otherwise, return the non-null subtree result.

Time Complexity: O(N), where N is the number of nodes.
Space Complexity: O(H), due to recursion stack, where H is the height of the tree.
========================================================
*/

TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
{
    // If current node is one of the targets, it can be the LCA.
    if (!root || root == p || root == q)
        return root;

    // Search for nodes in left and right subtrees.
    TreeNode *leftVal = lowestCommonAncestor(root->left, p, q);

    TreeNode *rightVal = lowestCommonAncestor(root->right, p, q);

    // If one side is empty, LCA exists on the other side.
    if (!leftVal)
        return rightVal;

    if (!rightVal)
        return leftVal;

    // Both sides contain one target node, so current node is the LCA.
    return root;
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

    TreeNode *p = root->left;
    TreeNode *q = root->right;

    TreeNode *lca = lowestCommonAncestor(root, p, q);

    cout << "Lowest Common Ancestor: " << lca->data << endl;

    return 0;
}