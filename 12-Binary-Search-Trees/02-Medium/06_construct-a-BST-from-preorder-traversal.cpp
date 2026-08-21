// Problem:
// Given the preorder traversal of a BST, construct the corresponding BST.
// The input is guaranteed to represent a valid BST.
// Return the root of the constructed BST.

#include <bits/stdc++.h>
using namespace std;

struct TreeNode
{
    int data;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

void inorderTraversal(TreeNode *root)
{
    if (root != nullptr)
    {
        inorderTraversal(root->left);
        cout << root->data << " ";
        inorderTraversal(root->right);
    }
}

// ================================================================================
// BRUTE FORCE APPROACH — INSERT EACH PREORDER VALUE
//
// Idea:
// - The first preorder value becomes the root of the BST.
// - Insert every remaining value into the BST using standard BST insertion.
// - This directly constructs a BST whose preorder traversal matches the input.
//
// Time Complexity: O(N * H) in the worst case, where H is the BST height.
//                  Worst case: O(N^2) for a skewed BST.
// Space Complexity: O(N) for the created tree, excluding the recursion stack.
// ================================================================================

// void insertElement(TreeNode *root, int elem)
// {
//     TreeNode *temp = root;

//     while (true)
//     {
//         if (elem < temp->data)
//         {
//             if (temp->left)
//             {
//                 temp = temp->left;
//             }
//             else
//             {
//                 temp->left = new TreeNode(elem);
//                 break;
//             }
//         }
//         else
//         {
//             if (temp->right)
//                 temp = temp->right;
//             else
//             {
//                 temp->right = new TreeNode(elem);
//                 break;
//             }
//         }
//     }
// }

// TreeNode *bstFromPreorder(vector<int> &preorder)
// {
//     int n = preorder.size();

//     if (n == 0)
//         return nullptr;

//     TreeNode *root = new TreeNode(preorder[0]);

//     for (int i = 1; i < n; i++)
//     {
//         insertElement(root, preorder[i]);
//     }

//     return root;
// }

// ================================================================================
// BETTER APPROACH — PREORDER + SORTED INORDER
//
// Idea:
// - The inorder traversal of a BST is the sorted order of its values.
// - Sort a copy of the preorder array to obtain the inorder traversal.
// - Construct the tree using the standard preorder + inorder construction method.
// - A hash map stores each inorder value's index for O(1) average lookup.
//
// Time Complexity: O(N log N) due to sorting the inorder array.
// Space Complexity: O(N) for the inorder array, hash map, and constructed tree.
// ================================================================================

// void fillInorderMap(vector<int> &inorder, unordered_map<int, int> &inorderMap)
// {
//     for (int i = 0; i < inorder.size(); i++)
//     {
//         inorderMap[inorder[i]] = i;
//     }
// }

// TreeNode *createBST(
//     vector<int> &preorder,
//     vector<int> &inorder,
//     unordered_map<int, int> &inorderMap,
//     int &preIdx,
//     int start,
//     int end)
// {
//     if (start > end)
//         return nullptr;

//     TreeNode *root = new TreeNode(preorder[preIdx]);

//     int inIdx = inorderMap[preorder[preIdx++]];

//     root->left = createBST(
//         preorder,
//         inorder,
//         inorderMap,
//         preIdx,
//         start,
//         inIdx - 1);

//     root->right = createBST(
//         preorder,
//         inorder,
//         inorderMap,
//         preIdx,
//         inIdx + 1,
//         end);

//     return root;
// }

// TreeNode *bstFromPreorder(vector<int> &preorder)
// {
//     int n = preorder.size();

//     if (n == 0)
//         return nullptr;

//     vector<int> inorder;

//     for (int it : preorder)
//     {
//         inorder.push_back(it);
//     }

//     sort(inorder.begin(), inorder.end());

//     unordered_map<int, int> inorderMap;

//     fillInorderMap(inorder, inorderMap);

//     int preIdx = 0;

//     return createBST(
//         preorder,
//         inorder,
//         inorderMap,
//         preIdx,
//         0,
//         inorder.size() - 1);
// }

// ================================================================================
// OPTIMAL APPROACH — PREORDER + UPPER BOUND
//
// Idea:
// - In preorder, the first value within a valid range is the current subtree's root.
// - Maintain an upper bound representing the maximum value allowed in the subtree.
// - After creating the root, recursively build its left subtree with root->data as
//   the new bound, then build its right subtree using the previous bound.
// - If the next value exceeds the current bound, it belongs to an ancestor's subtree,
//   so stop and return nullptr without consuming that value.
//
// Time Complexity: O(N), as every value is processed exactly once.
// Space Complexity: O(H) for the recursive call stack, where H is the tree height.
// ================================================================================

TreeNode *helper(vector<int> &preorder, int &preIdx, int bound)
{
    if (preIdx == preorder.size() || preorder[preIdx] > bound)
        return nullptr;

    TreeNode *root = new TreeNode(preorder[preIdx++]);

    root->left = helper(preorder, preIdx, root->data);
    root->right = helper(preorder, preIdx, bound);

    return root;
}

TreeNode *bstFromPreorder(vector<int> &preorder)
{
    int n = preorder.size();

    if (n == 0)
        return nullptr;

    int preIdx = 0;

    return helper(preorder, preIdx, INT_MAX);
}

int main()
{
    vector<int> preorder = {8, 5, 1, 7, 10, 12};

    TreeNode *root = bstFromPreorder(preorder);

    inorderTraversal(root);

    return 0;
}