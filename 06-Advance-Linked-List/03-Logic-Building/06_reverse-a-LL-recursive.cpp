// Problem:
// Given the head of a singly linked list, reverse the linked list and return the head of the reversed linked list.

#include <bits/stdc++.h>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode()
    {
        val = 0;
        next = NULL;
    }
    ListNode(int data1)
    {
        val = data1;
        next = NULL;
    }
    ListNode(int data1, ListNode *next1)
    {
        val = data1;
        next = next1;
    }
};

void printLinkedList(ListNode *head)
{
    ListNode *temp = head;
    while (temp != nullptr)
    {
        cout << temp->val << " ";
        temp = temp->next;
    }
    cout << endl;
}

// ============================================================================
// RECURSIVE APPROACH
//
// Idea:
// Recursively reverse the linked list starting from the second node onwards.
// Once the remaining list is reversed, attach the current node at the end.
// Break the original connection to avoid forming a cycle.
//
// Time Complexity: O(N)
// Space Complexity: O(N) -> Recursive call stack
//
// ============================================================================

ListNode *reverseList(ListNode *head)
{
    if (!head || !head->next)
        return head;

    ListNode *newHead = reverseList(head->next);

    ListNode *front = head->next; // Node after current node
    front->next = head;           // Attach current node after the reversed list
    head->next = nullptr;         // Remove old connection to prevent cycle

    return newHead;
}

int main()
{
    ListNode *head = new ListNode(1);
    head->next = new ListNode(3);
    head->next->next = new ListNode(2);
    head->next->next->next = new ListNode(4);

    cout << "Original Linked List: ";
    printLinkedList(head);

    head = reverseList(head);

    cout << "Reversed Linked List: ";
    printLinkedList(head);

    return 0;
}