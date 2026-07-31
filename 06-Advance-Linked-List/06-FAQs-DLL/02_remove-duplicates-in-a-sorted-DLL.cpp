// Problem:
// Given a sorted doubly linked list, remove all duplicate values.
// Keep only one occurrence of each value and return the head of the modified list.

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
Traverse the sorted doubly linked list and compare adjacent nodes.
Whenever duplicate nodes are found, remove the extra node by updating the previous and next pointers while maintaining list connections.

Time Complexity: O(N)
Space Complexity: O(1)
==================================================
*/

ListNode *removeDuplicates(ListNode *head)
{
    if (!head || !head->next)
        return head;

    ListNode *temp = head;
    ListNode *prevNode = nullptr;
    ListNode *nextNode = head->next;

    while (temp->next)
    {
        if (temp->val == temp->next->val)
        {
            // Update head if the first node is removed.
            if (temp == head)
                head = head->next ? head->next : nullptr;

            nextNode = temp->next;
            prevNode = temp->prev;

            // Connect previous node with next node.
            if (nextNode)
                nextNode->prev = prevNode;

            if (prevNode)
                prevNode->next = nextNode;

            // Detach the duplicate node before deleting.
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

    head->next->next = newNode(2);
    head->next->next->prev = head->next;

    head->next->next->next = newNode(3);
    head->next->next->next->prev = head->next->next;

    head->next->next->next->next = newNode(4);
    head->next->next->next->next->prev = head->next->next->next;

    head->next->next->next->next->next = newNode(4);
    head->next->next->next->next->next->prev = head->next->next->next->next;

    head->next->next->next->next->next->next = newNode(5);
    head->next->next->next->next->next->next->prev = head->next->next->next->next->next;

    cout << "Original list: ";
    printList(head);

    head = removeDuplicates(head);

    cout << "Modified list: ";
    printList(head);

    return 0;
}