// Problem:
// Given the head of a doubly linked list and an integer X, insert a new node with value X before the current head and return the new head.

#include <bits/stdc++.h>
using namespace std;

class ListNode
{
public:
    int data;
    ListNode *prev;
    ListNode *next;

    // Default constructor.
    ListNode() : data(0), prev(nullptr), next(nullptr) {}

    // Constructor to initialize node value.
    ListNode(int x) : data(x), prev(nullptr), next(nullptr) {}

    // Constructor to initialize node value, previous pointer, and next pointer.
    ListNode(int x, ListNode *prev, ListNode *next) : data(x), prev(prev), next(next) {}
};

// ============================================================================
// ARRAY TO DOUBLY LINKED LIST
//
// Idea:
// Create nodes from the array while maintaining both previous and next links.
// Each newly created node is connected with the previous node to preserve the doubly linked list structure.
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
        ListNode *temp = new ListNode(nums[i], prev, nullptr);

        prev->next = temp;

        prev = temp;
    }

    return head;
}

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
// INSERT BEFORE HEAD IN DOUBLY LINKED LIST
//
// Idea:
// Create a new node whose next pointer points to the current head.
// Update the current head's previous pointer to point back to the new node.
// Return the newly created node as the new head.
//
// Time Complexity: O(1)
// Space Complexity: O(1)   // Extra space excluding the newly created node.
// ============================================================================

ListNode *insertBeforeHead(ListNode *head, int X)
{
    ListNode *newHead = new ListNode(X, nullptr, head);

    head->prev = newHead;

    return newHead;
}

int main()
{
    vector<int> nums = {2, 3, 4, 5};

    // Create doubly linked list: 2 <-> 3 <-> 4 <-> 5
    ListNode *head = arrayToLinkedList(nums);

    cout << "Original List: ";
    printLL(head);

    head = insertBeforeHead(head, 1);

    cout << "Modified list: ";
    printLL(head);

    return 0;
}