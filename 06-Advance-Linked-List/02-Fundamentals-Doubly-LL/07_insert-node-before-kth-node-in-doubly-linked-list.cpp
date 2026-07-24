// Problem:
// Given the head of a doubly linked list and integers X and K, insert a new node with value X before the Kth node and return the modified list's head.

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
// Create nodes from the array and connect each node with both previous and next pointers to maintain the doubly linked list structure.
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
// INSERT BEFORE KTH NODE IN DOUBLY LINKED LIST
//
// Idea:
// Handle insertion before the first node separately.
// Otherwise, traverse to the Kth node and insert the new node between the
// Kth node and its previous node by updating all required links.
//
// Time Complexity: O(N)
// Space Complexity: O(1)   // Extra space excluding the newly created node.
// ============================================================================

ListNode *insertBeforeKthPosition(ListNode *head, int X, int K)
{
    if (head == NULL)
        return NULL;

    ListNode *newElem = new ListNode(X);

    // Insert before the head node.
    if (K == 1)
    {
        newElem->next = head;
        head->prev = newElem;

        return newElem;
    }

    ListNode *temp = head;
    int count = 0;

    while (temp != NULL)
    {
        count++;

        if (count == K)
        {
            ListNode *prevToTemp = temp->prev;

            // Connect previous node with the new node.
            prevToTemp->next = newElem;

            // Connect new node with the current node.
            temp->prev = newElem;

            // Complete forward and backward links.
            newElem->next = temp;
            newElem->prev = prevToTemp;

            break;
        }

        temp = temp->next;
    }

    return head;
}

int main()
{
    vector<int> nums = {1, 2, 3, 5};

    // Create doubly linked list: 1 <-> 2 <-> 3 <-> 5
    ListNode *head = arrayToLinkedList(nums);

    cout << "Original List: ";
    printLL(head);

    head = insertBeforeKthPosition(head, 100, 4);

    cout << "Modified list: ";
    printLL(head);

    return 0;
}