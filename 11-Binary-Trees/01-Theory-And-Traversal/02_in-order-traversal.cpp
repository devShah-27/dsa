// Problem:
// Given the root of a binary tree, return the inorder traversal of the tree.
// Inorder traversal visits nodes in the order: Left Subtree -> Root -> Right Subtree.

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
- Use recursion to traverse the tree following the inorder pattern.
- First visit the left subtree, then store the current node value,
  and finally visit the right subtree.

Time Complexity: O(N), where N is the number of nodes.
Space Complexity: O(N), due to recursion stack in the worst case.
========================================================
*/

// void recursiveInOrderTraversal(TreeNode *root, vector<int> &result)
// {
//     if (root == NULL)
//         return;

//     recursiveInOrderTraversal(root->left, result);

//     result.emplace_back(root->data);

//     recursiveInOrderTraversal(root->right, result);
// }

// vector<int> inorder(TreeNode *root)
// {
//     vector<int> result;
//     recursiveInOrderTraversal(root, result);
//     return result;
// }

/*
========================================================
ITERATIVE APPROACH

Idea:
- Simulate the recursive inorder traversal using an explicit stack.
- Continuously move towards the leftmost node while storing nodes in the stack.
- Once no left child exists, process the node and move to its right subtree.

Time Complexity: O(N), where N is the number of nodes.
Space Complexity: O(N), due to the stack storing nodes.
========================================================
*/

vector<int> inorder(TreeNode *root)
{
    vector<int> result;

    // Stack stores nodes whose left subtree is not completely processed.
    stack<TreeNode *> st;

    TreeNode *temp = root;

    while (true)
    {
        // Move to the leftmost node while storing ancestors.
        if (temp != NULL)
        {
            st.push(temp);
            temp = temp->left;
        }
        else
        {
            // If there are no pending nodes, traversal is complete.
            if (st.empty())
                break;

            // Process the current node and move to the right subtree.
            temp = st.top();
            st.pop();

            result.emplace_back(temp->data);

            temp = temp->right;
        }
    }

    return result;
}

int main()
{
    TreeNode *root = new TreeNode(1);

    root->left = new TreeNode(2);
    root->right = new TreeNode(3);

    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    vector<int> result = inorder(root);

    cout << "Inorder Traversal: ";

    for (int val : result)
    {
        cout << val << " ";
    }

    cout << endl;

    return 0;
}