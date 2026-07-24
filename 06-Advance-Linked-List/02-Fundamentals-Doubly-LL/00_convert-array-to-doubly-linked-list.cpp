// Problem:
// Given an array of integers, construct a doubly linked list containing the array elements in the same order and return the head of the list.

#include <bits/stdc++.h>
using namespace std;

class ListNode
{
public:
    int data;
    ListNode *next;
    ListNode *prev;

    // Default constructor.
    ListNode() : data(0), next(nullptr), prev(nullptr) {}

    // Constructor to initialize node value.
    ListNode(int x) : data(x), next(nullptr), prev(nullptr) {}

    // Constructor to initialize node value, next pointer, and previous pointer.
    ListNode(int d, ListNode *n, ListNode *p) : data(d), next(n), prev(p) {}
};

void printLL(ListNode *head)
{
    while (head != NULL)
    {
        cout << head->data << " ";
        head = head->next;
    }

    cout << endl;
}

// ============================================================================
// ARRAY TO DOUBLY LINKED LIST
//
// Idea:
// Create the head node from the first array element.
// Maintain a pointer to the last node in the list and, for each remaining element, create a new node and connect both forward and backward links.
//
// Time Complexity: O(N)
// Space Complexity: O(N)   // Space used by the newly created linked list.
// ============================================================================

ListNode *arrayToDoublyLinkedList(vector<int> &nums)
{
    if (nums.size() == 0)
        return nullptr;

    // Create the head node.
    ListNode *head = new ListNode(nums[0]);

    // Points to the current tail of the list.
    ListNode *temp = head;

    for (int i = 1; i < nums.size(); i++)
    {
        ListNode *newElem = new ListNode(nums[i]);

        // Link the new node in both directions.
        temp->next = newElem;
        newElem->prev = temp;

        // Update the tail pointer.
        temp = newElem;
    }

    return head;
}

int main()
{
    vector<int> nums = {1, 2, 3, 4};

    // Create doubly linked list: 1 <-> 2 <-> 3 <-> 4
    ListNode *head = arrayToDoublyLinkedList(nums);

    cout << "The doubly linked list is: ";
    printLL(head);

    return 0;
}