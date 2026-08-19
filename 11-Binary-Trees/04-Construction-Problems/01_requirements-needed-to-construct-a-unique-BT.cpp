// Problem:
// Given a pair of binary tree traversals, determine whether a unique binary tree can be constructed. Traversal types: 1 = Preorder, 2 = Inorder, 3 = Postorder.

// ================================================================================
// OPTIMAL APPROACH
//
// Idea:
// - A unique binary tree can be constructed from Inorder + Preorder or Inorder + Postorder traversals.
// - Preorder + Postorder alone cannot uniquely determine a binary tree in general.
// - Therefore, exactly one of the two traversals must be Inorder.
//
// Time Complexity: O(1)
// Space Complexity: O(1)
// ================================================================================

#include <bits/stdc++.h>
using namespace std;

bool uniqueBinaryTree(int a, int b)
{
    return (a == 2 || b == 2) && a != b;
}

int main()
{
    cout << uniqueBinaryTree(1, 2) << endl;
    cout << uniqueBinaryTree(1, 3) << endl;

    return 0;
}