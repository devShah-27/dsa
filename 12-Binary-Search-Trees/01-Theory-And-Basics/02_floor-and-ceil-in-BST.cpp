// Problem:
// Given a Binary Search Tree (BST) and a key, find the floor and ceil values of the key.
// Floor = greatest value in the BST that is <= key.
// Ceil = smallest value in the BST that is >= key. Return -1 if either value does not exist.

#include <bits/stdc++.h>
using namespace std;

class TreeNode
{
public:
    int data;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

TreeNode *insert(TreeNode *node, int key)
{
    if (node == nullptr)
        return new TreeNode(key);

    if (key < node->data)
        node->left = insert(node->left, key);
    else if (key > node->data)
        node->right = insert(node->right, key);

    return node;
}

// ================================================================================
// FLOOR — ITERATIVE BST SEARCH
//
// Idea:
// - If current value == key, it is the exact floor.
// - If current value > key, it cannot be the floor, so move left.
// - If current value < key, it is a valid floor candidate; store it and move right
//   to search for a larger valid value.
//
// Time Complexity: O(H), where H is the height of the BST.
// Space Complexity: O(1), using constant extra space.
// ================================================================================

int getFloor(TreeNode *root, int key)
{
    int floor = -1;

    while (root)
    {
        if (root->data == key)
        {
            floor = root->data;
            break;
        }

        if (root->data > key)
        {
            root = root->left;
        }
        else
        {
            floor = root->data;
            root = root->right;
        }
    }

    return floor;
}

// ================================================================================
// CEIL — ITERATIVE BST SEARCH
//
// Idea:
// - If current value == key, it is the exact ceil.
// - If current value < key, it cannot be the ceil, so move right.
// - If current value > key, it is a valid ceil candidate; store it and move left
//   to search for a smaller valid value.
//
// Time Complexity: O(H), where H is the height of the BST.
// Space Complexity: O(1), using constant extra space.
// ================================================================================

int getCeil(TreeNode *root, int key)
{
    int ceil = -1;

    while (root)
    {
        if (root->data == key)
        {
            ceil = root->data;
            break;
        }

        if (root->data < key)
        {
            root = root->right;
        }
        else
        {
            ceil = root->data;
            root = root->left;
        }
    }

    return ceil;
}

// ================================================================================
// FLOOR + CEIL OF BST
//
// Idea:
// - Independently find the floor and ceil using the BST property.
// - Return both values in the order: {floor, ceil}.
//
// Time Complexity: O(H), where H is the height of the BST.
// Space Complexity: O(1), excluding the returned vector.
// ================================================================================

vector<int> floorCeilOfBST(TreeNode *root, int key)
{
    return {getFloor(root, key), getCeil(root, key)};
}

int main()
{
    TreeNode *root = nullptr;

    root = insert(root, 8);
    insert(root, 4);
    insert(root, 12);
    insert(root, 2);
    insert(root, 6);
    insert(root, 10);
    insert(root, 14);

    int key = 11;

    vector<int> result = floorCeilOfBST(root, key);

    cout << "Floor: " << result[0] << ", Ceil: " << result[1] << endl;

    return 0;
}