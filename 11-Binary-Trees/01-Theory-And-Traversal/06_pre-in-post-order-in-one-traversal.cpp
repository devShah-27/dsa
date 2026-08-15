// Problem:
// Given the root of a binary tree, return its preorder, inorder, and postorder traversals.
// Perform all three traversals in a single traversal using an iterative approach.

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
ITERATIVE APPROACH USING SINGLE STACK

Idea:
- Use a stack storing pairs of (node, state) to simulate recursive traversal.
- State 1: Process node in preorder, then move to the left subtree.
- State 2: Process node in inorder, then move to the right subtree.
- State 3: Process node in postorder after both subtrees are completed.

Time Complexity: O(N), where N is the number of nodes.
Space Complexity: O(N), due to the stack storing nodes.
========================================================
*/

vector<vector<int>> treeTraversal(TreeNode *root)
{
    if (!root)
        return {{}};

    vector<int> pre, in, post;

    // Stack stores the node and its current traversal state.
    stack<pair<TreeNode *, int>> st;

    // State 1 represents the first visit to the node.
    st.push({root, 1});

    while (!st.empty())
    {
        auto topElem = st.top();
        st.pop();

        TreeNode *currNode = topElem.first;
        int state = topElem.second;

        // First visit: Preorder -> Root, Left, Right.
        if (state == 1)
        {
            pre.emplace_back(currNode->data);

            // Move to inorder state after processing left subtree.
            topElem.second = 2;
            st.push(topElem);

            if (currNode->left)
                st.push({currNode->left, 1});
        }

        // Second visit: Inorder -> Left, Root, Right.
        else if (state == 2)
        {
            in.emplace_back(currNode->data);

            // Move to postorder state after processing right subtree.
            topElem.second = 3;
            st.push(topElem);

            if (currNode->right)
                st.push({currNode->right, 1});
        }

        // Third visit: Postorder -> Left, Right, Root.
        else
        {
            post.emplace_back(currNode->data);
        }
    }

    return {pre, in, post};
}

int main()
{
    TreeNode *root = new TreeNode(1);

    root->left = new TreeNode(2);
    root->right = new TreeNode(3);

    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    vector<vector<int>> traversals = treeTraversal(root);

    cout << "Preorder traversal: ";
    for (int val : traversals[0])
        cout << val << " ";
    cout << endl;

    cout << "Inorder traversal: ";
    for (int val : traversals[1])
        cout << val << " ";
    cout << endl;

    cout << "Postorder traversal: ";
    for (int val : traversals[2])
        cout << val << " ";
    cout << endl;

    return 0;
}