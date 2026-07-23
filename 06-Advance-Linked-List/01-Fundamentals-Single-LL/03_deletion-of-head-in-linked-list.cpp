// Problem:
// Given the head of a singly linked list, delete the first node (head node) and return the head of the modified linked list.

#include <bits/stdc++.h>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;

    // Default constructor.
    ListNode() : val(0), next(nullptr) {}

    // Constructor to initialize node value.
    ListNode(int data1) : val(data1), next(nullptr) {}

    // Constructor to initialize node value and next pointer.
    ListNode(int data1, ListNode *next1) : val(data1), next(next1) {}
};

void printList(ListNode *head)
{
    ListNode *current = head;

    while (current != nullptr)
    {
        cout << current->val << " ";
        current = current->next;
    }

    cout << endl;
}

// ============================================================================
// INSERT AT HEAD
//
// Idea:
// Create a new node and make it point to the current head.
// Update the head pointer to the newly created node.
//
// Time Complexity: O(1)
// Space Complexity: O(1)   // Extra space excluding the newly created node.
// ============================================================================

ListNode *insertAtHead(ListNode *head, int data)
{
    ListNode *newNode = new ListNode(data);

    newNode->next = head;
    head = newNode;

    return head;
}

// ============================================================================
// DELETE HEAD NODE
//
// Idea:
// If the linked list is empty, return the current head.
// Store the current head temporarily, move the head pointer to the next node, and delete the old head node to free memory.
//
// Time Complexity: O(1)
// Space Complexity: O(1)
// ============================================================================

ListNode *deleteHead(ListNode *head)
{
    if (head == NULL)
        return head;

    ListNode *temp = head;

    // Move head to the second node.
    head = head->next;

    // Delete the previous head node.
    delete temp;

    return head;
}

int main()
{
    ListNode *head = nullptr;

    // Create linked list: 1 -> 2 -> 3
    head = insertAtHead(head, 3);
    head = insertAtHead(head, 2);
    head = insertAtHead(head, 1);

    cout << "Original list: ";
    printList(head);

    head = deleteHead(head);

    cout << "List after deleting head: ";
    printList(head);

    return 0;
}