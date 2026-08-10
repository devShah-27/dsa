// Problem:
// Implement a Last-In-First-Out (LIFO) stack using a singly linked list.
// The stack should support push, pop, top, and isEmpty operations.

#include <bits/stdc++.h>
using namespace std;

// =============================================================
// LINKED LIST IMPLEMENTATION OF STACK
//
// Idea:
// Use a singly linked list where the head node represents the top of the stack. Insertions and deletions are performed at the head to achieve constant time stack operations.
//
// Time Complexity:
// push() -> O(1)
// pop() -> O(1)
// top() -> O(1)
// isEmpty() -> O(1)
//
// Space Complexity:
// O(N), where N is the number of elements stored in the stack.
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

class LinkedListStack
{
    Node *head;
    int size;

public:
    LinkedListStack()
    {
        head = nullptr;
        size = 0;
    }

    ~LinkedListStack()
    {
        while (!isEmpty())
            pop();
    }

    void push(int x)
    {
        Node *newNode = new Node(x);

        newNode->next = head;
        head = newNode;

        size++;
    }

    int pop()
    {
        if (isEmpty())
            return -1;

        Node *temp = head;
        head = head->next;

        int data = temp->val;

        delete temp;
        size--;

        return data;
    }

    int top()
    {
        if (isEmpty())
            return -1;

        return head->val;
    }

    bool isEmpty()
    {
        return head == nullptr;
    }
};

int main()
{
    LinkedListStack st;

    vector<string> commands = {"LinkedListStack", "push", "push",
                               "pop", "top", "isEmpty"};

    vector<vector<int>> inputs = {{}, {3}, {7}, {}, {}, {}};

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
        else if (commands[i] == "LinkedListStack")
        {
            cout << "null ";
        }
    }

    return 0;
}