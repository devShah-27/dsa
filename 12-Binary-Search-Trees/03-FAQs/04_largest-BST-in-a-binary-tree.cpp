// Problem:
// Given a binary tree, find the size of the largest subtree that is also a valid BST.
// A valid BST has all left subtree values smaller than the node value and all right
// subtree values greater than the node value.

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
// BRUTE FORCE APPROACH — CHECK EVERY SUBTREE
//
// Idea:
// - Treat every node as the root of a possible BST subtree.
// - Validate whether the subtree rooted at the current node is a BST.
// - If valid, calculate its size and update the maximum size found.
//
// Time Complexity: O(N^2) in the worst case.
// Space Complexity: O(H), due to traversal stack.
// ================================================================================

// bool isValidBST(TreeNode *root, long long minVal, long long maxVal)
// {
//     if (!root)
//         return true;

//     if (root->data <= minVal || root->data >= maxVal)
//         return false;

//     bool left = isValidBST(root->left, minVal, root->data);
//     bool right = isValidBST(root->right, root->data, maxVal);

//     return left && right;
// }

// int findLength(TreeNode *root)
// {
//     if (!root)
//         return 0;

//     return 1 + findLength(root->left) + findLength(root->right);
// }

// int largestBST(TreeNode *root)
// {
//     if (!root)
//         return 0;

//     stack<TreeNode *> st;

//     TreeNode *temp = root;

//     int maxLength = 0;

//     while (true)
//     {
//         if (temp)
//         {
//             st.push(temp);
//             temp = temp->left;
//         }
//         else
//         {
//             if (st.empty())
//                 break;

//             temp = st.top();
//             st.pop();

//             if (isValidBST(temp, LLONG_MIN, LLONG_MAX))
//                 maxLength = max(maxLength, findLength(temp));

//             temp = temp->right;
//         }
//     }

//     return maxLength;
// }

// ================================================================================
// OPTIMAL APPROACH — POSTORDER PROPERTY INFORMATION
//
// Idea:
// - Solve the problem using postorder traversal (left -> right -> root).
// - For every subtree, store:
//   1. Size of the largest BST found inside the subtree.
//   2. Minimum value in the subtree.
//   3. Maximum value in the subtree.
// - A subtree is a BST if:
//      root value > maximum value of left subtree
//      root value < minimum value of right subtree
// - If the current subtree is not a BST, only pass the larger BST size from its children.
//
// Time Complexity: O(N), as every node is processed once.
// Space Complexity: O(H), due to recursive call stack.
// ================================================================================

class NodeVal
{
    int maxLength = 0;
    long long minVal = LLONG_MAX;
    long long maxVal = LLONG_MIN;

public:
    NodeVal(int _maxLength, long long _minVal, long long _maxVal)
    {
        maxLength = _maxLength;
        minVal = _minVal;
        maxVal = _maxVal;
    }

    int getMaxLength()
    {
        return maxLength;
    }

    long long getMaxVal()
    {
        return maxVal;
    }

    long long getMinVal()
    {
        return minVal;
    }
};

NodeVal helper(TreeNode *root)
{
    if (!root)
        return NodeVal(0, LLONG_MAX, LLONG_MIN);

    NodeVal leftVal = helper(root->left);
    NodeVal rightVal = helper(root->right);

    // Current subtree forms a valid BST.
    if (root->data > leftVal.getMaxVal() &&
        root->data < rightVal.getMinVal())
    {
        return NodeVal(
            leftVal.getMaxLength() + rightVal.getMaxLength() + 1,
            min((long long)root->data, leftVal.getMinVal()),
            max((long long)root->data, rightVal.getMaxVal()));
    }

    // Current subtree is not a BST.
    return NodeVal(
        max(leftVal.getMaxLength(), rightVal.getMaxLength()),
        LLONG_MIN,
        LLONG_MAX);
}

int largestBST(TreeNode *root)
{
    if (!root)
        return 0;

    return helper(root).getMaxLength();
}

int main()
{
    TreeNode *root = new TreeNode(2);

    root->left = new TreeNode(1);
    root->right = new TreeNode(3);

    cout << largestBST(root) << endl;

    TreeNode *root2 = new TreeNode(10);

    root2->left = new TreeNode(5);
    root2->right = new TreeNode(15);

    root2->left->left = new TreeNode(1);
    root2->left->right = new TreeNode(8);

    root2->right->right = new TreeNode(7);

    cout << largestBST(root2) << endl;
}