// Problem:
// Given the head of a singly linked list, return the middle node of the linked list.
// If the linked list contains an even number of nodes, return the second middle node.

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
BRUTE FORCE APPROACH

Idea:
First, traverse the linked list to calculate its total length.
Then, traverse again until reaching the middle position.
For an even-sized list, selecting (length / 2) + 1 gives the second middle node.

Time Complexity: O(2N) == O(N)
Space Complexity: O(1)
==================================================
*/
// ListNode *middleOfLinkedList(ListNode *head)
// {
//     if (!head || !head->next)
//         return head;

//     ListNode *temp = head;

//     int length = 0;

//     while (temp)
//     {
//         length++;
//         temp = temp->next;
//     }

//     int midNodeNumber = (length / 2) + 1;

//     temp = head;

//     while (temp)
//     {
//         midNodeNumber--;

//         if (midNodeNumber == 0)
//             break;

//         temp = temp->next;
//     }

//     return temp;
// }

/*
==================================================
OPTIMAL APPROACH (SLOW AND FAST POINTER)

Idea:
Use two pointers where slow moves one step and fast moves two steps at a time.
When fast reaches the end, slow will be positioned at the middle node.
For even-sized lists, this naturally returns the second middle node.

Time Complexity: O(N)
Space Complexity: O(1)
==================================================
*/

ListNode *middleOfLinkedList(ListNode *head)
{
    if (!head || !head->next)
        return head;

    ListNode *fast = head, *slow = head;

    while (fast && fast->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }

    return slow;
}

int main()
{
    ListNode *head = new ListNode(1);
    ListNode *second = new ListNode(2);
    ListNode *third = new ListNode(3);
    ListNode *fourth = new ListNode(4);
    ListNode *fifth = new ListNode(5);
    // ListNode *sixth = new ListNode(6);

    head->next = second;
    second->next = third;
    third->next = fourth;
    fourth->next = fifth;
    // fifth->next = sixth;

    ListNode *middleNode = middleOfLinkedList(head);

    printLinkedList(head);
    cout << "The middle node is: " << middleNode->val << endl;

    return 0;
}