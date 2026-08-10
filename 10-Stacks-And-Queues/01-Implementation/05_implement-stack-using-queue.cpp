// Problem:
// Implement a Last-In-First-Out (LIFO) stack using a single queue.
// The stack should support push, pop, top, and isEmpty operations.

#include <bits/stdc++.h>
using namespace std;

// =============================================================
// IMPLEMENT STACK USING A SINGLE QUEUE
//
// Idea:
// Use a queue and rearrange its elements after every push operation.
// The newly inserted element is moved to the front, making the queue behave like a stack where the front element is always the top.
//
// Time Complexity:
// push() -> O(N)
// pop() -> O(1)
// top() -> O(1)
// isEmpty() -> O(1)
//
// Space Complexity:
// O(N), where N is the number of elements stored in the stack.
//
// =============================================================

class QueueStack
{
    queue<int> q;

public:
    void push(int x)
    {
        int s = q.size();
        q.push(x);

        for (int i = 0; i < s; i++)
        {
            q.push(q.front());
            q.pop();
        }
    }

    int pop()
    {
        int val = q.front();
        q.pop();

        return val;
    }

    int top()
    {
        return q.front();
    }

    bool isEmpty()
    {
        return q.empty();
    }
};

int main()
{
    QueueStack st;

    vector<string> commands = {"QueueStack", "push", "push",
                               "pop", "top", "isEmpty"};

    vector<vector<int>> inputs = {{}, {4}, {8}, {}, {}, {}};

    for (int i = 0; i < commands.size(); ++i)
    {
        if (commands[i] == "push")
        {
            st.push(inputs[i][0]);
            cout << "null ";
        }
        else if (commands[i] == "pop")
        {
            cout << st.pop() << " ";
        }
        else if (commands[i] == "top")
        {
            cout << st.top() << " ";
        }
        else if (commands[i] == "isEmpty")
        {
            cout << (st.isEmpty() ? "true" : "false") << " ";
        }
        else if (commands[i] == "QueueStack")
        {
            cout << "null ";
        }
    }

    return 0;
}