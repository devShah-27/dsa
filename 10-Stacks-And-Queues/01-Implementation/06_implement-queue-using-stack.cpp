// Problem:
// Implement a First-In-First-Out (FIFO) queue using two stacks.
// The queue should support push, pop, peek, and isEmpty operations.

#include <bits/stdc++.h>
using namespace std;

// =============================================================
// APPROACH 1: EXPENSIVE PUSH OPERATION
//
// Idea:
// Maintain the front element of the queue always at the top of s1.
// During push, transfer all elements to s2, insert the new element, and restore elements back to s1.
//
// Time Complexity:
// push() -> O(N)
// pop() -> O(1)
// peek() -> O(1)
// isEmpty() -> O(1)
//
// Space Complexity:
// O(N), where N is the number of elements stored in the queue.
//
// =============================================================

// class StackQueue
// {
//     stack<int> s1, s2;

// public:
//     void push(int x)
//     {
//         while (s1.size())
//         {
//             s2.push(s1.top());
//             s1.pop();
//         }

//         s1.push(x);

//         while (s2.size())
//         {
//             s1.push(s2.top());
//             s2.pop();
//         }
//     }

//     int pop()
//     {
//         int n = s1.top();
//         s1.pop();
//         return n;
//     }

//     int peek()
//     {
//         return s1.top();
//     }

//     bool isEmpty()
//     {
//         return s1.empty();
//     }
// };

// =============================================================
// APPROACH 2: OPTIMIZED TWO STACK APPROACH
//
// Idea:
// Use one stack for input operations and another stack for output.
// Elements are transferred from s1 to s2 only when required, which reverses the order and allows queue-like FIFO behavior.
//
// Time Complexity:
// push() -> O(1)
// pop() -> Amortized O(1)
// peek() -> Amortized O(1)
// isEmpty() -> O(1)
//
// Space Complexity:
// O(N), where N is the number of elements stored in the queue.
//
// =============================================================

class StackQueue
{
    stack<int> s1, s2;

public:
    void push(int x)
    {
        s1.push(x);
    }

    int pop()
    {
        if (s2.empty())
        {
            while (s1.size())
            {
                s2.push(s1.top());
                s1.pop();
            }
        }

        int n = s2.top();
        s2.pop();

        return n;
    }

    int peek()
    {
        if (s2.empty())
        {
            while (s1.size())
            {
                s2.push(s1.top());
                s1.pop();
            }
        }

        return s2.top();
    }

    bool isEmpty()
    {
        return s1.empty() && s2.empty();
    }
};

int main()
{
    StackQueue q;

    vector<string> commands = {"StackQueue", "push", "push",
                               "pop", "peek", "isEmpty"};

    vector<vector<int>> inputs = {{}, {4}, {8}, {}, {}, {}};

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
        else if (commands[i] == "StackQueue")
        {
            cout << "null ";
        }
    }

    return 0;
}