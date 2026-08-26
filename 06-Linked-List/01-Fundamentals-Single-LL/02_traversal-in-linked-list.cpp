// Problem:
// Given the head of a singly linked list, traverse the list from head to tail and return all node values in the order they appear.

#include <bits/stdc++.h>
using namespace std;

class ListNode
{
public:
    int data;
    ListNode *next;

    // Default constructor.
    ListNode() : data(0), next(nullptr) {}

    // Constructor to initialize only the node value.
    ListNode(int x) : data(x), next(nullptr) {}

    // Constructor to initialize both value and next pointer.
    ListNode(int x, ListNode *next) : data(x), next(next) {}
};

// ============================================================================
// ITERATIVE TRAVERSAL APPROACH
//
// Idea:
// Start from the head node and visit each node exactly once.
// Store every node's value in a result array while moving to the next node until the end of the linked list reached.
//
// Time Complexity: O(N)
// Space Complexity: O(1) (Auxiliary space considered because output is generally not counted towards an algorithm's overall Space Complexity) 
// ============================================================================

vector<int> LLTraversal(ListNode *head)
{
    vector<int> result;

    // Pointer used to traverse the linked list.
    ListNode *temp = head;

    while (temp)
    {
        result.emplace_back(temp->data);

        // Move to the next node.
        temp = temp->next;
    }

    return result;
}

int main()
{
    // Create a sample linked list: 2 -> 5 -> 8 -> 7
    ListNode *y1 = new ListNode(2);
    ListNode *y2 = new ListNode(5);
    ListNode *y3 = new ListNode(8);
    ListNode *y4 = new ListNode(7);

    y1->next = y2;
    y2->next = y3;
    y3->next = y4;

    vector<int> result = LLTraversal(y1);

    cout << "Linked List Values:" << endl;
    for (int val : result)
    {
        cout << val << " ";
    }
    cout << endl;

    // Free allocated memory.
    delete y1;
    delete y2;
    delete y3;
    delete y4;

    return 0;
}