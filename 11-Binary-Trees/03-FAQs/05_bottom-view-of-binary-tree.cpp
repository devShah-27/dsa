// Problem:
// Given the root of a binary tree, return the bottom view of the tree.
// The bottom view contains the last visible node at each horizontal distance, ordered from the leftmost distance to the rightmost distance.

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
BFS + MAP APPROACH

Idea:
- Assign a horizontal distance to every node:
  - Root has horizontal distance 0.
  - Left child decreases distance by 1.
  - Right child increases distance by 1.
- Perform level order traversal using a queue.
- For every horizontal distance, keep updating the value with the latest visited node because it will be the bottommost node.
- BFS ensures that when multiple nodes share the same position, the node appearing later in level order is stored.

Time Complexity: O(N * log(N)), due to map operations.
Space Complexity: O(N), due to queue and map storage.
========================================================
*/

vector<int> bottomView(TreeNode *root)
{
    if (!root)
        return {};

    vector<int> res;

    // Stores horizontal distance -> bottommost node value.
    map<int, int> nodeMap;

    // Stores node along with its horizontal distance.
    queue<pair<TreeNode *, int>> q;

    // Root starts at horizontal distance 0.
    q.push({root, 0});

    while (!q.empty())
    {
        auto currPair = q.front();
        q.pop();

        TreeNode *currNode = currPair.first;

        int vertical = currPair.second;

        // Always update because the latest node at this distance is visible from bottom.
        nodeMap[vertical] = currNode->data;

        // Move left with horizontal distance -1.
        if (currNode->left)
            q.push({currNode->left, vertical - 1});

        // Move right with horizontal distance +1.
        if (currNode->right)
            q.push({currNode->right, vertical + 1});
    }

    // Map stores horizontal distances in sorted order.
    for (auto vertical : nodeMap)
    {
        res.push_back(vertical.second);
    }

    return res;
}

int main()
{
    // Creating a sample binary tree.
    TreeNode *root = new TreeNode(1);

    root->left = new TreeNode(2);

    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(10);

    root->left->left->right = new TreeNode(5);
    root->left->left->right->right = new TreeNode(6);

    root->right = new TreeNode(3);

    root->right->right = new TreeNode(10);
    root->right->left = new TreeNode(9);

    vector<int> bottomViewList = bottomView(root);

    cout << "Bottom View Traversal: " << endl;

    for (auto node : bottomViewList)
    {
        cout << node << " ";
    }

    return 0;
}