// Problem:
// Given the root of a binary tree, return the postorder traversal of the tree.
// Postorder traversal visits nodes in the order: Left Subtree -> Right Subtree -> Root.

#include <bits/stdc++.h>
using namespace std;

struct TreeNode
{
    int data;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

void printVector(const vector<int> &vec)
{
    for (int num : vec)
    {
        cout << num << " ";
    }

    cout << endl;
}

/*
========================================================
RECURSIVE APPROACH

Idea:
- Use recursion to traverse the tree following the postorder pattern.
- First visit the left subtree, then the right subtree,
  and finally store the current node value.

Time Complexity: O(N), where N is the number of nodes.
Space Complexity: O(N), due to recursion stack in the worst case.
========================================================
*/

// void recursivePostOrderTraversal(TreeNode *root, vector<int> &res)
// {
//     if (root == NULL)
//         return;

//     recursivePostOrderTraversal(root->left, res);

//     recursivePostOrderTraversal(root->right, res);

//     res.emplace_back(root->data);
// }

// vector<int> postorder(TreeNode *root)
// {
//     vector<int> res;
//     recursivePostOrderTraversal(root, res);

//     return res;
// }

/*
========================================================
ITERATIVE APPROACH

Idea:
- Use a stack to simulate the traversal process.
- Perform a modified preorder traversal: Root -> Right -> Left.
- Reverse the generated order to obtain the required postorder traversal:
  Left -> Right -> Root.

Time Complexity: O(N), where N is the number of nodes.
Space Complexity: O(N), due to the stack storing nodes.
========================================================
*/

vector<int> postorder(TreeNode *root)
{
    vector<int> res;

    stack<TreeNode *> st;

    st.push(root);

    while (!st.empty())
    {
        TreeNode *currNode = st.top();
        st.pop();

        res.emplace_back(currNode->data);

        // Push left child first so right child is processed first.
        if (currNode->left)
            st.push(currNode->left);

        if (currNode->right)
            st.push(currNode->right);
    }

    // Convert Root -> Right -> Left into Left -> Right -> Root.
    reverse(res.begin(), res.end());

    return res;
}

int main()
{
    TreeNode *root = new TreeNode(1);

    root->left = new TreeNode(2);
    root->right = new TreeNode(3);

    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    vector<int> result = postorder(root);

    cout << "Postorder traversal: ";
    printVector(result);

    return 0;
}