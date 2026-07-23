// Problem:
// Given the head of a singly linked list and two integers X and val, insert a new node with value val before the first node containing value X.

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
// INSERT BEFORE NODE WITH VALUE X
//
// Idea:
// Handle insertion before the head node separately.
// Otherwise, traverse the linked list while maintaining the previous node.
// When the node with value X is found, insert the new node between previous and current nodes.
//
// Time Complexity: O(N)
// Space Complexity: O(1)   // Extra space excluding the newly created node.
// ============================================================================

ListNode *insertBeforeX(ListNode *&head, int X, int val)
{
    if (head == NULL)
        return NULL;

    // Insert before the head node.
    if (head->data == X)
        return new ListNode(val, head);

    ListNode *temp = head;
    ListNode *prev = NULL;

    while (temp != NULL)
    {
        if (temp->data == X)
        {
            // Insert the new node between previous and current node.
            prev->next = new ListNode(val, temp);
            break;
        }

        prev = temp;
        temp = temp->next;
    }

    return head;
}

int main()
{
    vector<int> arr = {1, 2, 4, 5};
    int X = 1;
    int val = 100;

    // Create linked list: 1 -> 2 -> 4 -> 5
    ListNode *head = new ListNode(arr[0]);
    head->next = new ListNode(arr[1]);
    head->next->next = new ListNode(arr[2]);
    head->next->next->next = new ListNode(arr[3]);

    cout << "Original List: ";
    printLL(head);

    head = insertBeforeX(head, X, val);

    cout << "List after inserting a new node before the given node: ";
    printLL(head);

    return 0;
}