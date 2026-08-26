// Problem:
// Given a singly linked list, rotate the list to the right by k positions.
// Return the modified linked list by changing only the node links.
// The node values should remain unchanged.

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

void insertNode(ListNode *&head, int val)
{
    ListNode *newNode = new ListNode(val);

    if (head == NULL)
    {
        head = newNode;
        return;
    }

    ListNode *temp = head;

    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
}

void printList(ListNode *head)
{
    while (head != NULL)
    {
        cout << head->val;

        if (head->next != NULL)
            cout << "->";

        head = head->next;
    }

    cout << endl;
}

/*
==================================================
BRUTE FORCE APPROACH

Idea:
Rotate the linked list one position at a time by moving the last node to the front. Repeat this process k times.
The optimization in the optimal approach is avoiding repeated rotations.

Time Complexity: O(N * K)
Space Complexity: O(1)
==================================================
*/

// OPTIMAL APPROACH

/*
==================================================
OPTIMAL APPROACH (CIRCULAR LINK + BREAK)

Idea:
Connect the last node to the head to form a circular linked list.
Find the new tail after rotation and break the circle at that position.
Reduce unnecessary rotations by using k % length.

Time Complexity: O(N)
Space Complexity: O(1)
==================================================
*/

ListNode *rotateRight(ListNode *head, int k)
{
    if (!head || !head->next)
        return head;

    ListNode *tail = head;
    int length = 1;

    while (tail->next)
    {
        tail = tail->next;
        length++;
    }

    k = k % length;

    if (k == 0)
        return head;

    // Connect tail with head to form a circular linked list.
    tail->next = head;

    // Find the new tail node after rotation.
    ListNode *temp = head;
    int count = 0;

    while (temp)
    {
        count++;

        if (count == length - k)
            break;

        temp = temp->next;
    }

    // The next node of new tail becomes the new head.
    head = temp->next;

    // Break the circular linked list.
    temp->next = nullptr;

    return head;
}

int main()
{
    ListNode *head = NULL;

    insertNode(head, 1);
    insertNode(head, 2);
    insertNode(head, 3);
    insertNode(head, 4);
    insertNode(head, 5);

    cout << "Original list: ";
    printList(head);

    int k = 2;

    ListNode *newHead = rotateRight(head, k);

    cout << "After " << k << " iterations: ";

    printList(newHead);

    return 0;
}