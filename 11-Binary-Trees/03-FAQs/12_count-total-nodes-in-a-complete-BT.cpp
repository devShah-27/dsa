// Problem:
// Given the root of a complete binary tree, return the total number of nodes.
// A complete binary tree has all levels completely filled except possibly the last, where nodes are filled from left to right.

#include <bits/stdc++.h>
using namespace std;

struct TreeNode
{
    int data;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

/*
========================================================
BRUTE FORCE APPROACH

Idea:
- Traverse the entire tree using DFS.
- Count every visited node.
- Works for all types of binary trees.

Time Complexity: O(N), where N is the number of nodes.
Space Complexity: O(H), due to recursion stack.
========================================================
*/

// void inOrderTraversal(TreeNode *root, int &count)
// {
//     if (!root)
//         return;

//     inOrderTraversal(root->left, count);

//     count++;

//     inOrderTraversal(root->right, count);
// }

// int countNodes(TreeNode *root)
// {
//     int count = 0;

//     inOrderTraversal(root, count);

//     return count;
// }

/*
========================================================
OPTIMAL APPROACH

Idea:
- Use the property of a complete binary tree.
- Calculate the height of the leftmost and rightmost paths.
- If both heights are equal, the tree is a perfect binary tree: 
  nodes = 2^height - 1.
- Otherwise, recursively count nodes in left and right subtrees.

Time Complexity: O((log N)^2), where log N is the height of the tree.
Space Complexity: O(log N), due to recursion stack.
========================================================
*/

int findHeight(TreeNode *root, bool goLeft)
{
    int cnt = 0;

    TreeNode *currNode = root;

    while (currNode)
    {
        cnt++;

        currNode = goLeft ? currNode->left : currNode->right;
    }

    return cnt;
}

int countNodes(TreeNode *root)
{
    if (!root)
        return 0;

    int lHeight = findHeight(root, true);

    int rHeight = findHeight(root, false);

    // Complete binary tree is perfect if left and right heights are equal.
    if (lHeight == rHeight)
        return ((1 << lHeight) - 1);

    return 1 + countNodes(root->left) + countNodes(root->right);
}

int main()
{
    TreeNode *root = new TreeNode(1);

    root->left = new TreeNode(2);

    root->right = new TreeNode(3);

    root->left->left = new TreeNode(4);

    root->left->right = new TreeNode(5);

    root->right->left = new TreeNode(6);

    int totalNodes = countNodes(root);

    cout << "Total number of nodes in the Complete Binary Tree: "
         << totalNodes << endl;

    return 0;
}