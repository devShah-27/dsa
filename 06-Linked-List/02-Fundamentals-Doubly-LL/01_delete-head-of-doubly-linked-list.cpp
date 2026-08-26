// Problem:
// Given the head of a doubly linked list, delete the first node (head node) and return the head of the modified linked list.

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
// Create the first node as the head of the list.
// For every remaining element, create a new node and connect it with both previous and next pointers to maintain doubly linked list connections.
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
// DELETE HEAD NODE FROM DOUBLY LINKED LIST
//
// Idea:
// Handle empty and single-node lists separately.
// Store the next node as the new head, disconnect the old head from the list, update the new head's previous pointer, and delete the old head node.
//
// Time Complexity: O(1)
// Space Complexity: O(1)
// ============================================================================

ListNode *deleteHead(ListNode *&head)
{
    if (head == NULL)
        return head;

    // Single-node linked list.
    if (head->next == NULL)
    {
        delete head;
        return NULL;
    }

    // Move head pointer to the next node.
    ListNode *newHead = head->next;

    // Remove backward connection from the new head.
    newHead->prev = NULL;

    // Disconnect old head before deleting.
    head->next = NULL;

    delete head;

    return newHead;
}

int main()
{
    vector<int> nums = {1, 2, 3, 4, 5};

    // Create doubly linked list: 1 <-> 2 <-> 3 <-> 4 <-> 5
    ListNode *head = arrayToLinkedList(nums);

    cout << "Original List: ";
    printLL(head);

    head = deleteHead(head);

    cout << "Modified list: ";
    printLL(head);

    return 0;
}