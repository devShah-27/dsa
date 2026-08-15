// Problem:
// Given the root of a binary tree, return the level order traversal of its nodes' values.
// Traverse the tree level by level from left to right using a breadth-first approach.

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
BREADTH FIRST SEARCH (QUEUE) APPROACH

Idea:
- Use a queue to perform level order traversal.
- Store all nodes of the current level, then add their children
  to the queue for processing in the next level.
- The queue naturally maintains the left-to-right order.

Time Complexity: O(N), where N is the number of nodes.
Space Complexity: O(N), due to the queue storing nodes.
========================================================
*/

vector<vector<int>> levelOrder(TreeNode *root)
{
    vector<vector<int>> result;

    if (!root)
        return result;

    // Queue stores nodes waiting to be processed level by level.
    queue<TreeNode *> q;

    q.push(root);

    while (!q.empty())
    {
        vector<int> levelList;

        // Number of nodes present in the current level.
        int size = q.size();

        for (int i = 0; i < size; i++)
        {
            TreeNode *currNode = q.front();
            q.pop();

            levelList.emplace_back(currNode->data);

            // Add children for the next level.
            if (currNode->left)
                q.push(currNode->left);

            if (currNode->right)
                q.push(currNode->right);
        }

        result.emplace_back(levelList);
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

    vector<vector<int>> result = levelOrder(root);

    cout << "Level Order Traversal of Tree: " << endl;

    for (const vector<int> &level : result)
    {
        printVector(level);
    }

    return 0;
}