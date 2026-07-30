// Given the heads of two linked lists, list1 and list2, where each linked list has its elements sorted in non-decreasing order, merge them into a single sorted linked list and return the head of the merged linked list.

#include <bits/stdc++.h>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
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

void printLinkedList(ListNode *head)
{
    ListNode *temp = head;
    while (temp != nullptr)
    {

        cout << temp->val << " ";

        temp = temp->next;
    }
    cout << endl;
}

ListNode *convertToLL(vector<int> &arr)
{
    int n = arr.size();

    if (n == 0)
        return nullptr;

    ListNode *head = new ListNode(arr[0]);
    ListNode *temp = head;

    for (int i = 1; i < n; i++)
    {
        ListNode *newNode = new ListNode(arr[i]);
        temp->next = newNode;
        temp = temp->next;
    }

    return head;
}

// BRUTE FORCE
// ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) // TC -> O(N+M) + O((N+M) log(N+M)) + O(N+M), SC -> O(N+M)
// {
//     if (!list1)
//         return list2;
//     if (!list2)
//         return list1;

//     vector<int> arr;

//     ListNode *temp = list1;

//     while (temp)
//     {
//         arr.emplace_back(temp->val);
//         temp = temp->next;
//     }

//     temp = list2;

//     while (temp)
//     {
//         arr.emplace_back(temp->val);
//         temp = temp->next;
//     }

//     sort(arr.begin(), arr.end());

//     ListNode *newHead = convertToLL(arr);

//     return newHead;
// }

// Optimal Approach
ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) // TC -> O(N+M), SC -> O(1)
{
    if (!list1)
        return list2;
    if (!list2)
        return list1;

    ListNode *t1 = list1, *t2 = list2;

    ListNode *dummyNode = new ListNode(-1);

    ListNode *temp = dummyNode;

    while (t1 && t2)
    {
        if (t1->val <= t2->val)
        {
            temp->next = t1;
            t1 = t1->next;
        }
        else
        {
            temp->next = t2;
            t2 = t2->next;
        }

        temp = temp->next;
    }

    if (t1)
        temp->next = t1;

    if (t2)
        temp->next = t2;

    return dummyNode->next;
}

int main()
{
    ListNode *list1 = new ListNode(1);
    list1->next = new ListNode(3);
    list1->next->next = new ListNode(5);

    ListNode *list2 = new ListNode(2);
    list2->next = new ListNode(4);
    list2->next->next = new ListNode(6);

    cout << "First sorted linked list: ";
    printLinkedList(list1);

    cout << "Second sorted linked list: ";
    printLinkedList(list2);

    ListNode *mergedList = mergeTwoLists(list1, list2);

    cout << "Merged sorted linked list: ";
    printLinkedList(mergedList);

    return 0;
}
