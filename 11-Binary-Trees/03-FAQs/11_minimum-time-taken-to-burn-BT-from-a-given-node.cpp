// Problem:
// Given the root of a binary tree and a target node, determine the minimum time required to burn the entire tree when fire spreads to connected nodes (left child, right child, and parent) every second.

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
PARENT MAPPING + BFS APPROACH

Idea:
- Perform BFS traversal to create parent pointers for every node.
- During the same traversal, find the node where the fire starts.
- Treat the tree as an undirected graph and perform BFS from the target node.
- Every BFS level represents one second, as fire spreads to all connected nodes.

Time Complexity: O(N), where N is the number of nodes.
Space Complexity: O(N), due to parent mapping, visited map, and BFS queue.
========================================================
*/

TreeNode *getParentAndStartNode(TreeNode *root, unordered_map<TreeNode *, TreeNode *> &parentNode, int start)
{
    queue<TreeNode *> q;

    q.push(root);

    TreeNode *res = NULL;

    while (!q.empty())
    {
        TreeNode *currNode = q.front();

        q.pop();

        // Store the starting node reference.
        if (currNode->data == start)
            res = currNode;

        // Store parent relationship for left child.
        if (currNode->left)
        {
            parentNode[currNode->left] = currNode;

            q.push(currNode->left);
        }

        // Store parent relationship for right child.
        if (currNode->right)
        {
            parentNode[currNode->right] = currNode;

            q.push(currNode->right);
        }
    }

    return res;
}

int timeToBurnTree(TreeNode *root, int start)
{
    if (!root)
        return 0;

    // Stores parent references for upward movement.
    unordered_map<TreeNode *, TreeNode *> parentNode;

    // Create parent mapping and find the starting node.
    TreeNode *startNode = getParentAndStartNode(root, parentNode, start);

    queue<TreeNode *> q;

    q.push(startNode);

    // Keeps track of already burned nodes.
    unordered_map<TreeNode *, bool> visited;

    visited[startNode] = true;

    int timeToBurn = 0;

    while (!q.empty())
    {
        int n = q.size();

        bool burnedNewNodes = false;

        // Process all nodes burning at the current second.
        for (int i = 0; i < n; i++)
        {
            TreeNode *currNode = q.front();

            q.pop();

            // Spread fire to left child.
            if (currNode->left && !visited[currNode->left])
            {
                burnedNewNodes = true;

                q.push(currNode->left);

                visited[currNode->left] = true;
            }

            // Spread fire to right child.
            if (currNode->right && !visited[currNode->right])
            {
                burnedNewNodes = true;

                q.push(currNode->right);

                visited[currNode->right] = true;
            }

            // Spread fire to parent node.
            if (parentNode[currNode] && !visited[parentNode[currNode]])
            {
                burnedNewNodes = true;

                q.push(parentNode[currNode]);

                visited[parentNode[currNode]] = true;
            }
        }

        // Increment time only when fire spreads to new nodes.
        if (burnedNewNodes)
            timeToBurn++;
    }

    return timeToBurn;
}

int main()
{
    vector<TreeNode *> nodes(1024);

    for (int i = 1; i <= 1023; i++)
    {
        nodes[i] = new TreeNode(i);
    }

    for (int i = 1; i <= 511; i++)
    {
        nodes[i]->left = nodes[2 * i];

        nodes[i]->right = nodes[2 * i + 1];
    }

    TreeNode *root = nodes[1];

    int start = 1023;

    int result = timeToBurnTree(root, start);

    cout << "Start: " << start
         << " | Time to burn tree: "
         << result << endl;

    start = 1;

    result = timeToBurnTree(root, start);

    cout << "Start: " << start
         << " | Time to burn tree: "
         << result << endl;

    start = 100;

    result = timeToBurnTree(root, start);

    cout << "Start: " << start
         << " | Time to burn tree: "
         << result << endl;

    start = 7;

    result = timeToBurnTree(root, start);

    cout << "Start: " << start
         << " | Time to burn tree: "
         << result << endl;

    start = 900;

    result = timeToBurnTree(root, start);

    cout << "Start: " << start
         << " | Time to burn tree: "
         << result << endl;

    return 0;
}