// Problem:
// Given a binary tree, a target node, and an integer k, return all nodes that are exactly k distance away from the target node.
// Nodes can be reached through parent, left child, or right child directions.

#include <bits/stdc++.h>
using namespace std;

struct TreeNode
{
    int data;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

TreeNode *createTree(const vector<int> &nodes, int index = 0)
{
    if (index < nodes.size() && nodes[index] != -1)
    {
        TreeNode *root = new TreeNode(nodes[index]);

        root->left = createTree(nodes, 2 * index + 1);

        root->right = createTree(nodes, 2 * index + 2);

        return root;
    }

    return nullptr;
}

/*
========================================================
PARENT MAPPING + BFS APPROACH

Idea:
- A binary tree does not have parent pointers, so first create a mapping from every node to its parent using BFS.
- Perform another BFS starting from the target node, treating the tree as an undirected graph where nodes can move to left child, right child, or parent.
- Stop BFS after reaching distance k and collect all nodes at that level.

Time Complexity: O(N), where N is the number of nodes.
Space Complexity: O(N), due to parent mapping, visited map, and BFS queue.
========================================================
*/

void getParentNodes(TreeNode *root, unordered_map<TreeNode *, TreeNode *> &parentNode)
{
    queue<TreeNode *> q;

    q.push(root);

    while (!q.empty())
    {
        TreeNode *currNode = q.front();
        q.pop();

        if (currNode->left)
        {
            parentNode[currNode->left] = currNode;
            q.push(currNode->left);
        }

        if (currNode->right)
        {
            parentNode[currNode->right] = currNode;
            q.push(currNode->right);
        }
    }
}

vector<int> distanceK(TreeNode *root, TreeNode *target, int k)
{
    // Step 1: Store parent pointers for every node.
    unordered_map<TreeNode *, TreeNode *> parentNode;

    getParentNodes(root, parentNode);

    // Step 2: Perform BFS from target node.
    queue<TreeNode *> q;

    unordered_map<TreeNode *, bool> visited;

    q.push(target);

    visited[target] = true;

    int currLevel = 0;

    while (!q.empty())
    {
        // All nodes currently in queue are at distance k.
        if (currLevel == k)
            break;

        int n = q.size();

        currLevel++;

        for (int i = 0; i < n; i++)
        {
            TreeNode *currNode = q.front();

            q.pop();

            // Move to left child.
            if (currNode->left && !visited[currNode->left])
            {
                q.push(currNode->left);
                visited[currNode->left] = true;
            }

            // Move to right child.
            if (currNode->right && !visited[currNode->right])
            {
                q.push(currNode->right);
                visited[currNode->right] = true;
            }

            // Move to parent node.
            if (parentNode[currNode] && !visited[parentNode[currNode]])
            {
                q.push(parentNode[currNode]);
                visited[parentNode[currNode]] = true;
            }
        }
    }

    vector<int> res;

    // Remaining nodes in queue are exactly distance k away.
    while (!q.empty())
    {
        res.emplace_back(q.front()->data);

        q.pop();
    }

    return res;
}

int main()
{
    vector<int> nodes = {3, 5, 1, 6, 2, 0, 8, -1, -1, 7, 4};

    TreeNode *root = createTree(nodes);

    TreeNode *target = root->left;

    int k = 2;

    vector<int> result = distanceK(root, target, k);

    cout << "Nodes at distance " << k << " from target node are: ";

    for (int val : result)
    {
        cout << val << " ";
    }

    cout << endl;

    return 0;
}