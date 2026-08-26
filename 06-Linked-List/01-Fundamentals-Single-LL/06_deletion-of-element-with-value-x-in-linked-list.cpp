// Problem:
// Given the head of a singly linked list and an integer X, delete the first node containing value X and return the head of the modified linked list.

#include <bits/stdc++.h>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;

    // Default constructor.
    ListNode() : val(0), next(nullptr) {}

    // Constructor to initialize node value.
    ListNode(int data1) : val(data1), next(nullptr) {}

    // Constructor to initialize node value and next pointer.
    ListNode(int data1, ListNode *next1) : val(data1), next(next1) {}
};

void printLL(ListNode *head)
{
    ListNode *current = head;

    while (current != nullptr)
    {
        cout << current->val << " ";
        current = current->next;
    }

    cout << endl;
}

// ============================================================================
// DELETE NODE WITH GIVEN VALUE
//
// Idea:
// Traverse the linked list while keeping track of the previous node.
// If the target value is found, bypass the current node by updating the previous node's next pointer and delete the target node.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// ============================================================================

ListNode *deleteNodeWithValueX(ListNode *&head, int X)
{
    if (head == NULL)
        return NULL;

    ListNode *temp = head;

    // Special case: deleting the head node.
    if (head->val == X)
    {
        head = head->next;
        delete temp;

        return head;
    }

    ListNode *prev = NULL;

    while (temp != NULL)
    {
        if (temp->val == X)
        {
            // Remove the current node by connecting previous node to next node.
            prev->next = prev->next->next;

            delete temp;
            break;
        }

        prev = temp;
        temp = temp->next;
    }

    return head;
}

int main()
{
    vector<int> arr = {0, 1, 2};
    int X = 2;

    // Create linked list: 0 -> 1 -> 2
    ListNode *head = new ListNode(arr[0]);
    head->next = new ListNode(arr[1]);
    head->next->next = new ListNode(arr[2]);

    cout << "Original List: ";
    printLL(head);

    head = deleteNodeWithValueX(head, X);

    cout << "List after deleting the given value: ";
    printLL(head);

    return 0;
}