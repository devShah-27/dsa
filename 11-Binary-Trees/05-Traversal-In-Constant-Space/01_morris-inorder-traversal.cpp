// Problem:
// Given the root of a binary tree, return its inorder traversal.
// Use Morris Inorder Traversal to achieve O(1) auxiliary space without recursion or a stack.

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
// MORRIS INORDER TRAVERSAL
//
// Idea:
// - For a node with no left child, visit it and move to its right child.
// - Otherwise, find the inorder predecessor (rightmost node in the left subtree).
// - Create a temporary thread from the predecessor to the current node.
// - On the second visit, remove the thread, visit the current node, and move right.
//
// Time Complexity: O(N), where N is the number of nodes.
// Space Complexity: O(1) auxiliary space, excluding the output vector.
// ================================================================================

vector<int> getInorder(TreeNode *root)
{
    if (!root)
        return {};

    vector<int> res;

    TreeNode *curr = root;

    while (curr)
    {
        // No left subtree: visit current node and move right.
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

            // First visit: create a temporary thread to the current node.
            if (!IP->right)
            {
                IP->right = curr;

                curr = curr->left;
            }
            // Second visit: remove the thread, visit current, and move right.
            else
            {
                IP->right = NULL;

                res.push_back(curr->data);

                curr = curr->right;
            }
        }
    }

    return res;
}

int main()
{
    TreeNode *root = new TreeNode(1);

    root->left = new TreeNode(2);

    root->right = new TreeNode(3);

    root->left->left = new TreeNode(4);

    root->left->right = new TreeNode(5);

    root->left->right->right = new TreeNode(6);

    vector<int> inorder = getInorder(root);

    cout << "Binary Tree Morris Inorder Traversal: ";

    for (int val : inorder)
    {
        cout << val << " ";
    }

    cout << endl;

    return 0;
}