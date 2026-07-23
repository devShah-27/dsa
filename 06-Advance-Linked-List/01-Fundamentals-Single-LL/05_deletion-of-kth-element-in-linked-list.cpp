// Problem:
// Given the head of a singly linked list and an integer k, delete the kth node from the linked list and return the head of the modified list.

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
// DELETE KTH NODE APPROACH
//
// Idea:
// Traverse the linked list while maintaining a pointer to the previous node.
// Once the kth node is reached, bypass it by connecting the previous node to the next node and delete the kth node from memory.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// ============================================================================

ListNode *deleteKthNode(ListNode *&head, int k)
{
    if (head == NULL)
        return NULL;

    ListNode *temp = head;

    // Special case: deleting the head node.
    if (k == 1)
    {
        head = head->next;
        delete temp;

        return head;
    }

    int count = 0;
    ListNode *prev = NULL;

    while (temp != NULL)
    {
        count++;

        if (count == k)
        {
            // Remove the kth node by updating the previous node's link.
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
    vector<int> arr = {12, 5, 8, 7};

    // Create linked list: 12 -> 5 -> 8 -> 7
    ListNode *head = new ListNode(arr[0]);
    head->next = new ListNode(arr[1]);
    head->next->next = new ListNode(arr[2]);
    head->next->next->next = new ListNode(arr[3]);

    cout << "Original list: ";
    printLL(head);

    int k = 4;

    head = deleteKthNode(head, k);

    cout << "List after deleting the kth node: ";
    printLL(head);

    return 0;
}