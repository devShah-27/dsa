// Problem:
// Given the root of a Binary Search Tree (BST) and a key present in the tree, find the inorder predecessor and successor of the key.
// Return -1 if either the predecessor or successor does not exist.

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
// BRUTE FORCE APPROACH — INORDER + BINARY SEARCH
//
// Idea:
// - Inorder traversal of a BST produces values in sorted order.
// - Store the complete inorder traversal in an array.
// - Binary search for the key, then use the adjacent elements as predecessor and successor.
//
// Time Complexity: O(N) for inorder traversal + O(log N) for binary search.
// Space Complexity: O(N) for the inorder array.
// ================================================================================

// void inorderTraversal(TreeNode *root, vector<int> &inorder)
// {
//     if (!root)
//         return;

//     inorderTraversal(root->left, inorder);
//     inorder.emplace_back(root->data);
//     inorderTraversal(root->right, inorder);
// }

// int binarySearch(vector<int> &inorder, int key)
// {
//     int low = 0, high = inorder.size() - 1;

//     while (low <= high)
//     {
//         int mid = low + ((high - low) / 2);

//         if (inorder[mid] == key)
//             return mid;

//         if (inorder[mid] < key)
//             low = mid + 1;
//         else
//             high = mid - 1;
//     }

//     return -1;
// }

// vector<int> succPredBST(TreeNode *root, int key)
// {
//     if (!root)
//         return {};

//     vector<int> inorder;

//     inorderTraversal(root, inorder);

//     int n = inorder.size();

//     int keyIdx = binarySearch(inorder, key);

//     int predecessor = (keyIdx == 0 || keyIdx == -1) ? -1 : inorder[keyIdx - 1];

//     int successor = (keyIdx == n - 1 || keyIdx == -1) ? -1 : inorder[keyIdx + 1];

//     return {predecessor, successor};
// }

// ================================================================================
// BETTER APPROACH — INORDER TRAVERSAL WITHOUT STORING THE ARRAY
//
// Idea:
// - Traverse the BST in inorder order, which visits nodes in sorted order.
// - Keep updating the predecessor with every value smaller than the key.
// - Once the key is found, the first larger value visited afterward is the successor.
// - Avoid storing the complete inorder traversal.
//
// Time Complexity: O(N) in the worst case.
// Space Complexity: O(H) for the recursive call stack.
// ================================================================================

// void inorderTraversal(
//     TreeNode *root,
//     int key,
//     TreeNode *&predecessor,
//     TreeNode *&successor,
//     bool &found)
// {
//     if (!root)
//         return;

//     inorderTraversal(
//         root->left,
//         key,
//         predecessor,
//         successor,
//         found);

//     if (root->data < key)
//     {
//         predecessor = root;
//     }
//     else if (root->data == key)
//     {
//         found = true;
//     }
//     else if (root->data > key && found && !successor)
//     {
//         successor = root;
//         return;
//     }

//     inorderTraversal(
//         root->right,
//         key,
//         predecessor,
//         successor,
//         found);
// }

// vector<int> succPredBST(TreeNode *root, int key)
// {
//     if (!root)
//         return {};

//     TreeNode *predecessor = nullptr;
//     TreeNode *successor = nullptr;
//     bool found = false;

//     inorderTraversal(
//         root,
//         key,
//         predecessor,
//         successor,
//         found);

//     int pred = predecessor ? predecessor->data : -1;
//     int succ = successor ? successor->data : -1;

//     return {pred, succ};
// }

// ================================================================================
// OPTIMAL APPROACH — DIRECT BST SEARCH
//
// Idea:
// - Use the BST property to find the predecessor and successor without traversal.
// - For predecessor, values >= key cannot be the answer, so move left; otherwise, store the current node as a candidate and move right for a larger candidate.
// - For successor, values <= key cannot be the answer, so move right; otherwise, store the current node as a candidate and move left for a smaller candidate.
//
// Time Complexity: O(H), where H is the height of the BST.
// Space Complexity: O(1), using constant extra space.
// ================================================================================

int getPredecessor(TreeNode *root, int key)
{
    TreeNode *predecessor = nullptr;

    while (root)
    {
        if (root->data >= key)
        {
            root = root->left;
        }
        else
        {
            predecessor = root;
            root = root->right;
        }
    }

    return predecessor ? predecessor->data : -1;
}

int getSuccessor(TreeNode *root, int key)
{
    TreeNode *successor = nullptr;

    while (root)
    {
        if (root->data <= key)
        {
            root = root->right;
        }
        else
        {
            successor = root;
            root = root->left;
        }
    }

    return successor ? successor->data : -1;
}

vector<int> succPredBST(TreeNode *root, int key)
{
    int predVal = getPredecessor(root, key);
    int succVal = getSuccessor(root, key);

    return {predVal, succVal};
}

int main()
{
    TreeNode *root = new TreeNode(5);
    root->left = new TreeNode(2);
    root->right = new TreeNode(10);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(4);
    root->right->left = new TreeNode(7);
    root->right->right = new TreeNode(12);

    vector<int> result = succPredBST(root, 10);

    cout << "[" << result[0] << ", " << result[1] << "]" << endl;

    return 0;
}