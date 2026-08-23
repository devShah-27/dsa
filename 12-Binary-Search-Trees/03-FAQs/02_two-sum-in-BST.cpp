// Problem:
// Given the root of a Binary Search Tree (BST) and an integer k.
// Check whether there exist two distinct nodes in the BST whose values add up to k.
// Return true if such a pair exists, otherwise return false.

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
// BRUTE FORCE APPROACH — INORDER + TWO POINTER
//
// Idea:
// - Perform inorder traversal of BST to get values in sorted order.
// - Apply the two-pointer technique on the sorted array.
// - Move pointers based on the current sum compared with k.
//
// Time Complexity: O(N), where N is the number of nodes.
// Space Complexity: O(N), for storing inorder traversal.
// ================================================================================

// void getInorder(TreeNode *root, vector<int> &inorder)
// {
//     if (!root)
//         return;

//     getInorder(root->left, inorder);
//     inorder.push_back(root->data);
//     getInorder(root->right, inorder);
// }

// bool twoSumBST(TreeNode *root, int k)
// {
//     if (!root)
//         return false;

//     vector<int> inorder;

//     getInorder(root, inorder);

//     int l = 0;
//     int r = inorder.size() - 1;

//     while (l < r)
//     {
//         if (inorder[l] + inorder[r] == k)
//             return true;

//         else if (inorder[l] + inorder[r] > k)
//             r--;

//         else
//             l++;
//     }

//     return false;
// }

// ================================================================================
// OPTIMAL APPROACH — TWO BST ITERATORS
//
// Idea:
// - Use two iterators to simulate two pointers directly on the BST.
// - One iterator performs normal inorder traversal (smallest to largest).
// - The other performs reverse inorder traversal (largest to smallest).
// - Move the pointers similar to the two-pointer approach until they meet.
//
// Time Complexity: O(N), each node is visited at most once.
// Space Complexity: O(H), where H is the height of the BST.
// ================================================================================

class BSTIterator
{
    stack<TreeNode *> st;
    bool reverse = false;

private:
    // Push the complete path towards the next smallest/largest element.
    void pushAll(TreeNode *node)
    {
        while (node)
        {
            st.push(node);

            if (!reverse)
                node = node->left; // Normal inorder: move left first
            else
                node = node->right; // Reverse inorder: move right first
        }
    }

public:
    BSTIterator(TreeNode *root, bool _reverse)
    {
        reverse = _reverse;
        pushAll(root);
    }

    bool hasNext()
    {
        return !st.empty();
    }

    int next()
    {
        TreeNode *topNode = st.top();
        st.pop();

        if (!reverse)
            pushAll(topNode->right); // Continue normal inorder
        else
            pushAll(topNode->left); // Continue reverse inorder

        return topNode->data;
    }
};

bool twoSumBST(TreeNode *root, int k)
{
    if (!root)
        return false;

    BSTIterator i(root, false); // Left iterator gives increasing values.
    BSTIterator j(root, true);  // Right iterator gives decreasing values.

    int l = i.next();
    int r = j.next();

    while (l < r)
    {
        if (l + r == k)
            return true;

        else if (l + r > k)
            r = j.next();

        else
            l = i.next();
    }

    return false;
}

int main()
{
    TreeNode *root = new TreeNode(5);

    root->left = new TreeNode(3);
    root->right = new TreeNode(6);

    root->left->left = new TreeNode(2);
    root->left->right = new TreeNode(4);

    root->right->right = new TreeNode(7);

    int k = 9;

    bool result = twoSumBST(root, k);

    cout << (result ? "True" : "False") << endl;

    delete root->right->right;
    delete root->left->right;
    delete root->left->left;
    delete root->right;
    delete root->left;
    delete root;

    return 0;
}