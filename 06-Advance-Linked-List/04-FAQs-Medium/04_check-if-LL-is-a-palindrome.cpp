// Problem:
// Given a singly linked list representing a positive integer, check whether the sequence of node values forms a palindrome or not.
// Return true if the linked list reads the same forward and backward, otherwise return false.

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

/*
==================================================
BRUTE FORCE APPROACH

Idea:
Store all linked list values in a stack to preserve the reverse order.
Traverse the linked list again and compare each value with the stack's top element.
If any mismatch occurs, the linked list is not a palindrome.

Time Complexity: O(2N) == O(N)
Space Complexity: O(N)
==================================================
*/
// bool isPalindrome(ListNode *head)
// {
//     if (!head || !head->next)
//         return true;

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
//         if (temp->val != st.top())
//             return false;

//         st.pop();
//         temp = temp->next;
//     }

//     return true;
// }

/*
==================================================
OPTIMAL APPROACH (SLOW AND FAST POINTER)

Idea:
Use slow and fast pointers to find the middle of the linked list.
Reverse the second half of the list and compare it with the first half.
Restore the original linked list structure after comparison.

Time Complexity: O(N)
Space Complexity: O(1)
==================================================
*/

ListNode *reverseLL(ListNode *head)
{
    if (!head || !head->next)
        return head;

    ListNode *temp = head, *prev = nullptr;

    while (temp)
    {
        ListNode *front = temp->next;
        temp->next = prev;
        prev = temp;
        temp = front;
    }

    return prev;
}

bool isPalindrome(ListNode *head)
{
    if (!head || !head->next)
        return true;

    // Find the end of the first half using the slow and fast pointer approach.
    ListNode *fast = head, *slow = head;

    while (fast->next && fast->next->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Reverse the second half of the linked list.
    ListNode *revPartitionHead = reverseLL(slow->next);

    // Compare the first half and reversed second half node by node.
    ListNode *first = head, *second = revPartitionHead;

    while (second)
    {
        if (first->val != second->val)
        {
            // Restore the original linked list before returning.
            reverseLL(revPartitionHead);
            return false;
        }

        first = first->next;
        second = second->next;
    }

    // Restore the original linked list structure.
    reverseLL(revPartitionHead);

    return true;
}

int main()
{

    ListNode *head = new ListNode(1);
    head->next = new ListNode(5);
    head->next->next = new ListNode(2);
    head->next->next->next = new ListNode(5);
    head->next->next->next->next = new ListNode(1);
    head->next->next->next->next->next = new ListNode(2);

    cout << "Original Linked List: ";
    printLinkedList(head);

    if (isPalindrome(head))
    {
        cout << "The linked list is a palindrome." << endl;
    }
    else
    {
        cout << "The linked list is not a palindrome." << endl;
    }

    cout << "Original Linked List: ";
    printLinkedList(head);

    return 0;
}