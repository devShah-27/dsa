// Problem:
// Given the root of a Binary Search Tree (BST) and two node values p and q.
// Find and return the Lowest Common Ancestor (LCA) of the two nodes.
// The LCA is the lowest node that has both p and q as descendants (a node can be a descendant of itself).

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
// BRUTE FORCE APPROACH — PATH COMPARISON
//
// Idea:
// - Find the path from root to both target nodes.
// - Compare both paths until the nodes differ.
// - The last common node in both paths is the LCA.
//
// Time Complexity: O(N), where N is the number of nodes in the BST.
// Space Complexity: O(H), where H is the height of the BST, due to stored paths.
// ================================================================================

// bool getPath(TreeNode *root, int target, vector<TreeNode *> &path)
// {
//     if (!root)
//         return false;

//     path.push_back(root);

//     if (root->data == target)
//         return true;

//     if (getPath(root->left, target, path) || getPath(root->right, target, path))
//         return true;

//     path.pop_back();

//     return false;
// }

// TreeNode *lca(TreeNode *root, int p, int q)
// {
//     if (!root)
//         return nullptr;

//     vector<TreeNode *> pathP, pathQ;

//     getPath(root, p, pathP);
//     getPath(root, q, pathQ);

//     TreeNode *lca = nullptr;

//     int i = 0;

//     while (i < pathP.size() && i < pathQ.size() && pathP[i] == pathQ[i])
//     {
//         lca = pathP[i];
//         i++;
//     }

//     return lca;
// }

// ================================================================================
// OPTIMAL APPROACH — USING BST PROPERTY
//
// Idea:
// - Use the ordering property of BST to avoid searching both subtrees.
// - If both nodes are smaller than the current node, move to the left subtree.
// - If both nodes are larger than the current node, move to the right subtree.
// - Otherwise, the current node is the split point and is the LCA.
//
// Time Complexity: O(H), where H is the height of the BST.
// Space Complexity: O(H), due to recursive call stack.
// ================================================================================

TreeNode *lca(TreeNode *root, int p, int q)
{
    if (!root)
        return nullptr;

    int val = root->data;

    if (val > p && val > q)
        return lca(root->left, p, q);

    if (val < p && val < q)
        return lca(root->right, p, q);

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

    root->left->right->left = new TreeNode(7);
    root->left->right->right = new TreeNode(4);

    TreeNode *ans = lca(root, 5, 1);

    if (ans != nullptr)
    {
        cout << "LCA(5, 1) = " << ans->data << endl;
    }
    else
    {
        cout << "LCA(5, 1) is not present in the tree" << endl;
    }

    ans = lca(root, 5, 4);

    if (ans != nullptr)
    {
        cout << "LCA(5, 4) = " << ans->data << endl;
    }
    else
    {
        cout << "LCA(5, 4) is not present in the tree" << endl;
    }

    return 0;
}