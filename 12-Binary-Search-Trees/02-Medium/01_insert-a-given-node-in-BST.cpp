// Problem:
// Given the root of a Binary Search Tree (BST) and a value val, insert val into the BST.
// The value is guaranteed not to already exist in the BST.
// Return the root of the BST after insertion.

#include <bits/stdc++.h>
using namespace std;

class TreeNode
{
public:
    int data;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

void printInOrder(TreeNode *root)
{
    if (root == nullptr)
        return;

    printInOrder(root->left);
    cout << root->data << " ";
    printInOrder(root->right);
}

// ================================================================================
// OPTIMAL APPROACH — ITERATIVE BST INSERTION
//
// Idea:
// - Use the BST property to move toward the position where the new value belongs.
// - Move left if val is smaller and right if val is larger than the current node.
// - When the required child pointer is null, insert the new node there.
// - If the tree is empty, the new node itself becomes the root.
//
// Time Complexity: O(H), where H is the height of the BST.
// Space Complexity: O(1), using constant extra space.
// ================================================================================

TreeNode *insertIntoBST(TreeNode *root, int val)
{
    if (!root)
        return new TreeNode(val);

    TreeNode *temp = root;

    while (true)
    {
        if (temp->data > val)
        {
            if (temp->left)
                temp = temp->left;
            else
            {
                temp->left = new TreeNode(val);
                break;
            }
        }
        else
        {
            if (temp->right)
                temp = temp->right;
            else
            {
                temp->right = new TreeNode(val);
                break;
            }
        }
    }

    return root;
}

int main()
{
    TreeNode *root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(7);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);

    int val = 5;

    TreeNode *newRoot = insertIntoBST(root, val);

    printInOrder(newRoot);

    return 0;
}