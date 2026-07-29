// Problem:
// Given the head of a singly linked list, return the node where the cycle begins.
// If the linked list does not contain a cycle, return nullptr.

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

void createTestList(ListNode *&head, int loop_start_val)
{
    ListNode *node1 = new ListNode(1);
    ListNode *node2 = new ListNode(2);
    ListNode *node3 = new ListNode(3);
    ListNode *node4 = new ListNode(4);
    ListNode *node5 = new ListNode(5);

    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;

    head = node1;

    ListNode *temp = head;
    while (temp != nullptr && temp->val != loop_start_val)
    {
        temp = temp->next;
    }

    node5->next = temp; // Creates a loop only if the target node exists.
}

/*
==================================================
BRUTE FORCE APPROACH (HASH SET)

Idea:
Traverse the linked list while storing every visited node in a hash set.
The first node encountered twice is the starting point of the cycle.
If the traversal reaches nullptr, no cycle exists.

Time Complexity: O(N)
Space Complexity: O(N)
==================================================
*/
// ListNode *findStartingPoint(ListNode *head)
// {
//     if (!head || !head->next)
//         return nullptr;

//     unordered_set<ListNode *> st;

//     ListNode *temp = head;

//     while (temp)
//     {
//         if (st.find(temp) != st.end())
//             return temp;

//         st.insert(temp);
//         temp = temp->next;
//     }

//     return nullptr;
// }

/*
==================================================
OPTIMAL APPROACH (FLOYD'S CYCLE DETECTION)

Idea:
Use slow and fast pointers to detect whether a cycle exists.
Once they meet, move one pointer back to the head.
Advance both pointers one step at a time; their next meeting point is the starting node of the cycle.

Time Complexity: O(N)
Space Complexity: O(1)
==================================================
*/

ListNode *findStartingPoint(ListNode *head)
{
    if (!head || !head->next)
        return nullptr;

    ListNode *slow = head, *fast = head;

    while (fast && fast->next)
    {
        fast = fast->next->next;
        slow = slow->next;

        if (fast == slow)
        {
            slow = head;

            while (fast != slow)
            {
                slow = slow->next;
                fast = fast->next;
            }

            return fast;
        }
    }

    return nullptr;
}

int main()
{
    vector<int> testCases = {
        1, // Loop starts at head
        2, // Loop starts near the beginning
        3, // Loop starts in the middle
        4, // Small cycle: 4 -> 5 -> 4
        5, // Self-loop at the last node
        10 // Invalid value -> No loop
    };

    for (int loopStart : testCases)
    {
        cout << "=====================================\n";
        cout << "Test Case: loop_start_val = " << loopStart << '\n';

        ListNode *head = nullptr;
        createTestList(head, loopStart);

        ListNode *loopStartNode = findStartingPoint(head);

        if (loopStartNode)
            cout << "Loop detected. Starting node of the loop is: "
                 << loopStartNode->val << '\n';
        else
            cout << "No loop detected in the linked list.\n";

        ListNode *temp = head;
        unordered_map<ListNode *, bool> visited;

        while (temp != nullptr && visited[temp] == false)
        {
            visited[temp] = true;
            ListNode *next = temp->next;
            delete temp;
            temp = next;
        }

        cout << '\n';
    }

    return 0;
}