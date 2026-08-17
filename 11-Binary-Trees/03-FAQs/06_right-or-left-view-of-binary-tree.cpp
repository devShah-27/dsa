// Problem:
// Given the root of a binary tree, return the nodes visible from the left and right sides.
// The visible nodes are arranged from top to bottom, with one node selected from each level.

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
- Perform level order traversal using BFS.
- For the right view, select the last node of every level.
- For the left view, select the first node of every level.

Time Complexity: O(N), where N is the number of nodes.
Space Complexity: O(N), due to storing the level order traversal.
========================================================
*/

// vector<vector<int>> levelOrderTraversal(TreeNode *root)
// {
//     queue<TreeNode *> q;

//     q.push(root);

//     vector<vector<int>> res;

//     while (!q.empty())
//     {
//         int n = q.size();

//         vector<int> levelList;

//         for (int i = 0; i < n; i++)
//         {
//             TreeNode *currNode = q.front();
//             q.pop();

//             levelList.emplace_back(currNode->data);

//             if (currNode->left)
//                 q.push(currNode->left);

//             if (currNode->right)
//                 q.push(currNode->right);
//         }

//         res.emplace_back(levelList);
//     }

//     return res;
// }

// vector<int> rightSideView(TreeNode *root)
// {
//     if (!root)
//         return {};

//     vector<vector<int>> levelOrder = levelOrderTraversal(root);

//     vector<int> res;

//     // Last node of every level is visible from the right side.
//     for (vector<int> levelList : levelOrder)
//     {
//         res.emplace_back(levelList.back());
//     }

//     return res;
// }

// vector<int> leftSideView(TreeNode *root)
// {
//     if (!root)
//         return {};

//     vector<vector<int>> levelOrder = levelOrderTraversal(root);

//     vector<int> res;

//     // First node of every level is visible from the left side.
//     for (vector<int> levelList : levelOrder)
//     {
//         res.emplace_back(levelList.front());
//     }

//     return res;
// }

/*
========================================================
OPTIMAL APPROACH

Idea:
- Use DFS traversal while keeping track of the current level.
- Store the first node encountered at every level.
- For the right view, visit the right subtree before the left subtree.
- For the left view, visit the left subtree before the right subtree.

Time Complexity: O(N), where N is the number of nodes.
Space Complexity: O(H), due to recursion stack, where H is the height of the tree.
========================================================
*/

// Right View: Root -> Right -> Left traversal.
void rightSideViewHelper(TreeNode *root, vector<int> &helperList, int level)
{
    if (!root)
        return;

    // First node encountered at this level is visible from the right side.
    if (level == helperList.size())
        helperList.emplace_back(root->data);

    rightSideViewHelper(root->right, helperList, level + 1);

    rightSideViewHelper(root->left, helperList, level + 1);
}

vector<int> rightSideView(TreeNode *root)
{
    if (!root)
        return {};

    vector<int> helperList;

    rightSideViewHelper(root, helperList, 0);

    return helperList;
}

// Left View: Root -> Left -> Right traversal.
void leftSideViewHelper(TreeNode *root, vector<int> &helperList, int level)
{
    if (!root)
        return;

    // First node encountered at this level is visible from the left side.
    if (level == helperList.size())
        helperList.emplace_back(root->data);

    leftSideViewHelper(root->left, helperList, level + 1);

    leftSideViewHelper(root->right, helperList, level + 1);
}

vector<int> leftSideView(TreeNode *root)
{
    if (!root)
        return {};

    vector<int> helperList;

    leftSideViewHelper(root, helperList, 0);

    return helperList;
}

int main()
{
    TreeNode *root = new TreeNode(1);

    root->left = new TreeNode(2);

    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(10);

    root->left->left->right = new TreeNode(5);
    root->left->left->right->right = new TreeNode(6);

    root->right = new TreeNode(3);

    root->right->right = new TreeNode(10);
    root->right->left = new TreeNode(9);

    vector<int> rightView = rightSideView(root);

    cout << "Right View Traversal: ";

    for (auto node : rightView)
    {
        cout << node << " ";
    }

    cout << endl;

    vector<int> leftView = leftSideView(root);

    cout << "Left View Traversal: ";

    for (auto node : leftView)
    {
        cout << node << " ";
    }

    cout << endl;

    return 0;
}