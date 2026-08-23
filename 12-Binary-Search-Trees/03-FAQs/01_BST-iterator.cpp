// Problem:
// Implement a BST iterator that returns nodes in inorder (ascending) order.
// next() returns the next smallest value, and hasNext() checks whether another value exists.
// The iterator should use O(H) auxiliary space, where H is the height of the BST.

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
// BRUTE FORCE APPROACH — STORE COMPLETE INORDER TRAVERSAL
//
// Idea:
// - Perform a complete inorder traversal during construction.
// - Store all node values in a vector, which gives the sorted BST order.
// - next() simply returns the current value and moves the index forward.
//
// Time Complexity: O(N) initialization, O(1) per next() and hasNext() call.
// Space Complexity: O(N) for storing the complete inorder traversal.
// ================================================================================

// class BSTIterator
// {
//     vector<int> v;
//     int idx = 0;

// private:
//     void storeInorder(TreeNode *root, vector<int> &v)
//     {
//         if (!root)
//             return;

//         storeInorder(root->left, v);
//         v.push_back(root->data);
//         storeInorder(root->right, v);
//     }

// public:
//     BSTIterator(TreeNode *root)
//     {
//         storeInorder(root, v);
//     }

//     bool hasNext()
//     {
//         return idx < v.size();
//     }

//     int next()
//     {
//         if (idx >= v.size())
//             return -1;

//         return v[idx++];
//     }
// };

// ================================================================================
// OPTIMAL APPROACH — CONTROLLED INORDER TRAVERSAL
//
// Idea:
// - Use a stack to simulate inorder traversal without storing the entire traversal.
// - Initially push the complete left path from the root onto the stack.
// - next() pops the smallest available node, then pushes the left path of its right subtree.
// - Each node is pushed and popped exactly once across the complete traversal.
//
// Time Complexity: O(H) initialization, O(1) amortized per next() call, and O(1) per hasNext() call.
// Space Complexity: O(H), where H is the height of the BST.
// ================================================================================

class BSTIterator
{
    stack<TreeNode *> st;

private:
    // Push the complete left path starting from the given node.
    void pushAll(TreeNode *node)
    {
        while (node)
        {
            st.push(node);
            node = node->left;
        }
    }

public:
    BSTIterator(TreeNode *root)
    {
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

        // After visiting a node, its right subtree is next in inorder.
        pushAll(topNode->right);

        return topNode->data;
    }
};

int main()
{
    TreeNode *root = new TreeNode(7);
    root->left = new TreeNode(3);
    root->right = new TreeNode(15);
    root->right->left = new TreeNode(9);
    root->right->right = new TreeNode(20);

    BSTIterator *iterator = new BSTIterator(root);

    while (iterator->hasNext())
    {
        cout << iterator->next() << " ";
    }

    // Output: 3 7 9 15 20

    return 0;
}