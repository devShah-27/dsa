// Problem:
// Given the head of a non-empty singly linked list, delete the middle node of the list.
// The middle node is defined as the (⌊n / 2⌋ + 1)th node using 1-based indexing.
// Return the head of the modified linked list.

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

void printLL(ListNode *head)
{
    ListNode *temp = head;
    while (temp != NULL)
    {
        cout << temp->val << " ";
        temp = temp->next;
    }
    cout << endl;
}

/*
==================================================
BRUTE FORCE APPROACH

Idea:
First, traverse the linked list to calculate its total length.
Find the middle node position using (length / 2) + 1.
Traverse again to reach the middle node, unlink it, and delete it.

Time Complexity: O(N + N/2) == O(N)
Space Complexity: O(1)
==================================================
*/
// ListNode *deleteMiddle(ListNode *head)
// {
//     if (!head)
//         return nullptr;

//     if (!head->next)
//     {
//         delete head;
//         return nullptr;
//     }

//     ListNode *temp = head;
//     int length = 0;

//     while (temp)
//     {
//         length++;
//         temp = temp->next;
//     }

//     temp = head;
//     ListNode *prev = nullptr;

//     int nodeDeleteNumber = (length / 2) + 1;

//     while (temp)
//     {
//         nodeDeleteNumber--;
//         if (nodeDeleteNumber == 0)
//             break;

//         prev = temp;
//         temp = temp->next;
//     }

//     prev->next = temp->next;

//     delete temp;

//     return head;
// }

/*
==================================================
OPTIMAL APPROACH (SLOW AND FAST POINTER)

Idea:
Use two pointers where fast moves two steps and slow moves one step.
Maintain a pointer to the node before slow to directly remove the middle node.
When fast reaches the end, slow will point to the middle node.

Time Complexity: O(N/2) == O(N)
Space Complexity: O(1)
==================================================
*/

ListNode *deleteMiddle(ListNode *head)
{
    if (!head)
        return nullptr;

    if (!head->next)
    {
        delete head;
        return nullptr;
    }

    ListNode *fast = head, *slow = head, *prevToSlow = nullptr;

    while (fast && fast->next)
    {
        fast = fast->next->next;
        prevToSlow = slow;
        slow = slow->next;
    }

    prevToSlow->next = slow->next;

    delete slow;

    return head;
}

int main()
{
    ListNode *head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);
    // head->next->next->next->next->next = new ListNode(6);

    cout << "Original Linked List: ";
    printLL(head);

    head = deleteMiddle(head);

    cout << "Updated Linked List: ";
    printLL(head);

    return 0;
}