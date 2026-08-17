// Problem:
// Given the root of a binary tree, return its boundary traversal in anticlockwise order.
// Boundary traversal consists of root, left boundary, all leaf nodes, and reversed right boundary.

#include <bits/stdc++.h>
using namespace std;

struct TreeNode
{
    int data;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

void printResult(const vector<int> &result)
{
    for (int val : result)
    {
        cout << val << " ";
    }

    cout << endl;
}

/*
========================================================
BOUNDARY TRAVERSAL APPROACH

Idea:
- Traverse the tree boundary in four parts:
  1. Add root node.
  2. Add left boundary excluding leaf nodes.
  3. Add all leaf nodes from left to right.
  4. Add right boundary in reverse order excluding leaf nodes.
- This ensures every boundary node is visited exactly once.

Time Complexity: O(N), where N is the number of nodes.
Space Complexity: O(H), due to recursion stack for leaf traversal.
========================================================
*/

// Checks whether the current node is a leaf node.
bool isLeaf(TreeNode *root)
{
    return !root->left && !root->right;
}

// Adds left boundary nodes excluding leaf nodes.
void leftBoundaryTraversal(TreeNode *root, vector<int> &res)
{
    TreeNode *currNode = root->left;

    while (currNode)
    {
        if (!isLeaf(currNode))
            res.push_back(currNode->data);

        // Prefer left child, otherwise move to right child.
        if (currNode->left)
            currNode = currNode->left;
        else
            currNode = currNode->right;
    }
}

// Adds all leaf nodes from left to right.
void leafNodeTraversal(TreeNode *root, vector<int> &res)
{
    if (!root)
        return;

    if (isLeaf(root))
    {
        res.push_back(root->data);
        return;
    }

    leafNodeTraversal(root->left, res);

    leafNodeTraversal(root->right, res);
}

// Adds right boundary nodes in reverse order excluding leaf nodes.
void rightBoundaryTraversal(TreeNode *root, vector<int> &res)
{
    TreeNode *currNode = root->right;

    vector<int> temp;

    while (currNode)
    {
        if (!isLeaf(currNode))
            temp.push_back(currNode->data);

        // Prefer right child, otherwise move to left child.
        if (currNode->right)
            currNode = currNode->right;
        else
            currNode = currNode->left;
    }

    // Reverse right boundary to maintain anticlockwise order.
    int n = temp.size();

    for (int i = n - 1; i >= 0; i--)
    {
        res.push_back(temp[i]);
    }
}

vector<int> boundary(TreeNode *root)
{
    if (!root)
        return {};

    // Single node tree: root itself is the complete boundary.
    if (isLeaf(root))
        return {root->data};

    vector<int> res;

    // Add root node first.
    res.push_back(root->data);

    leftBoundaryTraversal(root, res);

    leafNodeTraversal(root, res);

    rightBoundaryTraversal(root, res);

    return res;
}

int main()
{
    TreeNode *root = new TreeNode(1);

    root->left = new TreeNode(2);
    root->right = new TreeNode(3);

    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);

    vector<int> result = boundary(root);

    cout << "Boundary Traversal: ";

    printResult(result);

    return 0;
}