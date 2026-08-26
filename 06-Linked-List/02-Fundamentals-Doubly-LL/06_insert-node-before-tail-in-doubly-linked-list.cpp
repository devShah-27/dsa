// Problem:
// Given the head of a doubly linked list and an integer X, insert a new node with value X immediately before the tail node and return the head.

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
// Create nodes from the array and connect every node using both previous and next pointers to maintain the doubly linked list structure.
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
// INSERT BEFORE TAIL IN DOUBLY LINKED LIST
//
// Idea:
// Handle the single-node list separately.
// Traverse to the tail node, then insert the new node between the tail and its previous node by updating all required previous and next pointers.
//
// Time Complexity: O(N)
// Space Complexity: O(1)   // Extra space excluding the newly created node.
// ============================================================================

ListNode *insertBeforeTail(ListNode *head, int X)
{
    if (head == NULL)
        return head;

    ListNode *newElem = new ListNode(X);

    // Single-node linked list.
    if (head->prev == NULL && head->next == NULL)
    {
        newElem->next = head;
        head->prev = newElem;

        return newElem;
    }

    ListNode *temp = head;

    // Move to the tail node.
    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    ListNode *prevToTail = temp->prev;

    // Connect previous node with the new node.
    prevToTail->next = newElem;

    // Connect new node with the tail node.
    temp->prev = newElem;

    // Complete backward and forward links.
    newElem->prev = prevToTail;
    newElem->next = temp;

    return head;
}

int main()
{
    vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Create doubly linked list:
    // 1 <-> 2 <-> 3 <-> 4 <-> 5 <-> 6 <-> 7 <-> 8 <-> 9 <-> 10
    ListNode *head = arrayToLinkedList(nums);

    cout << "Original List: ";
    printLL(head);

    head = insertBeforeTail(head, 100);

    cout << "Modified list: ";
    printLL(head);

    return 0;
}