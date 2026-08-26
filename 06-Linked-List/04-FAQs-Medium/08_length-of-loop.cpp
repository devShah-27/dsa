// Problem:
// Given the head of a singly linked list, find the length of the loop if a cycle exists.
// Return the number of nodes in the cycle; otherwise, return 0.

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

/*
==================================================
BRUTE FORCE APPROACH (HASH MAP)

Idea:
Traverse the linked list while storing each node along with the time/index
at which it was visited.
If a previously visited node is encountered again, the difference between
the current index and stored index gives the length of the loop.

Time Complexity: O(N)
Space Complexity: O(N)
==================================================
*/
// int findLengthOfLoop(ListNode *head)
// {
//     if (!head || !head->next)
//         return 0;

//     unordered_map<ListNode *, int> mpp;
//     ListNode *temp = head;
//     int currentTimer = 0;

//     while (temp)
//     {
//         if (mpp.find(temp) != mpp.end())
//         {
//             int timerAtTemp = mpp[temp];
//             return currentTimer - timerAtTemp;
//         }

//         mpp.insert({temp, currentTimer});

//         currentTimer++;

//         temp = temp->next;
//     }

//     return 0;
// }

/*
==================================================
OPTIMAL APPROACH (FLOYD'S CYCLE DETECTION)

Idea:
Use slow and fast pointers to detect whether a cycle exists.
Once both pointers meet, traverse the cycle once using one pointer
to count the number of nodes present inside the loop.

Time Complexity: O(N)
Space Complexity: O(1)
==================================================
*/

int findLengthOfLoop(ListNode *head)
{
    if (!head || !head->next)
        return 0;

    ListNode *fast = head, *slow = head;

    while (fast && fast->next)
    {
        fast = fast->next->next;
        slow = slow->next;

        if (fast == slow)
        {
            fast = fast->next;
            int count = 1;

            while (fast != slow)
            {
                count++;
                fast = fast->next;
            }

            return count;
        }
    }

    return 0;
}

int main()
{
    vector<int> loopStartCases = {
        -1, // No loop
        1,  // Loop starts at head
        2,  // Loop starts at second node
        3,  // Loop starts in middle
        5   // Loop starts at last node (self-loop)
    };

    for (int loopStart : loopStartCases)
    {
        cout << "=====================================\n";

        ListNode *head = new ListNode(1);
        ListNode *second = new ListNode(2);
        ListNode *third = new ListNode(3);
        ListNode *fourth = new ListNode(4);
        ListNode *fifth = new ListNode(5);

        head->next = second;
        second->next = third;
        third->next = fourth;
        fourth->next = fifth;

        if (loopStart == 1)
            fifth->next = head;
        else if (loopStart == 2)
            fifth->next = second;
        else if (loopStart == 3)
            fifth->next = third;
        else if (loopStart == 5)
            fifth->next = fifth;
        else
            fifth->next = nullptr;

        cout << "Test Case: Loop starts at node value = " << loopStart << endl;

        int loopLength = findLengthOfLoop(head);

        if (loopLength > 0)
            cout << "Length of the loop: " << loopLength << endl;
        else
            cout << "No loop found in the linked list." << endl;

        // Safely delete nodes even when a cycle exists.
        unordered_set<ListNode *> visited;
        ListNode *temp = head;

        while (temp && visited.find(temp) == visited.end())
        {
            visited.insert(temp);
            ListNode *next = temp->next;
            delete temp;
            temp = next;
        }
    }

    cout << "=====================================\n";
    cout << "Large loop test\n";

    vector<ListNode *> nodes;

    for (int i = 1; i <= 100000; i++)
    {
        nodes.push_back(new ListNode(i));
    }

    for (int i = 0; i < 99999; i++)
    {
        nodes[i]->next = nodes[i + 1];
    }

    nodes[99999]->next = nodes[49999];

    int largeLoopLength = findLengthOfLoop(nodes[0]);

    cout << "Length of large loop: " << largeLoopLength << endl;

    unordered_set<ListNode *> visited;
    ListNode *temp = nodes[0];

    while (temp && visited.find(temp) == visited.end())
    {
        visited.insert(temp);
        ListNode *next = temp->next;
        delete temp;
        temp = next;
    }

    return 0;
}