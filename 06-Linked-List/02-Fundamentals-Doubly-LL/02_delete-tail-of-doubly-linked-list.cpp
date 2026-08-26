// Problem:
// Given the head of a doubly linked list, delete the last node (tail node) and return the head of the modified linked list.

#include <bits/stdc++.h>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode *prev;

    // Default constructor.
    ListNode()
    {
        val = 0;
        next = NULL;
        prev = NULL;
    }

    // Constructor to initialize node value.
    ListNode(int data1)
    {
        val = data1;
        next = NULL;
        prev = NULL;
    }

    // Constructor to initialize node value, next pointer, and previous pointer.
    ListNode(int data1, ListNode *next1, ListNode *prev1)
    {
        val = data1;
        next = next1;
        prev = prev1;
    }
};

// ============================================================================
// ARRAY TO DOUBLY LINKED LIST
//
// Idea:
// Create the first node as the head and maintain a pointer to the last node.
// Connect each newly created node with both previous and next pointers to preserve the doubly linked list structure.
//
// Time Complexity: O(N)
// Space Complexity: O(N)   // Space used by the newly created linked list.
// ============================================================================

ListNode *arrayToLinkedList(vector<int> &nums)
{
    if (nums.empty())
        return nullptr;

    ListNode *head = new ListNode(nums[0]);
    ListNode *prev = head;

    for (int i = 1; i < nums.size(); i++)
    {
        ListNode *temp = new ListNode(nums[i], nullptr, prev);

        prev->next = temp;
        prev = temp;
    }

    return head;
}

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
// DELETE TAIL NODE FROM DOUBLY LINKED LIST
//
// Idea:
// Handle empty and single-node lists separately.
// Traverse to the last node, update the previous node's next pointer, remove the backward link of the tail, and delete the tail node.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// ============================================================================

ListNode *deleteTail(ListNode *&head)
{
    if (head == NULL)
        return head;

    // Single-node linked list.
    if (head->next == NULL)
    {
        delete head;
        return NULL;
    }

    ListNode *temp = head;

    // Move to the last node.
    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    // Update the previous node to become the new tail.
    ListNode *prev = temp->prev;
    prev->next = nullptr;

    // Disconnect the deleted node.
    temp->prev = nullptr;

    delete temp;

    return head;
}

int main()
{
    vector<int> nums = {1, 2, 3, 4, 5, 6};

    // Create doubly linked list: 1 <-> 2 <-> 3 <-> 4 <-> 5 <-> 6
    ListNode *head = arrayToLinkedList(nums);

    cout << "Original List: ";
    printLL(head);

    head = deleteTail(head);

    cout << "Modified list: ";
    printLL(head);

    return 0;
}