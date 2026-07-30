// Given the head of a singly linked list containing integers, shift the elements of the linked list to the right by k places and return the head of the modified list. Do not change the values of the nodes, only change the links between nodes.

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

void insertNode(ListNode *&head, int val)
{
    ListNode *newNode = new ListNode(val);
    if (head == NULL)
    {
        head = newNode;
        return;
    }
    ListNode *temp = head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = newNode;
}

void printList(ListNode *head)
{
    while (head != NULL)
    {
        cout << head->val;
        if (head->next != NULL)
            cout << "->";
        head = head->next;
    }
    cout << endl;
}

// BRUTE FORCE -> Same as optimal without the step k=k%length where TC -> O(N*K), SC -> O(1)

// OPTIMAL APPROACH
ListNode *rotateRight(ListNode *head, int k) // TC -> O(N), SC -> O(1)
{
    if (!head || !head->next)
        return head;

    ListNode *tail = head;
    int length = 1;

    while (tail->next)
    {
        tail = tail->next;
        length++;
    }

    k = k % length;

    if (k == 0)
        return head;

    tail->next = head;

    ListNode *temp = head;
    int count = 0;

    while (temp)
    {
        count++;

        if (count == length - k)
            break;

        temp = temp->next;
    }

    head = temp->next;

    temp->next = nullptr;

    return head;
}

int main()
{
    ListNode *head = NULL;

    insertNode(head, 1);
    insertNode(head, 2);
    insertNode(head, 3);
    insertNode(head, 4);
    insertNode(head, 5);

    cout << "Original list: ";
    printList(head);

    int k = 2;

    ListNode *newHead = rotateRight(head, k);

    cout << "After " << k << " iterations: ";

    printList(newHead);

    return 0;
}
