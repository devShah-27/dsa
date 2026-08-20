// Problem:
// Given the root of a Binary Search Tree (BST) and a key, delete the node containing the key.
// Return the root of the BST after deletion while preserving the BST property.
// If the key does not exist, return the original tree unchanged.

#include <bits/stdc++.h>
using namespace std;

struct TreeNode
{
    int data;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : data(x), left(nullptr), right(nullptr) {}
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
// HELPER — FIND RIGHTMOST NODE
//
// Idea:
// - Starting from a subtree, repeatedly move to the right child.
// - The rightmost node contains the maximum value in that subtree.
// - This node is used to connect the deleted node's right subtree.
//
// Time Complexity: O(H), where H is the height of the subtree.
// Space Complexity: O(1).
// ================================================================================

TreeNode *findRightmostLeftChild(TreeNode *root)
{
    while (root && root->right)
        root = root->right;

    return root;
}

// ================================================================================
// HELPER — RECONNECT SUBTREES AFTER DELETION
//
// Idea:
// - If the node has no left child, replace it with its right subtree.
// - If the node has no right child, replace it with its left subtree.
// - If both children exist, use the left subtree as the replacement.
// - Attach the original right subtree to the rightmost node of the left subtree,
//   preserving the BST ordering.
//
// Time Complexity: O(H) in the two-child case.
// Space Complexity: O(1).
// ================================================================================

TreeNode *makeConnections(TreeNode *root)
{
    if (!root->left)
        return root->right;

    if (!root->right)
        return root->left;

    TreeNode *rightChild = root->right;
    TreeNode *rightmostLeftChild = findRightmostLeftChild(root->left);

    rightmostLeftChild->right = rightChild;

    return root->left;
}

// ================================================================================
// ITERATIVE BST DELETION
//
// Idea:
// - Use the BST property to search for the node containing the key.
// - Once found, reconnect its children using makeConnections().
// - For a non-root node, update its parent's corresponding child pointer.
// - The root is handled separately because deleting it may change the root itself.
//
// Time Complexity: O(H), where H is the height of the BST.
// Space Complexity: O(1), using constant extra space.
// ================================================================================

TreeNode *deleteNode(TreeNode *root, int key)
{
    if (!root)
        return nullptr;

    // Special case: the node to delete is the root.
    if (root->data == key)
        return makeConnections(root);

    TreeNode *temp = root;

    while (temp)
    {
        if (temp->data > key)
        {
            // The target is the left child of the current node.
            if (temp->left && temp->left->data == key)
            {
                temp->left = makeConnections(temp->left);
                break;
            }
            else
            {
                temp = temp->left;
            }
        }
        else
        {
            // The target is the right child of the current node.
            if (temp->right && temp->right->data == key)
            {
                temp->right = makeConnections(temp->right);
                break;
            }
            else
            {
                temp = temp->right;
            }
        }
    }

    return root;
}

int main()
{
    TreeNode *root = new TreeNode(5);
    root->left = new TreeNode(3);
    root->right = new TreeNode(8);
    root->left->left = new TreeNode(2);
    root->left->right = new TreeNode(4);

    root = deleteNode(root, 3);

    printInOrder(root);

    return 0;
}