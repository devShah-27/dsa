// Problem:
// Given a special linked list where each node has a next pointer and a child pointer, flatten the list into a single sorted linked list using only the child pointers.
// The final linked list should contain all nodes in sorted order.

#include <bits/stdc++.h>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode *child;

    ListNode()
    {
        val = 0;
        next = NULL;
        child = NULL;
    }

    ListNode(int data1)
    {
        val = data1;
        next = NULL;
        child = NULL;
    }

    ListNode(int data1, ListNode *next1, ListNode *next2)
    {
        val = data1;
        next = next1;
        child = next1;
    }
};

void printLinkedList(ListNode *head)
{
    while (head != nullptr)
    {
        cout << head->val << " ";
        head = head->child;
    }

    cout << endl;
}

void printOriginalLinkedList(ListNode *head, int depth)
{
    while (head != nullptr)
    {
        cout << head->val;

        if (head->child)
        {
            cout << " -> ";
            printOriginalLinkedList(head->child, depth + 1);
        }

        if (head->next)
        {
            cout << endl;

            for (int i = 0; i < depth; ++i)
            {
                cout << "| ";
            }
        }

        head = head->next;
    }
}

/*
==================================================
BRUTE FORCE APPROACH

Idea:
Traverse every node and collect all values from both next and child chains.
Sort all collected values and create a new flattened linked list.

Time Complexity: O(N*M + K log K) where K is total number of nodes
Space Complexity: O(K)
==================================================
*/

// ListNode *convertToLL(vector<int> &arr)
// {
//     if (arr.size() == 0)
//         return nullptr;

//     ListNode *dummyNode = new ListNode(-1);
//     ListNode *temp = dummyNode;

//     for (int it : arr)
//     {
//         temp->child = new ListNode(it);
//         temp = temp->child;
//     }

//     return dummyNode->child;
// }

// ListNode *flattenLinkedList(ListNode *&head)
// {
//     if (!head)
//         return nullptr;

//     vector<int> ls;

//     ListNode *temp = head;

//     while (temp)
//     {
//         ls.emplace_back(temp->val);

//         if (temp->child)
//         {
//             ListNode *childTemp = temp->child;

//             while (childTemp)
//             {
//                 ls.emplace_back(childTemp->val);
//                 childTemp = childTemp->child;
//             }
//         }

//         temp = temp->next;
//     }

//     sort(ls.begin(), ls.end());

//     return convertToLL(ls);
// }

/*
==================================================
OPTIMAL APPROACH (RECURSIVE MERGE)

Idea:
Flatten the linked list by recursively flattening the next chain.
Merge two sorted child-linked lists similar to merging two sorted linked lists.
The merged result uses only child pointers and removes next links.

Time Complexity: O(N) where N is total number of nodes
Space Complexity: O(N) due to recursion stack
==================================================
*/

ListNode *mergeTwoLL(ListNode *headA, ListNode *headB)
{
    if (!headA)
        return headB;

    if (!headB)
        return headA;

    ListNode *dummyNode = new ListNode(-1);
    ListNode *temp = dummyNode;

    ListNode *tempA = headA;
    ListNode *tempB = headB;

    while (tempA && tempB)
    {
        if (tempA->val <= tempB->val)
        {
            temp->child = tempA;
            tempA = tempA->child;
        }
        else
        {
            temp->child = tempB;
            tempB = tempB->child;
        }

        temp = temp->child;
        temp->next = nullptr;
    }

    if (tempA)
        temp->child = tempA;

    if (tempB)
        temp->child = tempB;

    return dummyNode->child;
}

ListNode *flattenLinkedList(ListNode *&head)
{
    if (!head || !head->next)
        return head;

    return mergeTwoLL(head, flattenLinkedList(head->next));
}

int main()
{
    ListNode *head = new ListNode(5);
    head->child = new ListNode(14);

    head->next = new ListNode(4);
    head->next->child = new ListNode(10);

    head->next->next = new ListNode(12);
    head->next->next->child = new ListNode(13);
    head->next->next->child->child = new ListNode(20);

    head->next->next->next = new ListNode(7);
    head->next->next->next->child = new ListNode(17);

    cout << "Original linked list:" << endl;
    printOriginalLinkedList(head, 0);

    ListNode *flattened = flattenLinkedList(head);

    cout << "\nFlattened linked list: ";
    printLinkedList(flattened);

    return 0;
}