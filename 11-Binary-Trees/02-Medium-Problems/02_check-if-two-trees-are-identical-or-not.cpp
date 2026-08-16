// Problem:
// Given roots of two binary trees, check whether they are identical or not.
// Two trees are identical if they have the same structure and corresponding nodes have the same values.

#include <bits/stdc++.h>
using namespace std;

struct TreeNode
{
    int data;
    TreeNode *left, *right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

/*
========================================================
RECURSIVE APPROACH

Idea:
- Compare both trees simultaneously using recursion.
- If both nodes are NULL, they are identical at that position.
- If one node is NULL or values differ, the trees are not identical.
- Recursively check the left and right subtrees.

Time Complexity: O(N), where N is the number of nodes in the smaller tree.
Space Complexity: O(H), due to recursion stack, where H is the height of the tree.
========================================================
*/

bool isSameTree(TreeNode *p, TreeNode *q)
{
    // Both nodes are NULL, meaning this part of the tree matches.
    if (!p || !q)
        return (p == q);

    // Check current node and recursively compare both subtrees.
    return (p->data == q->data) &&
           isSameTree(p->left, q->left) &&
           isSameTree(p->right, q->right);
}

int main()
{
    TreeNode *tree1 = new TreeNode(1);

    tree1->left = new TreeNode(2);
    tree1->right = new TreeNode(3);

    TreeNode *tree2 = new TreeNode(1);

    tree2->left = new TreeNode(2);
    tree2->right = new TreeNode(3);

    bool result = isSameTree(tree1, tree2);

    cout << "Are the trees identical? " << result << endl;

    delete tree1->left;
    delete tree1->right;
    delete tree1;

    delete tree2->left;
    delete tree2->right;
    delete tree2;

    return 0;
}