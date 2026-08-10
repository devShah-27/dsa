// Problem:
// Implement a Last-In-First-Out (LIFO) stack using an array.
// The stack should support push, pop, top, and isEmpty operations.

#include <bits/stdc++.h>
using namespace std;

// =============================================================
// ARRAY IMPLEMENTATION OF STACK
//
// Idea:
// Maintain an array and a pointer to track the current top element.
// Push inserts an element at the top index and increments the pointer.
// Pop removes and returns the element at the current top index.
// =============================================================
//
// Time Complexity:
// push()  -> O(1)
// pop()   -> O(1)
// top()   -> O(1)
// isEmpty() -> O(1)
//
// Space Complexity:
// O(N), where N is the stack capacity.
//
// =============================================================

class ArrayStack
{
    int topIdx;
    int *st;
    int capacity;

public:
    ArrayStack(int size = 1000)
    {
        capacity = size;
        st = new int[capacity];
        topIdx = -1;
    }

    ~ArrayStack()
    {
        delete[] st;
    }

    void push(int x)
    {
        if (topIdx >= capacity - 1)
        {
            cout << "Stack Overflow" << endl;
            return;
        }

        st[++topIdx] = x;
    }

    int pop()
    {
        if (isEmpty())
        {
            cout << "Stack is empty" << endl;
            return -1;
        }

        return st[topIdx--];
    }

    int top()
    {
        if (isEmpty())
        {
            cout << "Stack is empty" << endl;
            return -1;
        }

        return st[topIdx];
    }

    bool isEmpty()
    {
        return topIdx == -1;
    }
};

int main()
{
    ArrayStack stack;
    vector<string> commands = {"ArrayStack", "push", "push", "top", "pop", "isEmpty"};
    vector<vector<int>> inputs = {{}, {5}, {10}, {}, {}, {}};

    for (size_t i = 0; i < commands.size(); ++i)
    {
        if (commands[i] == "push")
        {
            stack.push(inputs[i][0]);
            cout << "null ";
        }
        else if (commands[i] == "pop")
        {
            cout << stack.pop() << " ";
        }
        else if (commands[i] == "top")
        {
            cout << stack.top() << " ";
        }
        else if (commands[i] == "isEmpty")
        {
            cout << (stack.isEmpty() ? "true" : "false") << " ";
        }
        else if (commands[i] == "ArrayStack")
        {
            cout << "null ";
        }
    }

    return 0;
}