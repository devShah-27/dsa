// Problem:
// Given the root of a Binary Search Tree (BST) and an integer k.
// Find the kth smallest and kth largest values (1-indexed) among all nodes.
// Return the result as {kth smallest, kth largest}.

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
// BRUTE FORCE APPROACH — STORE VALUES + SORT
//
// Idea:
// - Traverse the entire BST and store every node value in an array.
// - Sort the array in ascending order.
// - In the sorted array:
//      kth smallest = arr[k - 1]
//      kth largest  = arr[n - k]
//
// Time Complexity: O(N + NlogN), where N is the number of nodes.
//                  O(N) for traversal and O(NlogN) for sorting.
// Space Complexity: O(N), to store all node values.
// ================================================================================

// void storeValues(TreeNode *root, vector<int> &values)
// {
//     if (!root)
//         return;

//     values.push_back(root->data);

//     storeValues(root->left, values);
//     storeValues(root->right, values);
// }

// vector<int> kLargesSmall(TreeNode *root, int k)
// {
//     vector<int> values;

//     storeValues(root, values);

//     sort(values.begin(), values.end());

//     int n = values.size();

//     return {values[k - 1], values[n - k]};
// }

// ================================================================================
// OPTIMAL APPROACH — ITERATIVE INORDER / REVERSE INORDER TRAVERSAL
//
// Idea:
// - In a BST, inorder traversal gives nodes in ascending order.
// - Reverse inorder traversal gives nodes in descending order.
// - Use a stack to perform both traversals iteratively and stop once the kth node is reached instead of traversing the entire tree.
//
// Time Complexity: O(H + k), where H is the height of the BST.
// Space Complexity: O(H), due to the stack used for traversal.
// ================================================================================

int inorderTraversal(TreeNode *root, int k, bool findSmallest)
{
    int cnt = 0;

    TreeNode *node = root;

    stack<TreeNode *> st;

    while (true)
    {
        if (node)
        {
            st.push(node);

            // For kth smallest: move left first (inorder traversal).
            // For kth largest: move right first (reverse inorder traversal).
            node = findSmallest ? node->left : node->right;
        }
        else
        {
            if (st.empty())
                break;

            node = st.top();
            st.pop();

            cnt++;

            if (cnt == k)
                return node->data;

            // Continue traversal after visiting current node.
            // For kth smallest: explore right subtree.
            // For kth largest: explore left subtree.
            node = findSmallest ? node->right : node->left;
        }
    }

    return -1;
}

vector<int> kLargesSmall(TreeNode *root, int k)
{
    return {inorderTraversal(root, k, true), inorderTraversal(root, k, false)};
}

int main()
{
    TreeNode *root = new TreeNode(3);
    root->left = new TreeNode(1);
    root->left->right = new TreeNode(2);
    root->right = new TreeNode(4);

    int k = 1;

    vector<int> result = kLargesSmall(root, k);

    cout << "[" << result[0] << ", " << result[1] << "]" << endl;

    return 0;
}