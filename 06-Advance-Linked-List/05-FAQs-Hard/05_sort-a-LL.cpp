// Problem:
// Given the head of a singly linked list, sort the linked list in non-decreasing order.
// Return the head of the sorted linked list.
// The sorting should be performed by rearranging node links without modifying node values.

#include <bits/stdc++.h>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;

    ListNode() : val(0), next(NULL) {}
    ListNode(int data1) : val(data1), next(NULL) {}
    ListNode(int data1, ListNode *next1) : val(data1), next(next1) {}
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
Store all node values in an array.
Sort the array using the built-in sorting algorithm.
Traverse the linked list again and update node values using sorted values.

Time Complexity: O(N) + O(N log N) + O(N) == O(N log N)
Space Complexity: O(N)
==================================================
*/
// ListNode *sortList(ListNode *head)
// {
//     if (!head || !head->next)
//         return head;

//     vector<int> list;
//     ListNode *temp = head;

//     while (temp)
//     {
//         list.emplace_back(temp->val);
//         temp = temp->next;
//     }

//     sort(list.begin(), list.end());

//     temp = head;
//     int idx = 0;

//     while (temp)
//     {
//         temp->val = list[idx++];
//         temp = temp->next;
//     }

//     return head;
// }

/*
==================================================
OPTIMAL APPROACH (MERGE SORT ON LINKED LIST)

Idea:
Use merge sort by recursively dividing the linked list into two halves.
Sort both halves independently and merge the sorted halves.
Linked lists are efficiently split and merged using pointers.

Time Complexity: O(N log N)
Space Complexity: O(log N) due to recursion stack
==================================================
*/

ListNode *merge(ListNode *headA, ListNode *headB)
{
    if (!headA)
        return headB;

    if (!headB)
        return headA;

    ListNode *tempA = headA, *tempB = headB;

    ListNode *dummy = new ListNode(-1);
    ListNode *temp = dummy;

    while (tempA && tempB)
    {
        if (tempA->val <= tempB->val)
        {
            temp->next = tempA;
            tempA = tempA->next;
        }
        else
        {
            temp->next = tempB;
            tempB = tempB->next;
        }

        temp = temp->next;
    }

    if (tempA)
        temp->next = tempA;

    if (tempB)
        temp->next = tempB;

    return dummy->next;
}

ListNode *sortList(ListNode *head)
{
    if (!head || !head->next)
        return head;

    // Find the middle node to split the linked list into two halves.
    ListNode *fast = head->next;
    ListNode *slow = head;

    while (fast && fast->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }

    // Split the linked list into two parts.
    ListNode *partitionATail = slow;
    ListNode *partitionBHead = slow->next;

    partitionATail->next = nullptr;

    // Recursively sort both halves.
    head = sortList(head);
    partitionBHead = sortList(partitionBHead);

    // Merge the sorted halves.
    head = merge(head, partitionBHead);

    return head;
}

int main()
{
    ListNode *head = new ListNode(3);
    head->next = new ListNode(2);
    head->next->next = new ListNode(5);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(1);

    cout << "Original Linked List: ";
    printLinkedList(head);

    head = sortList(head);

    cout << "Sorted Linked List: ";
    printLinkedList(head);

    return 0;
}