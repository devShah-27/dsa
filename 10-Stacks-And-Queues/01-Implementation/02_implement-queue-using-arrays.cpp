// Problem:
// Implement a First-In-First-Out (FIFO) queue using an array.
// The queue should support push, pop, peek, and isEmpty operations.

#include <bits/stdc++.h>
using namespace std;

// =============================================================
// ARRAY IMPLEMENTATION OF QUEUE
//
// Idea:
// Use a circular array to efficiently utilize available space.
// Maintain start and end pointers to track the front and rear elements.
// Push inserts at the rear, while pop removes from the front.
// =============================================================
//
// Time Complexity:
// push()   -> O(1)
// pop()    -> O(1)
// peek()   -> O(1)
// isEmpty() -> O(1)
//
// Space Complexity:
// O(N), where N is the queue capacity.
//
// =============================================================

class ArrayQueue
{
    int capacity;
    int *q;
    int currSize;
    int start;
    int end;

public:
    ArrayQueue(int size = 1000)
    {
        capacity = size;
        q = new int[capacity];
        currSize = 0;
        start = -1;
        end = -1;
    }

    ~ArrayQueue()
    {
        delete[] q;
    }

    void push(int x)
    {
        if (currSize >= capacity)
        {
            cout << "Queue overflow" << endl;
            return;
        }
        else if (currSize == 0)
        {
            start = end = 0;
        }
        else
        {
            end = (end + 1) % capacity;
        }

        currSize++;

        q[end] = x;
    }

    int pop()
    {
        if (isEmpty())
        {
            cout << "Queue is empty" << endl;
            return -1;
        }

        int popped = q[start];

        if (currSize == 1)
        {
            start = end = -1;
        }
        else
        {
            start = (start + 1) % capacity;
        }

        currSize--;

        return popped;
    }

    int peek()
    {
        if (isEmpty())
        {
            cout << "Queue is Empty" << endl;
            return -1;
        }

        return q[start];
    }

    bool isEmpty()
    {
        return currSize == 0;
    }
};

int main()
{
    ArrayQueue queue;
    vector<string> commands = {"ArrayQueue", "push", "push",
                               "peek", "pop", "isEmpty"};
    vector<vector<int>> inputs = {{}, {5}, {10}, {}, {}, {}};

    for (int i = 0; i < commands.size(); ++i)
    {
        if (commands[i] == "push")
        {
            queue.push(inputs[i][0]);
            cout << "null ";
        }
        else if (commands[i] == "pop")
        {
            cout << queue.pop() << " ";
        }
        else if (commands[i] == "peek")
        {
            cout << queue.peek() << " ";
        }
        else if (commands[i] == "isEmpty")
        {
            cout << (queue.isEmpty() ? "true" : "false") << " ";
        }
        else if (commands[i] == "ArrayQueue")
        {
            cout << "null ";
        }
    }

    return 0;
}