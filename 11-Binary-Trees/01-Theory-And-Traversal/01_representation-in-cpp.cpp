// Problem:
// Create a basic binary tree structure using a Node class.
// Each node stores a value and pointers to its left and right children.
// Build a sample binary tree manually using dynamic memory allocation.

#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *left, *right;

    Node(int val)
    {
        data = val;
        left = right = NULL;
    }
};

int main()
{
    // Create the root node of the binary tree.
    Node *root = new Node(1);

    // Create and attach the left and right children of the root.
    root->left = new Node(2);
    root->right = new Node(3);

    // Attach a right child to the left subtree.
    root->left->right = new Node(5);
}