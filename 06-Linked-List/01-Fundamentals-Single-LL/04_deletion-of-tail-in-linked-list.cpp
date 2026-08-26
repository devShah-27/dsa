// Problem:
// Given the head of a singly linked list, delete the last node (tail node) and return the head of the modified linked list.

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
// Create a new node and connect it before the current head node.
// Update the head pointer to point to the newly inserted node.
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
// DELETE TAIL NODE
//
// Idea:
// Handle empty and single-node lists separately.
// Traverse until the second-last node, delete the last node, and update the second-last node's next pointer to nullptr.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// ============================================================================

ListNode *deleteTail(ListNode *head)
{
    // Empty linked list.
    if (head == NULL)
        return NULL;

    // Single-node linked list.
    if (head->next == NULL)
    {
        delete head;
        return NULL;
    }

    ListNode *temp = head;

    // Move to the second-last node.
    while (temp->next->next != NULL)
    {
        temp = temp->next;
    }

    // Store and delete the last node.
    ListNode *lastElem = temp->next;
    delete lastElem;

    // Disconnect the deleted node from the list.
    temp->next = nullptr;

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

    head = deleteTail(head);

    cout << "List after deleting tail: ";
    printList(head);

    return 0;
}