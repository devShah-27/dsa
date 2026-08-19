// Problem:
// Given inorder and postorder traversals of the same binary tree, construct and return the tree.
// Assume all node values are unique, so the inorder position of each value uniquely identifies
// the left and right subtrees.

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
    if (!root)
    {
        return;
    }

    printInorder(root->left);

    cout << root->data << " ";

    printInorder(root->right);
}

void printVector(vector<int> &vec)
{
    for (int num : vec)
    {
        cout << num << " ";
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
// - The last element of postorder traversal is always the root of the current subtree.
// - Find the root position in inorder to divide the tree into left and right subtrees.
// - Since postorder gives root at the end, process the right subtree before the left subtree.
// - Use a hash map for O(1) average-time lookup of root positions in inorder.
//
// Time Complexity: O(N) average, where N is the number of nodes.
// Space Complexity: O(N) for the inorder index map and O(H) recursion stack,
//                   where H is the height of the tree.
// ================================================================================

TreeNode *helper(
    vector<int> &inorder,
    vector<int> &postorder,
    unordered_map<int, int> &inorderIndex,
    int &postIdx,
    int left,
    int right)
{
    if (left > right)
        return NULL;

    // The last element in postorder is the root of the current subtree.
    TreeNode *root = new TreeNode(postorder[postIdx]);

    // Find root position in inorder traversal.
    int inIdx = inorderIndex[root->data];

    // Move to the next root in postorder.
    postIdx--;

    // Build right subtree first because postorder is processed from the end.
    root->right =
        helper(inorder, postorder, inorderIndex, postIdx, inIdx + 1, right);

    // Build left subtree after completing the right subtree.
    root->left =
        helper(inorder, postorder, inorderIndex, postIdx, left, inIdx - 1);

    return root;
}

TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
{
    unordered_map<int, int> inorderIndex;

    // Store inorder indices for constant-time root position lookup.
    buildInorderIndex(inorder, inorderIndex);

    int postIdx = postorder.size() - 1;

    return helper(
        inorder,
        postorder,
        inorderIndex,
        postIdx,
        0,
        inorder.size() - 1);
}

int main()
{
    vector<int> inorder = {40, 20, 50, 10, 60, 30};

    vector<int> postorder = {40, 50, 20, 60, 30, 10};

    cout << "Inorder Vector: ";
    printVector(inorder);

    cout << "Postorder Vector: ";
    printVector(postorder);

    TreeNode *root = buildTree(inorder, postorder);

    cout << "Inorder of Unique Binary Tree Created: " << endl;
    printInorder(root);
    cout << endl;

    return 0;
}