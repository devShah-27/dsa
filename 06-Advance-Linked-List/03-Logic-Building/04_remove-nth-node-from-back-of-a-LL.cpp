// Problem:
// Given the head of a singly linked list and an integer n, remove the nth node from the end of the linked list and return the head of the modified list.
// The value of n is always valid and less than or equal to the list length.

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

// ============================================================================
// BRUTE FORCE APPROACH
//
// Idea:
// First calculate the length of the linked list.
// The nth node from the end is equivalent to the (length - n + 1)th node from the beginning, so traverse again and remove that node.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// ============================================================================

// ListNode *removeNthFromEnd(ListNode *head, int n)
// {
//     if (!head)
//         return head;

//     int linkedListLength = 0;

//     ListNode *temp = head;

//     while (temp)
//     {
//         linkedListLength++;
//         temp = temp->next;
//     }

//     // Removing the head node.
//     if (linkedListLength == n)
//     {
//         ListNode *newHead = head->next;

//         head->next = nullptr;
//         delete head;

//         return newHead;
//     }

//     int nodeBeforeDeletionPos = linkedListLength - n;

//     temp = head;

//     // Move to the node before the target node.
//     while (temp)
//     {
//         nodeBeforeDeletionPos--;

//         if (nodeBeforeDeletionPos == 0)
//             break;

//         temp = temp->next;
//     }

//     ListNode *markedForDeletion = temp->next;

//     temp->next = temp->next->next;

//     markedForDeletion->next = nullptr;
//     delete markedForDeletion;

//     return head;
// }

// ============================================================================
// OPTIMAL APPROACH (TWO POINTER APPROACH)
//
// Idea:
// Maintain two pointers with a gap of n nodes between them.
// Move both pointers together until the fast pointer reaches the end.
// The slow pointer will then be positioned just before the node to delete.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// ============================================================================

ListNode *removeNthFromEnd(ListNode *head, int n)
{
    if (!head)
        return head;

    // Move fast pointer n steps ahead to maintain the required gap.
    ListNode *fast = head;

    for (int i = 0; i < n; i++)
    {
        fast = fast->next;
    }

    // If fast becomes NULL, the head node needs to be removed.
    if (!fast)
    {
        ListNode *newHead = head->next;

        head->next = nullptr;
        delete head;

        return newHead;
    }

    ListNode *slow = head;

    // Move both pointers until fast reaches the last node.
    while (fast->next)
    {
        slow = slow->next;
        fast = fast->next;
    }

    // slow is now just before the node to be removed.
    ListNode *nodeToDelete = slow->next;

    slow->next = slow->next->next;

    nodeToDelete->next = nullptr;
    delete nodeToDelete;

    return head;
}

void printLL(ListNode *head)
{
    while (head != NULL)
    {
        cout << head->val << " ";
        head = head->next;
    }
}

int main()
{
    vector<int> arr = {1, 2, 3, 4, 5};
    int N = 5;

    ListNode *head = new ListNode(arr[0]);
    head->next = new ListNode(arr[1]);
    head->next->next = new ListNode(arr[2]);
    head->next->next->next = new ListNode(arr[3]);
    head->next->next->next->next = new ListNode(arr[4]);

    head = removeNthFromEnd(head, N);

    printLL(head);

    return 0;
}