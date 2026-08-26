// Problem:
// Given a reference to a node in a doubly linked list (excluding the head), delete that node while maintaining the integrity of the linked list.

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
// Create nodes from the array and connect each node with both previous and next pointers to form a doubly linked list.
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
// DELETE GIVEN NODE FROM DOUBLY LINKED LIST
//
// Idea:
// Since the node reference is directly provided, there is no need to traverse the list.
// Update the previous and next node connections to remove the given node, then delete it from memory.
//
// Time Complexity: O(1)
// Space Complexity: O(1)
// ============================================================================

void deleteGivenNode(ListNode *node)
{
    ListNode *prev = node->prev;
    ListNode *next = node->next;

    // If deleting the tail node, only update the previous node's next pointer.
    if (next == nullptr)
    {
        prev->next = nullptr;
    }
    else
    {
        // Connect previous and next nodes together.
        prev->next = next;
        next->prev = prev;

        // Disconnect deleted node from the next node.
        node->next = nullptr;
    }

    // Disconnect deleted node from the previous node.
    node->prev = nullptr;

    delete node;

    return;
}

int main()
{
    vector<int> nums = {1, 2, 3, 4, 5};

    // Create doubly linked list: 1 <-> 2 <-> 3 <-> 4 <-> 5
    ListNode *head = arrayToLinkedList(nums);

    // Select node with value 3.
    ListNode *node = head->next->next;

    cout << "Original List: ";
    printLL(head);

    deleteGivenNode(node);

    cout << "Modified list: ";
    printLL(head);

    return 0;
}