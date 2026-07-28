// Problem:
// Given the heads of two singly linked lists, find the node where the two linked lists intersect.
// If the linked lists do not intersect, return NULL.
// The original structure of both linked lists must remain unchanged.

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
    while (head->next != NULL)
    {
        cout << head->val << "->";
        head = head->next;
    }

    cout << head->val << endl;
}

/*
==================================================
BRUTE FORCE APPROACH (HASH SET)

Idea:
Store all nodes of the first linked list in a hash set.
Traverse the second linked list and check whether any node already exists in the set.
The first common node encountered is the intersection point.

Time Complexity: O(M + N)
Space Complexity: O(M) or O(N)
==================================================
*/
// ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
// {
//     if (!headA || !headB)
//         return NULL;

//     unordered_set<ListNode *> st;

//     ListNode *temp = headA;

//     while (temp)
//     {
//         st.insert(temp);
//         temp = temp->next;
//     }

//     temp = headB;

//     while (temp)
//     {
//         if (st.find(temp) != st.end())
//             return temp;

//         temp = temp->next;
//     }

//     return NULL;
// }

/*
==================================================
BETTER APPROACH (LENGTH DIFFERENCE)

Idea:
Calculate the lengths of both linked lists.
Move the pointer of the longer list ahead by the length difference.
Traverse both lists together until both pointers point to the same node.

Time Complexity: O(M + N)
Space Complexity: O(1)
==================================================
*/
// ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
// {
//     if (!headA || !headB)
//         return NULL;

//     int lenA = 0, lenB = 0;

//     ListNode *temp = headA;

//     while (temp)
//     {
//         lenA++;
//         temp = temp->next;
//     }

//     temp = headB;

//     while (temp)
//     {
//         lenB++;
//         temp = temp->next;
//     }

//     int diff = 0;

//     if (lenA > lenB)
//     {
//         diff = lenA - lenB;

//         ListNode *swapTemp = headA;
//         headA = headB;
//         headB = swapTemp;
//     }
//     else
//     {
//         diff = lenB - lenA;
//     }

//     ListNode *tempA = headA, *tempB = headB;

//     while (diff)
//     {
//         tempB = tempB->next;
//         diff--;
//     }

//     while (tempA && tempB)
//     {
//         if (tempA == tempB)
//             return tempA;

//         tempA = tempA->next;
//         tempB = tempB->next;
//     }

//     return NULL;
// }

/*
==================================================
OPTIMAL APPROACH (TWO POINTER SWITCHING)

Idea:
Traverse both linked lists using two pointers.
When a pointer reaches the end of one list, redirect it to the head of the other list.
After traversing equal distances, both pointers will meet at the intersection node.

Time Complexity: O(M + N)
Space Complexity: O(1)
==================================================
*/

ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
{
    if (!headA || !headB)
        return NULL;

    ListNode *tempA = headA, *tempB = headB;

    while (tempA != tempB)
    {
        tempA = tempA->next;
        tempB = tempB->next;

        if (tempA == tempB)
            return tempA;

        if (tempA == NULL)
            tempA = headB;

        if (tempB == NULL)
            tempB = headA;
    }

    return tempA;
}

int main()
{
    ListNode *head1 = NULL;
    insertNode(head1, 1);
    insertNode(head1, 3);
    insertNode(head1, 1);
    insertNode(head1, 2);
    insertNode(head1, 4);

    ListNode *intersection = head1->next->next->next;

    ListNode *head2 = NULL;
    insertNode(head2, 3);
    head2->next = intersection;

    cout << "List1: ";
    printList(head1);

    cout << "List2: ";
    printList(head2);

    ListNode *answerNode = getIntersectionNode(head1, head2);

    if (answerNode == NULL)
        cout << "No intersection\n";
    else
        cout << "The intersection point is " << answerNode->val << endl;

    return 0;
}