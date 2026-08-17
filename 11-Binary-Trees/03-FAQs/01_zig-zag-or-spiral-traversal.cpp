// Problem:
// Given the root of a binary tree, return its zigzag level order traversal.
// Traverse levels alternately from left to right and right to left.

#include <bits/stdc++.h>
using namespace std;

struct TreeNode
{
    int data;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

void printResult(const vector<vector<int>> &result)
{
    for (const auto &row : result)
    {
        for (int val : row)
        {
            cout << val << " ";
        }

        cout << endl;
    }
}

/*
========================================================
BREADTH FIRST SEARCH (QUEUE) APPROACH

Idea:
- Use level order traversal with a queue to process nodes level by level.
- Store each level's values in a temporary array.
- Based on the traversal direction, place values either from left to right
  or from right to left using index manipulation.

Time Complexity: O(N), where N is the number of nodes.
Space Complexity: O(N), due to the queue storing nodes.
========================================================
*/

vector<vector<int>> zigzagLevelOrder(TreeNode *root)
{
    if (!root)
        return {};

    vector<vector<int>> result;

    // Queue stores nodes for level order traversal.
    queue<TreeNode *> q;

    q.push(root);

    // Controls the direction of insertion for each level.
    bool leftToRight = true;

    while (!q.empty())
    {
        int n = q.size();

        vector<int> levelList(n);

        for (int i = 0; i < n; i++)
        {
            TreeNode *currNode = q.front();
            q.pop();

            // Place values according to current traversal direction.
            int idx = leftToRight ? i : n - i - 1;

            levelList[idx] = currNode->data;

            // Add children for the next level.
            if (currNode->left)
                q.push(currNode->left);

            if (currNode->right)
                q.push(currNode->right);
        }

        result.push_back(levelList);

        // Reverse direction for the next level.
        leftToRight = !leftToRight;
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

    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);

    vector<vector<int>> result = zigzagLevelOrder(root);

    printResult(result);

    return 0;
}