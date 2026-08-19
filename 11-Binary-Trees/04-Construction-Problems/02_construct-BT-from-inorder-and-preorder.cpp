// Problem:
// Given preorder and inorder traversals of the same binary tree, construct and return the tree.
// Assume all node values are unique, so the inorder position of each value uniquely identifies the left and right subtrees.

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
// HELPER FUNCTIONS
// ================================================================================

void printInorder(TreeNode *root)
{
    if (root != nullptr)
    {
        printInorder(root->left);

        cout << root->data << " ";

        printInorder(root->right);
    }
}

void printVector(vector<int> &vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << " ";
    }

    cout << endl;
}

void buildInorderIndex(
    const vector<int> &inorder,
    unordered_map<int, int> &inorderIndex)
{
    for (int i = 0; i < inorder.size(); i++)
    {
        inorderIndex[inorder[i]] = i;
    }
}

// ================================================================================
// OPTIMAL APPROACH
//
// Idea:
// - The first element of the current preorder range is always the root.
// - Find this root's position in inorder to divide the tree into left and right subtrees.
// - The number of elements on the left in inorder determines the corresponding preorder range.
// - Use an index map for O(1) average-time lookup of each root in the inorder traversal.
//
// Time Complexity: O(N) average, where N is the number of nodes.
// Space Complexity: O(N) for the inorder index map and O(H) recursion stack,
//                   where H is the height of the tree.
// ================================================================================

TreeNode *buildTreeHelper(
    const vector<int> &preorder,
    int preorderStart,
    int preorderEnd,
    const vector<int> &inorder,
    int inorderStart,
    int inorderEnd,
    unordered_map<int, int> &inorderIndex)
{
    if (preorderStart > preorderEnd || inorderStart > inorderEnd)
        return nullptr;

    // The first element of preorder is the root of the current subtree.
    int rootValue = preorder[preorderStart];

    TreeNode *root = new TreeNode(rootValue);

    // Locate the root in inorder to separate left and right subtrees.
    int rootInorderIndex = inorderIndex[rootValue];

    // Number of nodes belonging to the left subtree.
    int leftSubtreeSize = rootInorderIndex - inorderStart;

    // Build the left subtree using the corresponding preorder and inorder ranges.
    root->left = buildTreeHelper(
        preorder,
        preorderStart + 1,
        preorderStart + leftSubtreeSize,
        inorder,
        inorderStart,
        rootInorderIndex - 1,
        inorderIndex);

    // Build the right subtree using the remaining preorder and inorder ranges.
    root->right = buildTreeHelper(
        preorder,
        preorderStart + leftSubtreeSize + 1,
        preorderEnd,
        inorder,
        rootInorderIndex + 1,
        inorderEnd,
        inorderIndex);

    return root;
}

TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
{
    unordered_map<int, int> inorderMap;

    // Precompute each value's position in inorder for O(1) average lookup.
    buildInorderIndex(inorder, inorderMap);

    return buildTreeHelper(
        preorder,
        0,
        preorder.size() - 1,
        inorder,
        0,
        inorder.size() - 1,
        inorderMap);
}

int main()
{
    vector<int> inorder = {9, 3, 15, 20, 7};
    vector<int> preorder = {3, 9, 20, 15, 7};

    cout << "Inorder Vector: ";
    printVector(inorder);

    cout << "Preorder Vector: ";
    printVector(preorder);

    TreeNode *root = buildTree(preorder, inorder);

    cout << "Inorder of Unique Binary Tree Created:" << endl;
    printInorder(root);
    cout << endl;

    return 0;
}