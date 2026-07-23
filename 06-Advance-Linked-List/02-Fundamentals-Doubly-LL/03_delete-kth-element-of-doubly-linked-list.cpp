// Problem:
// Given the head of a doubly linked list and an integer k, delete the node at the kth position and return the head of the modified linked list.

#include <bits/stdc++.h>
using namespace std;

// Definition of doubly linked list
struct ListNode
{
    int val;
    ListNode *next;
    ListNode *prev;

    // Default constructor.
    ListNode()
    {
        val = 0;
        next = NULL;
        prev = NULL;
    }

    // Constructor to initialize node value.
    ListNode(int data1)
    {
        val = data1;
        next = NULL;
        prev = NULL;
    }

    // Constructor to initialize node value, next pointer, and previous pointer.
    ListNode(int data1, ListNode *next1, ListNode *prev1)
    {
        val = data1;
        next = next1;
        prev = prev1;
    }
};

// ============================================================================
// ARRAY TO DOUBLY LINKED LIST
//
// Idea:
// Create nodes one by one from the array values.
// Maintain previous and next pointers for every node to form a doubly linked list.
//
// Time Complexity: O(N)
// Space Complexity: O(N)   // Space used by the newly created linked list.
// ============================================================================

ListNode *arrayToLinkedList(vector<int> &nums)
{
    if (nums.empty())
        return nullptr;

    ListNode *head = new ListNode(nums[0]);

    ListNode *prev = head;

    for (int i = 1; i < nums.size(); i++)
    {
        ListNode *temp = new ListNode(nums[i], nullptr, prev);

        prev->next = temp;
        prev = temp;
    }

    return head;
}

void printLL(ListNode *head)
{
    while (head != NULL)
    {
        cout << head->val << " ";
        head = head->next;
    }

    cout << endl;
}

// ============================================================================
// DELETE KTH NODE FROM DOUBLY LINKED LIST
//
// Idea:
// Handle deletion of the head node separately.
// For other positions, traverse to the kth node and update both previous and next links to remove the node while maintaining the doubly linked structure.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// ============================================================================

ListNode *deleteKthElement(ListNode *head, int k)
{
    if (head == NULL)
        return head;

    // Deleting the head node.
    if (k == 1)
    {
        ListNode *newHead = head->next;

        if (head->next != NULL)
        {
            // Remove backward link from the new head.
            newHead->prev = NULL;

            // Disconnect old head.
            head->next = NULL;
        }

        delete head;

        return newHead;
    }

    int count = 0;
    ListNode *temp = head;

    while (temp != NULL)
    {
        count++;

        if (count == k)
        {
            // Connect previous node to next node.
            temp->prev->next = temp->next;

            // Update next node's previous pointer if it exists.
            if (temp->next != nullptr)
                temp->next->prev = temp->prev;

            // Disconnect the deleted node.
            temp->next = nullptr;
            temp->prev = nullptr;

            delete temp;

            break;
        }

        temp = temp->next;
    }

    return head;
}

int main()
{
    vector<int> nums = {1, 2, 3, 4, 5};
    int k = 5;

    // Create doubly linked list: 1 <-> 2 <-> 3 <-> 4 <-> 5
    ListNode *head = arrayToLinkedList(nums);

    cout << "Original List: ";
    printLL(head);

    head = deleteKthElement(head, k);

    cout << "Modified list: ";
    printLL(head);

    return 0;
}