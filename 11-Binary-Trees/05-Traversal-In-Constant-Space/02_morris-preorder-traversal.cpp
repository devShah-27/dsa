// Problem:
// Given the root of a binary tree, return its preorder traversal.
// Use Morris Preorder Traversal to achieve O(1) auxiliary space without recursion or a stack.

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
// MORRIS PREORDER TRAVERSAL
//
// Idea:
// - If the current node has no left child, visit it and move to the right child.
// - Otherwise, find the inorder predecessor (rightmost node in the left subtree).
// - On the first visit, create a temporary thread, visit the current node, and move left.
// - On the second visit, remove the thread and move to the right subtree.
//
// Time Complexity: O(N), where N is the number of nodes.
// Space Complexity: O(1) auxiliary space, excluding the output vector.
// ================================================================================

vector<int> preorder(TreeNode *root)
{
    if (!root)
        return {};

    vector<int> res;

    TreeNode *curr = root;

    while (curr)
    {
        // No left subtree: visit current node and move to the right.
        if (!curr->left)
        {
            res.push_back(curr->data);

            curr = curr->right;
        }
        else
        {
            // Find the inorder predecessor of the current node.
            TreeNode *IP = curr->left;

            while (IP->right && IP->right != curr)
            {
                IP = IP->right;
            }

            // First visit: create a temporary thread, visit current node, and move left.
            if (!IP->right)
            {
                IP->right = curr;

                res.push_back(curr->data);

                curr = curr->left;
            }
            // Second visit: remove the temporary thread and move to the right subtree.
            else
            {
                IP->right = NULL;

                curr = curr->right;
            }
        }
    }

    return res;
}

int main()
{
    TreeNode *root = new TreeNode(1);

    root->left = new TreeNode(4);

    root->left->left = new TreeNode(4);

    root->left->left->left = new TreeNode(2);

    vector<int> preorderVal = preorder(root);

    cout << "Binary Tree Morris Preorder Traversal: ";

    for (int i : preorderVal)
    {
        cout << i << " ";
    }

    cout << endl;

    return 0;
}