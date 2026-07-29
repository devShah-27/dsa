// Problem:
// Given the head of a singly linked list, determine whether the linked list contains a cycle.
// Return true if a loop exists; otherwise, return false.

#include <bits/stdc++.h>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(NULL) {}
    ListNode(int data1) : val(data1), next(NULL) {}
    ListNode(int data1, ListNode *next1) : val(data1), next(next1) {}
};

/*
==================================================
BRUTE FORCE APPROACH (HASH SET)

Idea:
Traverse the linked list while storing the address of every visited node in a hash set.
If a node is encountered again, a cycle exists.
If the traversal reaches NULL, the linked list is acyclic.

Time Complexity: O(N)
Space Complexity: O(N)
==================================================
*/
// bool hasCycle(ListNode *head)
// {
//     if (!head || !head->next)
//         return false;

//     unordered_set<ListNode *> st;

//     ListNode *temp = head;

//     while (temp)
//     {
//         if (st.find(temp) != st.end())
//             return true;

//         st.insert(temp);
//         temp = temp->next;
//     }

//     return false;
// }

/*
==================================================
OPTIMAL APPROACH (FLOYD'S CYCLE DETECTION)

Idea:
Use two pointers where slow moves one step and fast moves two steps.
If a cycle exists, the two pointers will eventually meet inside the loop.
If fast reaches NULL, no cycle is present.

Time Complexity: O(N)
Space Complexity: O(1)
==================================================
*/

bool hasCycle(ListNode *head)
{
    if (!head || !head->next)
        return false;

    ListNode *fast = head, *slow = head;

    while (fast && fast->next)
    {
        fast = fast->next->next;
        slow = slow->next;

        if (fast == slow)
            return true;
    }

    return false;
}

int main()
{
    ListNode *head = new ListNode(1);
    ListNode *second = new ListNode(2);
    ListNode *third = new ListNode(3);
    ListNode *fourth = new ListNode(4);
    ListNode *fifth = new ListNode(5);

    head->next = second;
    second->next = third;
    third->next = fourth;
    fourth->next = fifth;

    fifth->next = third;

    if (hasCycle(head))
    {
        cout << "Loop detected in the linked list." << endl;
    }
    else
    {
        cout << "No loop detected in the linked list." << endl;
    }

    // NOTE: Deleting nodes individually is unsafe because the linked list contains a cycle.
    // Break the cycle before deallocating the nodes to avoid undefined behavior.
    delete head;
    delete second;
    delete third;
    delete fourth;
    delete fifth;

    return 0;
}