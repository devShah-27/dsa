// Problem:
// Given the root of a binary tree, return its maximum depth.
// Maximum depth is the number of nodes present in the longest path from root to any leaf node.

#include <bits/stdc++.h>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/*
========================================================
RECURSIVE APPROACH

Idea:
- Recursively calculate the depth of the left and right subtrees.
- The maximum depth of the current node is 1 + maximum depth
  of its two children.

Time Complexity: O(N), where N is the number of nodes.
Space Complexity: O(N), due to recursion stack in the worst case.
========================================================
*/

// int maxDepth(TreeNode *root)
// {
//     if (!root)
//         return 0;

//     int leftDepth = maxDepth(root->left);
//     int rightDepth = maxDepth(root->right);

//     return 1 + max(leftDepth, rightDepth);
// }

/*
========================================================
ITERATIVE APPROACH (LEVEL ORDER TRAVERSAL)

Idea:
- Use BFS traversal using a queue.
- Each level of the tree increases the depth count by one.
- Continue processing levels until all nodes are visited.

Time Complexity: O(N), where N is the number of nodes.
Space Complexity: O(N), due to the queue storing nodes.
========================================================
*/

int maxDepth(TreeNode *root)
{
    if (!root)
        return 0;

    int maxDepth = 0;

    queue<TreeNode *> q;

    q.push(root);

    while (!q.empty())
    {
        // Number of nodes present at the current level.
        int n = q.size();

        maxDepth++;

        for (int i = 0; i < n; i++)
        {
            TreeNode *currNode = q.front();
            q.pop();

            // Add children for the next level.
            if (currNode->left)
                q.push(currNode->left);

            if (currNode->right)
                q.push(currNode->right);
        }
    }

    return maxDepth;
}

int main()
{
    // Creating a sample binary tree.
    TreeNode *root = new TreeNode(1);

    root->left = new TreeNode(2);
    root->right = new TreeNode(3);

    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    cout << "Maximum Depth: " << maxDepth(root) << endl;

    return 0;
}