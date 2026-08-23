// Problem:
// Given a Binary Search Tree (BST) where exactly two nodes have been swapped by mistake, recover the BST without changing its structure.
// Only the values of the two incorrect nodes should be swapped back.

#include <bits/stdc++.h>
using namespace std;

struct TreeNode
{
    int data;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

void inorderPrint(TreeNode *root)
{
    if (root)
    {
        inorderPrint(root->left);
        cout << root->data << " ";
        inorderPrint(root->right);
    }
}

TreeNode *insertLevelOrder(vector<int> &arr, int i)
{
    if (i >= arr.size() || arr[i] == -1)
        return nullptr;

    TreeNode *root = new TreeNode(arr[i]);

    root->left = insertLevelOrder(arr, 2 * i + 1);
    root->right = insertLevelOrder(arr, 2 * i + 2);

    return root;
}

// ================================================================================
// BRUTE FORCE APPROACH — INORDER SORTING
//
// Idea:
// - Inorder traversal of a BST should always be sorted.
// - Store the inorder traversal, sort it, and replace node values using the sorted sequence while keeping the original tree structure unchanged.
//
// Time Complexity: O(N log N), due to sorting the inorder array.
// Space Complexity: O(N), for storing inorder traversal.
// ================================================================================

// void getInorder(TreeNode *root, vector<int> &inorder)
// {
//     if (!root)
//         return;

//     getInorder(root->left, inorder);

//     inorder.emplace_back(root->data);

//     getInorder(root->right, inorder);
// }

// void helper(TreeNode *root, vector<int> &inorder, int &idx)
// {
//     if (!root)
//         return;

//     helper(root->left, inorder, idx);

//     root->data = inorder[idx++];

//     helper(root->right, inorder, idx);
// }

// void recoverTree(TreeNode *root)
// {
//     if (!root)
//         return;

//     vector<int> inorder;

//     getInorder(root, inorder);

//     sort(inorder.begin(), inorder.end());

//     int idx = 0;

//     helper(root, inorder, idx);
// }

// ================================================================================
// OPTIMAL APPROACH — INORDER VIOLATION DETECTION
//
// Idea:
// - Inorder traversal of a valid BST is always increasing.
// - The swapped nodes create one or two inversions in this sequence.
// - Track the previous visited node and identify the misplaced nodes.
// - For adjacent swaps, swap first and middle; for non-adjacent swaps, swap first and last.
//
// Time Complexity: O(N), where N is the number of nodes.
// Space Complexity: O(H), due to recursive traversal stack.
// ================================================================================

void helper(
    TreeNode *root,
    TreeNode *&prev,
    TreeNode *&first,
    TreeNode *&middle,
    TreeNode *&last)
{
    if (!root)
        return;

    helper(root->left, prev, first, middle, last);

    // Detect an inversion in inorder traversal.
    if (prev && (root->data < prev->data))
    {
        if (!first)
        {
            // First violation: previous node is the first misplaced node.
            first = prev;
            middle = root;
        }
        else
        {
            // Second violation: current node is the second misplaced node.
            last = root;
        }
    }

    prev = root;

    helper(root->right, prev, first, middle, last);
}

void recoverTree(TreeNode *root)
{
    if (!root)
        return;

    TreeNode *prev = nullptr;
    TreeNode *first = nullptr;
    TreeNode *middle = nullptr;
    TreeNode *last = nullptr;

    helper(root, prev, first, middle, last);

    // Non-adjacent swapped nodes.
    if (first && last)
        swap(first->data, last->data);

    // Adjacent swapped nodes.
    else if (first && middle)
        swap(first->data, middle->data);
}

int main()
{
    vector<int> nodes = {1, 3, -1, -1, 2};

    TreeNode *root = insertLevelOrder(nodes, 0);

    inorderPrint(root);

    cout << endl;

    recoverTree(root);

    inorderPrint(root);

    return 0;
}