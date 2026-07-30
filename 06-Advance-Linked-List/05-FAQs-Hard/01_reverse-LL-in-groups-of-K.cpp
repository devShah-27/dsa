// Problem:
// Given a singly linked list, reverse the nodes in groups of size k.
// If the remaining nodes at the end are fewer than k, keep them unchanged.
// Only modify links between nodes, without changing node values.

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

/*
==================================================
HELPER FUNCTION (REVERSE LINKED LIST)

Idea:
Reverse the given linked list using three pointers.
This helper is used to reverse each group of k nodes.

Time Complexity: O(N)
Space Complexity: O(1)
==================================================
*/

ListNode *revLLHelper(ListNode *head)
{
    if (!head || !head->next)
        return head;

    ListNode *temp = head, *prev = nullptr;

    while (temp)
    {
        ListNode *front = temp->next;
        temp->next = prev;
        prev = temp;
        temp = front;
    }

    return prev;
}

/*
==================================================
OPTIMAL APPROACH (RECURSION + LINK REVERSAL)

Idea:
Check whether at least k nodes are available for reversal.
Reverse the current group and recursively process the remaining list.
Connect the reversed group with the next processed group.

Time Complexity: O(N)
Space Complexity: O(N) due to recursion stack
==================================================
*/

ListNode *reverseKGroup(ListNode *head, int k)
{
    if (!head)
        return nullptr;

    ListNode *temp = head, *prev = nullptr;

    int count = 0;

    while (count < k)
    {
        if (temp == nullptr)
            return head;

        prev = temp;

        temp = temp->next;

        count++;
    }

    ListNode *revLLHead = reverseKGroup(temp, k);

    prev->next = nullptr;

    revLLHelper(head);

    head->next = revLLHead;

    return prev;
}

int main()
{
    ListNode *head = new ListNode(5);
    head->next = new ListNode(4);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(7);
    head->next->next->next->next = new ListNode(9);
    head->next->next->next->next->next = new ListNode(2);

    cout << "Original Linked List: ";
    printLinkedList(head);

    head = reverseKGroup(head, 2);

    cout << "Reversed Linked List: ";
    printLinkedList(head);

    return 0;
}