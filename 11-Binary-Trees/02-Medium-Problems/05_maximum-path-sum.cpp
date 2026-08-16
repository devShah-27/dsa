// Problem:
// Given the root of a binary tree, find the maximum path sum among all possible non-empty paths.
// A path can start and end at any node but cannot visit any node more than once.

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
OPTIMAL APPROACH (POSTORDER TRAVERSAL)

Idea:
- Use postorder traversal to calculate the maximum contribution of each subtree.
- Ignore negative subtree contributions because they decrease the path sum.
- For every node, calculate the maximum path passing through it:
  left contribution + node value + right contribution.
- Maintain the global maximum path sum while returning the best single-side contribution.

Time Complexity: O(N), where N is the number of nodes.
Space Complexity: O(N), due to recursion stack in the worst case.
========================================================
*/

int maxSum(TreeNode *root, int &maxi)
{
    if (!root)
        return 0;

    // Negative contributions are ignored as they reduce the path sum.
    int lMax = max(0, maxSum(root->left, maxi));

    int rMax = max(0, maxSum(root->right, maxi));

    // Maximum path passing through the current node.
    maxi = max(maxi, lMax + rMax + root->data);

    // Return maximum contribution that can be extended to the parent.
    return max(lMax, rMax) + root->data;
}

int maxPathSum(TreeNode *root)
{
    int maxi = INT_MIN;

    maxSum(root, maxi);

    return maxi;
}

int main()
{
    TreeNode *root = new TreeNode(1);

    root->left = new TreeNode(2);
    root->right = new TreeNode(3);

    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    root->left->right->right = new TreeNode(6);
    root->left->right->right->right = new TreeNode(7);

    int maxPathSumVal = maxPathSum(root);

    cout << "Maximum Path Sum: " << maxPathSumVal << endl;

    return 0;
}