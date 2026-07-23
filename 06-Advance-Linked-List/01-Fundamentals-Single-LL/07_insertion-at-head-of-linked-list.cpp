// Problem:
// Given the head of a singly linked list and an integer X, insert a new node with value X at the beginning of the linked list and return the new head.

#include <bits/stdc++.h>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;

    // Constructor to initialize node value.
    ListNode(int data1)
    {
        val = data1;
        next = NULL;
    }

    // Constructor to initialize node value and next pointer.
    ListNode(int data1, ListNode *next1)
    {
        val = data1;
        next = next1;
    }
};

void printLL(ListNode *head)
{
    while (head != NULL)
    {
        cout << head->val << " ";
        head = head->next;
    }

    cout << endl;
}

// ============================================================================
// INSERT AT HEAD APPROACH
//
// Idea:
// Create a new node with value X.
// Connect the new node to the current head and update it as the new head.
//
// Time Complexity: O(1)
// Space Complexity: O(1)   // Extra space excluding the newly created node.
// ============================================================================

ListNode *insertAtHead(ListNode *head, int X)
{
    return new ListNode(X, head);
}

int main()
{
    vector<int> arr = {20, 30, 40};
    int X = 10;

    // Create linked list: 20 -> 30 -> 40
    ListNode *head = new ListNode(arr[0]);
    head->next = new ListNode(arr[1]);
    head->next->next = new ListNode(arr[2]);

    cout << "Original List: ";
    printLL(head);

    head = insertAtHead(head, X);

    cout << "List after inserting the given value at head: ";
    printLL(head);

    return 0;
}