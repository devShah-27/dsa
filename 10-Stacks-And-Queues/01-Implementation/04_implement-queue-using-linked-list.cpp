// Problem:
// Implement a First-In-First-Out (FIFO) queue using a singly linked list.
// The queue should support push, pop, peek, and isEmpty operations.

#include <bits/stdc++.h>
using namespace std;

// =============================================================
// LINKED LIST IMPLEMENTATION OF QUEUE
//
// Idea:
// Use a singly linked list with two pointers: start for the front element and end for the rear element. Insertions are performed at the rear and deletions are performed at the front.
//
// Time Complexity:
// push() -> O(1)
// pop() -> O(1)
// peek() -> O(1)
// isEmpty() -> O(1)
//
// Space Complexity:
// O(N), where N is the number of elements stored in the queue.
//
// =============================================================

struct Node
{
    int val;
    Node *next;

    Node(int d)
    {
        val = d;
        next = NULL;
    }
};

class LinkedListQueue
{
    Node *start, *end;
    int size;

public:
    LinkedListQueue()
    {
        start = nullptr;
        end = nullptr;
        size = 0;
    }

    ~LinkedListQueue()
    {
        while (!isEmpty())
            pop();
    }

    void push(int x)
    {
        Node *newNode = new Node(x);

        if (start == nullptr)
        {
            start = end = newNode;
        }
        else
        {
            end->next = newNode;
            end = end->next;
        }

        size++;
    }

    int pop()
    {
        if (isEmpty())
            return -1;

        Node *temp = start;
        start = start->next;

        int data = temp->val;

        delete temp;

        if (isEmpty())
            end = nullptr;

        return data;
    }

    int peek()
    {
        if (isEmpty())
            return -1;

        return start->val;
    }

    bool isEmpty()
    {
        return (start == nullptr);
    }
};

int main()
{
    LinkedListQueue q;

    vector<string> commands = {"LinkedListQueue", "push", "push",
                               "peek", "pop", "isEmpty"};

    vector<vector<int>> inputs = {{}, {3}, {7}, {}, {}, {}};

    for (int i = 0; i < commands.size(); ++i)
    {
        if (commands[i] == "push")
        {
            q.push(inputs[i][0]);
            cout << "null ";
        }
        else if (commands[i] == "pop")
        {
            cout << q.pop() << " ";
        }
        else if (commands[i] == "peek")
        {
            cout << q.peek() << " ";
        }
        else if (commands[i] == "isEmpty")
        {
            cout << (q.isEmpty() ? "true" : "false") << " ";
        }
        else if (commands[i] == "LinkedListQueue")
        {
            cout << "null ";
        }
    }

    return 0;
}