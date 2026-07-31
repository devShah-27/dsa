// Problem:
// Given the head of a doubly linked list and an integer target, delete all nodes containing the target value.
// Return the head of the modified doubly linked list.

#include <bits/stdc++.h>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode *prev;

    ListNode()
    {
        val = 0;
        next = NULL;
        prev = NULL;
    }

    ListNode(int data1)
    {
        val = data1;
        next = NULL;
        prev = NULL;
    }

    ListNode(int data1, ListNode *next1, ListNode *prev1)
    {
        val = data1;
        next = next1;
        prev = prev1;
    }
};

void printList(ListNode *head)
{
    ListNode *temp = head;

    while (temp != NULL)
    {
        cout << temp->val << " ";
        temp = temp->next;
    }

    cout << endl;
}

ListNode *newNode(int data)
{
    ListNode *node = new ListNode(data);
    return node;
}

/*
==================================================
OPTIMAL APPROACH (SINGLE PASS)

Idea:
Traverse the doubly linked list and check every node's value.
When a target node is found, adjust its previous and next pointers to remove it from the list while maintaining list connectivity.

Time Complexity: O(N)
Space Complexity: O(1)
==================================================
*/

ListNode *deleteAllOccurrences(ListNode *head, int target)
{
    if (!head)
        return nullptr;

    ListNode *temp = head;
    ListNode *prevNode = nullptr;
    ListNode *nextNode = head->next;

    while (temp)
    {
        if (temp->val == target)
        {
            // Update head if the first node is deleted.
            if (temp == head)
                head = head->next ? head->next : nullptr;

            nextNode = temp->next;
            prevNode = temp->prev;

            // Connect previous node with next node.
            if (prevNode)
                prevNode->next = temp->next;

            // Connect next node with previous node.
            if (nextNode)
                nextNode->prev = prevNode;

            // Detach the node before deleting it.
            temp->prev = nullptr;
            temp->next = nullptr;

            delete temp;

            temp = nextNode;
        }
        else
        {
            temp = temp->next;
        }
    }

    return head;
}

int main()
{
    ListNode *head = newNode(1);
    head->next = newNode(2);
    head->next->prev = head;
    head->next->next = newNode(3);
    head->next->next->prev = head->next;
    head->next->next->next = newNode(2);
    head->next->next->next->prev = head->next->next;
    head->next->next->next->next = newNode(4);
    head->next->next->next->next->prev = head->next->next->next;
    head->next->next->next->next->next = newNode(2);
    head->next->next->next->next->next->prev = head->next->next->next->next;
    head->next->next->next->next->next->next = newNode(5);
    head->next->next->next->next->next->next->prev = head->next->next->next->next->next;

    cout << "Original list: ";
    printList(head);

    head = deleteAllOccurrences(head, 2);

    cout << "Modified list: ";
    printList(head);

    return 0;
}