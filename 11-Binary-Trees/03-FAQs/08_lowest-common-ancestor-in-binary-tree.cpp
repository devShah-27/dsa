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
    vector<TreeNode *> nodes(1024);

    for (int i = 1; i <= 1023; i++)
    {
        nodes[i] = new TreeNode(i);
    }

    for (int i = 1; i <= 511; i++)
    {
        nodes[i]->left = nodes[2 * i];
        nodes[i]->right = nodes[2 * i + 1];
    }

    TreeNode *root = nodes[1];

    TreeNode *p = nodes[500];
    TreeNode *q = nodes[900];

    TreeNode *lca = lowestCommonAncestor(root, p, q);

    cout << "LCA of " << p->data
         << " and " << q->data
         << " = " << lca->data << endl;

    p = nodes[1000];
    q = nodes[1001];

    lca = lowestCommonAncestor(root, p, q);

    cout << "LCA of " << p->data
         << " and " << q->data
         << " = " << lca->data << endl;

    p = nodes[100];
    q = nodes[400];

    lca = lowestCommonAncestor(root, p, q);

    cout << "LCA of " << p->data
         << " and " << q->data
         << " = " << lca->data << endl;

    p = nodes[1022];
    q = nodes[1023];

    lca = lowestCommonAncestor(root, p, q);

    cout << "LCA of " << p->data
         << " and " << q->data
         << " = " << lca->data << endl;

    return 0;
}