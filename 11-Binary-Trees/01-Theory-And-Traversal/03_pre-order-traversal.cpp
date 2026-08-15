// Problem:
// Given the root of a binary tree, return the preorder traversal of the tree.
// Preorder traversal visits nodes in the order: Root -> Left Subtree -> Right Subtree.

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
RECURSIVE APPROACH

Idea:
- Use recursion to traverse the tree following the preorder pattern.
- First store the current node value, then recursively traverse
  the left subtree followed by the right subtree.

Time Complexity: O(N), where N is the number of nodes.
Space Complexity: O(N), due to recursion stack in the worst case.
========================================================
*/

// void recursivePreOrderTraversal(TreeNode *root, vector<int> &res)
// {
//     if (root == NULL)
//         return;

//     res.emplace_back(root->data);

//     recursivePreOrderTraversal(root->left, res);

//     recursivePreOrderTraversal(root->right, res);
// }

// vector<int> preorder(TreeNode *root)
// {
//     vector<int> res;
//     recursivePreOrderTraversal(root, res);
//     return res;
// }

/*
========================================================
ITERATIVE APPROACH

Idea:
- Simulate recursive preorder traversal using an explicit stack.
- Since stack follows LIFO order, push the right child before the left child
  so that the left subtree is processed first.
- Process each node when it is removed from the stack.

Time Complexity: O(N), where N is the number of nodes.
Space Complexity: O(N), due to the stack storing nodes.
========================================================
*/

vector<int> preorder(TreeNode *root)
{
    if (!root)
        return {};

    vector<int> res;

    // Stack stores nodes that are yet to be processed.
    stack<TreeNode *> st;

    st.push(root);

    while (!st.empty())
    {
        // Process the current node.
        TreeNode *topNode = st.top();
        st.pop();

        res.emplace_back(topNode->data);

        // Push right child first because stack processes the latest element first.
        if (topNode->right)
            st.push(topNode->right);

        // Push left child after right so it gets processed before the right subtree.
        if (topNode->left)
            st.push(topNode->left);
    }

    return res;
}

int main()
{
    TreeNode *root = new TreeNode(1);

    root->left = new TreeNode(2);
    root->right = new TreeNode(3);

    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    vector<int> result = preorder(root);

    cout << "Preorder Traversal: ";

    for (int val : result)
    {
        cout << val << " ";
    }

    cout << endl;

    return 0;
}