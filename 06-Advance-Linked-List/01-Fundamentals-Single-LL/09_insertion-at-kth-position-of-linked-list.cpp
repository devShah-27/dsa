// Problem:
// Given the head of a singly linked list, an integer X, and a position K, insert a new node with value X at the Kth position and return the head.

#include <bits/stdc++.h>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;

    // Constructor to initialize node value.
    ListNode(int data1)
    {
        val = data1;
        next = NULL;
    }

    // Constructor to initialize node value and next pointer.
    ListNode(int data1, ListNode *next1)
    {
        val = data1;
        next = next1;
    }
};

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
// INSERT AT KTH POSITION APPROACH
//
// Idea:
// Handle insertion at the head separately when K = 1.
// Otherwise, traverse until the (K-1)th node and insert the new node by adjusting the next pointers.
//
// Time Complexity: O(N)
// Space Complexity: O(1)   // Extra space excluding the newly created node.
// ============================================================================

ListNode *insertAtKthPosition(ListNode *&head, int X, int K)
{
    // Empty linked list case.
    if (head == NULL)
    {
        if (K == 1)
            return new ListNode(X);

        return NULL;
    }

    // Insert at the beginning.
    if (K == 1)
        return new ListNode(X, head);

    ListNode *temp = head;
    int count = 0;

    while (temp != NULL)
    {
        count++;

        // Move to the node before the insertion position.
        if (count == K - 1)
        {
            temp->next = new ListNode(X, temp->next);
            break;
        }

        temp = temp->next;
    }

    return head;
}

int main()
{
    vector<int> arr = {10, 30, 40};
    int X = 20;
    int K = 3;

    // Create linked list: 10 -> 30 -> 40
    ListNode *head = new ListNode(arr[0]);
    head->next = new ListNode(arr[1]);
    head->next->next = new ListNode(arr[2]);

    cout << "Original List: ";
    printLL(head);

    head = insertAtKthPosition(head, X, K);

    cout << "List after inserting the given value at the Kth position: ";
    printLL(head);

    return 0;
}