// Problem:
// Given the head of a singly linked list containing only 0s, 1s, and 2s, sort the linked list in-place by modifying node links without creating new data nodes.

#include <bits/stdc++.h>
using namespace std;

class ListNode
{
public:
    int data;
    ListNode *next;

    // Default constructor.
    ListNode() : data(0), next(nullptr) {}

    // Constructor to initialize node value.
    ListNode(int x) : data(x), next(nullptr) {}

    // Constructor to initialize node value and next pointer.
    ListNode(int x, ListNode *next) : data(x), next(next) {}
};

void printList(ListNode *head)
{
    while (head != NULL)
    {
        cout << head->data << " ";
        head = head->next;
    }

    cout << endl;
}

ListNode *newNode(int data)
{
    return new ListNode(data);
}

// ============================================================================
// BRUTE FORCE APPROACH
//
// Idea:
// Count the number of 0s, 1s, and 2s in the first traversal.
// Traverse the list again and overwrite node values according to the counts.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// ============================================================================

// ListNode *sortList(ListNode *&head)
// {
//     if (!head || !head->next)
//         return head;

//     ListNode *temp = head;

//     int zeroCount = 0, oneCount = 0, twoCount = 0;

//     while (temp)
//     {
//         if (temp->data == 0)
//             zeroCount++;
//         if (temp->data == 1)
//             oneCount++;
//         if (temp->data == 2)
//             twoCount++;

//         temp = temp->next;
//     }

//     temp = head;

//     while (temp)
//     {
//         if (zeroCount)
//         {
//             temp->data = 0;
//             zeroCount--;
//         }
//         else if (oneCount)
//         {
//             temp->data = 1;
//             oneCount--;
//         }
//         else if (twoCount)
//         {
//             temp->data = 2;
//             twoCount--;
//         }

//         temp = temp->next;
//     }

//     return head;
// }

// ============================================================================
// OPTIMAL APPROACH
//
// Idea:
// Partition the nodes into three separate linked lists for 0s, 1s, and 2s using dummy nodes.
// Finally, connect the three lists together while preserving the original relative order within each group.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// ============================================================================

ListNode *sortList(ListNode *&head)
{
    if (!head || !head->next)
        return head;

    ListNode *temp = head;

    // Dummy heads for the three partitions.
    ListNode *zeroHead = new ListNode(-1);
    ListNode *oneHead = new ListNode(-1);
    ListNode *twoHead = new ListNode(-1);

    // Tail pointers for each partition.
    ListNode *zero = zeroHead;
    ListNode *one = oneHead;
    ListNode *two = twoHead;

    while (temp)
    {
        if (temp->data == 0)
        {
            zero->next = temp;
            zero = zero->next;
        }
        else if (temp->data == 1)
        {
            one->next = temp;
            one = one->next;
        }
        else
        {
            two->next = temp;
            two = two->next;
        }

        temp = temp->next;
    }

    // Connect the 0-list to the 1-list if it exists; otherwise connect directly
    // to the 2-list.
    zero->next = (oneHead->next) ? oneHead->next : twoHead->next;

    // Connect the 1-list to the 2-list.
    one->next = twoHead->next;

    // Mark the end of the final list.
    two->next = nullptr;

    // Update the head of the original list.
    head = zeroHead->next;

    // Delete the dummy heads.
    delete zeroHead;
    delete oneHead;
    delete twoHead;

    // Return the head of the sorted list.
    return head;
}

int main()
{
    // Create linked list:
    // 1 -> 2 -> 0 -> 1 -> 2 -> 0 -> 1
    ListNode *head = newNode(1);
    head->next = newNode(2);
    head->next->next = newNode(0);
    head->next->next->next = newNode(1);
    head->next->next->next->next = newNode(2);
    head->next->next->next->next->next = newNode(0);
    head->next->next->next->next->next->next = newNode(1);

    cout << "Original list: ";
    printList(head);

    head = sortList(head);

    cout << "Sorted list: ";
    printList(head);

    return 0;
}