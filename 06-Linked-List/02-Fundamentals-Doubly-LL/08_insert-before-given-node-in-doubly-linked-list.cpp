// Problem:
// Given a reference to a node in a doubly linked list (excluding the head) and an integer X, insert a new node with value X immediately before the given node.

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
// Create the head node from the first array element.
// For every remaining element, create a new node and connect it with both previous and next pointers to form a doubly linked list.
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
// INSERT BEFORE A GIVEN NODE
//
// Idea:
// Since the target node is directly provided, no traversal is required.
// Create a new node between the target node and its previous node by updating all affected previous and next pointers.
//
// Time Complexity: O(1)
// Space Complexity: O(1)   // Extra space excluding the newly created node.
// ============================================================================

void insertBeforeGivenNode(ListNode *node, int X)
{
    ListNode *newElem = new ListNode(X, node->prev, node);

    // Connect the previous node to the new node.
    node->prev->next = newElem;

    // Connect the target node back to the new node.
    node->prev = newElem;
}

int main()
{
    vector<int> nums = {1, 2, 4, 5};

    // Create doubly linked list: 1 <-> 2 <-> 4 <-> 5
    ListNode *head = arrayToLinkedList(nums);

    // Select node with value 4.
    ListNode *node = head->next->next;

    cout << "Original List: ";
    printLL(head);

    insertBeforeGivenNode(node, 100);

    cout << "Modified list: ";
    printLL(head);

    return 0;
}