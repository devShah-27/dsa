// Problem:
// Given the head of a singly linked list, rearrange the list by placing all nodes at odd indices first followed by all nodes at even indices.
// Maintain the original relative order within both groups.

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
// BRUTE FORCE APPROACH
//
// Idea:
// Store odd-indexed nodes followed by even-indexed nodes in an auxiliary array.
// Traverse the linked list again and replace node values using the stored order.
//
// Time Complexity: O(N)
// Space Complexity: O(N)
// ============================================================================

// ListNode *oddEvenList(ListNode *&head)
// {
//     if (head == NULL || head->next == NULL)
//         return head;

//     vector<int> ans;

//     ListNode *temp = head;

//     // Store nodes at odd indices.
//     while (temp && temp->next)
//     {
//         ans.emplace_back(temp->data);
//         temp = temp->next->next;
//     }

//     if (temp)
//         ans.emplace_back(temp->data);

//     temp = head->next;

//     // Store nodes at even indices.
//     while (temp && temp->next)
//     {
//         ans.emplace_back(temp->data);
//         temp = temp->next->next;
//     }

//     if (temp)
//         ans.emplace_back(temp->data);

//     // Update linked list values using reordered sequence.
//     int idx = 0;
//     temp = head;

//     while (temp)
//     {
//         temp->data = ans[idx];
//         idx++;
//         temp = temp->next;
//     }

//     return head;
// }

// ============================================================================
// OPTIMAL APPROACH
//
// Idea:
// Maintain two separate chains for odd-indexed and even-indexed nodes while traversing the list.
// After traversal, connect the end of the odd chain to the start of the even chain to obtain the required ordering.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// ============================================================================

ListNode *oddEvenList(ListNode *&head)
{
    if (!head || !head->next)
        return head;

    // odd points to the current end of odd-indexed nodes.
    // even points to the current end of even-indexed nodes.
    // evenHead stores the starting point of the even-indexed chain.
    ListNode *odd = head;
    ListNode *even = head->next;
    ListNode *evenHead = head->next;

    while (even && even->next)
    {
        // Attach next odd node to the odd chain.
        odd->next = odd->next->next;

        // Attach next even node to the even chain.
        even->next = even->next->next;

        // Move both pointers forward.
        odd = odd->next;
        even = even->next;
    }

    // Connect odd chain with even chain.
    odd->next = evenHead;

    return head;
}

int main()
{
    vector<int> arr = {1, 3, 4, 2, 5, 6};

    // Create linked list: 1 -> 3 -> 4 -> 2 -> 5 -> 6
    ListNode *head = new ListNode(arr[0]);
    head->next = new ListNode(arr[1]);
    head->next->next = new ListNode(arr[2]);
    head->next->next->next = new ListNode(arr[3]);
    head->next->next->next->next = new ListNode(arr[4]);
    head->next->next->next->next->next = new ListNode(arr[5]);

    head = oddEvenList(head);

    printLL(head);

    return 0;
}