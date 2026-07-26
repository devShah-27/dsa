// Problem:
// Given the head of a singly linked list, reverse the linked list and return the head of the reversed linked list.

#include <bits/stdc++.h>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode()
    {
        val = 0;
        next = NULL;
    }
    ListNode(int data1)
    {
        val = data1;
        next = NULL;
    }
    ListNode(int data1, ListNode *next1)
    {
        val = data1;
        next = next1;
    }
};

void printLinkedList(ListNode *head)
{
    ListNode *temp = head;
    while (temp != nullptr)
    {
        cout << temp->val << " ";
        temp = temp->next;
    }
    cout << endl;
}

// ============================================================================
// BRUTE FORCE APPROACH
//
// Idea:
// Store all node values in a stack while traversing the linked list.
// Traverse the list again and replace values using the stack order.
// The links between nodes remain unchanged.
//
// Time Complexity: O(2*N) -> O(N)
// Space Complexity: O(N)
//
// ============================================================================

// ListNode *reverseList(ListNode *head)
// {
//     if (!head || !head->next)
//         return head;

//     ListNode *temp = head;

//     stack<int> st;

//     while (temp)
//     {
//         st.push(temp->val);
//         temp = temp->next;
//     }

//     temp = head;

//     while (temp)
//     {
//         temp->val = st.top();
//        st.pop();
//         temp = temp->next;
//     }

//     return head;
// }

// ============================================================================
// OPTIMAL APPROACH
//
// Idea:
// Reverse the linked list by changing the direction of pointers during traversal.
// Maintain three pointers: previous node, current node, and next node.
// Move through the list and reverse each link one by one until all nodes are reversed.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
//
// ============================================================================

ListNode *reverseList(ListNode *head)
{
    if (!head || !head->next)
        return head;

    ListNode *temp = head, *prev = nullptr;

    while (temp)
    {
        ListNode *front = temp->next; // Store next node before breaking the link
        temp->next = prev;            // Reverse current node's pointer
        prev = temp;                  // Move previous pointer forward
        temp = front;                 // Move current pointer forward
    }

    return prev;
}

int main()
{
    ListNode *head = new ListNode(1);
    head->next = new ListNode(3);
    head->next->next = new ListNode(2);
    head->next->next->next = new ListNode(4);

    cout << "Original Linked List: ";
    printLinkedList(head);

    head = reverseList(head);

    cout << "Reversed Linked List: ";
    printLinkedList(head);

    return 0;
}