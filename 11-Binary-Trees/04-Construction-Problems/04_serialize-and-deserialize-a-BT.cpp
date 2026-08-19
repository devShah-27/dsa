// Problem:
// Design an algorithm to serialize and deserialize a binary tree.
// Serialization converts a tree into a string representation, and deserialization reconstructs the original tree structure from that string.

#include <bits/stdc++.h>
using namespace std;

struct TreeNode
{
    int data;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

static void inorder(TreeNode *root)
{
    if (root == nullptr)
    {
        return;
    }

    inorder(root->left);

    cout << root->data << " ";

    inorder(root->right);
}

// ================================================================================
// OPTIMAL APPROACH
//
// Idea:
// - Use level order traversal (BFS) to serialize the tree.
// - Store node values and use "#" as a marker for NULL nodes to preserve structure.
// - During deserialization, recreate nodes level by level using the stored sequence.
// - Queue helps maintain the parent-child relationship while rebuilding the tree.
//
// Time Complexity: O(N), where N is the number of nodes in the tree.
// Space Complexity: O(N) for storing the serialized string and queue.
// ================================================================================

string serialize(TreeNode *root)
{
    if (!root)
        return "";

    string st = "";

    queue<TreeNode *> q;

    q.push(root);

    while (!q.empty())
    {
        TreeNode *currNode = q.front();
        q.pop();

        if (!currNode)
        {
            // Store marker for NULL nodes to preserve tree structure.
            st += "#,";
        }
        else
        {
            // Store current node value and add children for BFS traversal.
            st += to_string(currNode->data) + ",";

            q.push(currNode->left);
            q.push(currNode->right);
        }
    }

    return st;
}

TreeNode *deserialize(string data)
{
    if (data.size() == 0)
        return NULL;

    stringstream s(data);

    string str;

    // First value represents the root node.
    getline(s, str, ',');

    TreeNode *root = new TreeNode(stoi(str));

    queue<TreeNode *> q;

    q.push(root);

    while (!q.empty())
    {
        TreeNode *currNode = q.front();
        q.pop();

        // Construct left child.
        getline(s, str, ',');

        if (str != "#")
        {
            TreeNode *leftNode = new TreeNode(stoi(str));

            currNode->left = leftNode;

            q.push(leftNode);
        }

        // Construct right child.
        getline(s, str, ',');

        if (str != "#")
        {
            TreeNode *rightNode = new TreeNode(stoi(str));

            currNode->right = rightNode;

            q.push(rightNode);
        }
    }

    return root;
}

int main()
{
    TreeNode *root = new TreeNode(1);

    root->left = new TreeNode(2);

    root->right = new TreeNode(3);

    root->right->left = new TreeNode(4);

    root->right->right = new TreeNode(5);

    cout << "Original Tree: ";
    inorder(root);
    cout << endl;

    string serialized = serialize(root);

    cout << "Serialized: " << serialized << endl;

    TreeNode *deserialized = deserialize(serialized);

    cout << "Tree after deserialization: ";
    inorder(deserialized);
    cout << endl;

    return 0;
}