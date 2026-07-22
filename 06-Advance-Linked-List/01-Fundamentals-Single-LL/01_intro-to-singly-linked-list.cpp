// Problem:
// Implement a singly linked list node and construct a linked list from an array.
// Demonstrate basic node creation, pointer access, and array-to-linked-list conversion.

#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    int data;
    Node *nextPtr;

public:
    // Constructor to initialize both data and next pointer.
    Node(int data1, Node *nextPtr1)
    {
        data = data1;
        nextPtr = nextPtr1;
    }

public:
    // Constructor to initialize a node with only data.
    // The next pointer is set to nullptr by default.
    Node(int data1)
    {
        data = data1;
        nextPtr = nullptr;
    }
};

// ============================================================================
// ARRAY TO LINKED LIST
//
// Idea:
// Create the head node from the first array element.
// Maintain a pointer to the last node and keep attaching newly created nodes until all array elements are processed.
//
// Time Complexity: O(N)
// Space Complexity: O(N)   // Space used by the newly created linked list.
// ============================================================================

Node *convertArrayToLinkedList(vector<int> &arr)
{
    if (arr.size() == 0)
        return nullptr;

    Node *head = new Node(arr[0]);

    // Points to the last node currently present in the list.
    Node *mover = head;

    for (int i = 1; i < arr.size(); i++)
    {
        Node *temp = new Node(arr[i]);

        // Link the new node to the current tail.
        mover->nextPtr = temp;

        // Advance the tail pointer.
        mover = temp;
    }

    return head;
}

int main()
{
    // Create a standalone node.
    Node *y = new Node(2, nullptr);

    cout << y << endl;
    cout << y->data << endl;
    cout << y->nextPtr << endl;

    // Convert an array into a singly linked list.
    vector<int> arr = {2, 5, 7, 8};

    Node *head = convertArrayToLinkedList(arr);

    cout << head << endl;
    cout << head->data << endl;
    cout << head->nextPtr << endl;
}