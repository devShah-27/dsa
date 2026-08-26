// Problem:
// Given a linked list where each node has next and random pointers, create a deep copy of the linked list with the same values and pointer relationships.
// Return the head of the newly created cloned linked list.

#include <bits/stdc++.h>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode *random;

    ListNode()
    {
        val = 0;
        next = NULL;
        random = NULL;
    }

    ListNode(int data1)
    {
        val = data1;
        next = NULL;
        random = NULL;
    }

    ListNode(int data1, ListNode *next1, ListNode *r)
    {
        val = data1;
        next = next1;
        random = r;
    }
};

void printClonedLinkedList(ListNode *head)
{
    while (head != nullptr)
    {
        cout << "Data: " << head->val;

        if (head->random != nullptr)
        {
            cout << ", Random: " << head->random->val;
        }
        else
        {
            cout << ", Random: nullptr";
        }

        cout << endl;

        head = head->next;
    }
}

/*
==================================================
BRUTE FORCE APPROACH (HASH MAP)

Idea:
Create a copy of every node and store the mapping between original nodes and their corresponding cloned nodes.
Use this mapping to correctly assign next and random pointers.

Time Complexity: O(N)
Space Complexity: O(N)
==================================================
*/
// ListNode *copyRandomList(ListNode *head)
// {
//     if (!head)
//         return nullptr;

//     ListNode *temp = head;

//     unordered_map<ListNode *, ListNode *> mpp;

//     while (temp)
//     {
//         mpp[temp] = new ListNode(temp->val);
//         temp = temp->next;
//     }

//     temp = head;

//     while (temp)
//     {
//         ListNode *copyNode = mpp[temp];

//         copyNode->next = mpp[temp->next];
//         copyNode->random = mpp[temp->random];

//         temp = temp->next;
//     }

//     return mpp[head];
// }

/*
==================================================
OPTIMAL APPROACH (INTERWEAVING LINKED LIST)

Idea:
Insert cloned nodes in between their corresponding original nodes.
Use the interleaved structure to assign random pointers without extra space.
Finally, separate the original and cloned linked lists.

Time Complexity: O(3N) == O(N)
Space Complexity: O(1) excluding the space required for cloned nodes
==================================================
*/

// Step 1: Insert cloned nodes between original nodes.
void insertNodeCopiesInBetween(ListNode *head)
{
    ListNode *temp = head;

    while (temp)
    {
        ListNode *copyNode = new ListNode(temp->val);
        copyNode->next = temp->next;
        temp->next = copyNode;
        temp = temp->next->next;
    }
}

// Step 2: Assign random pointers of cloned nodes.
void assignRandomPointers(ListNode *head)
{
    ListNode *temp = head;

    while (temp)
    {
        ListNode *copyNode = temp->next;
        if (temp->random != nullptr)
            copyNode->random = temp->random->next;
        else
            copyNode->random = nullptr;
        temp = temp->next->next;
    }
}

// Step 3: Separate cloned list from the original list.
ListNode *removeNodeCopies(ListNode *head)
{
    ListNode *dummy = new ListNode(-1);
    ListNode *res = dummy;
    ListNode *temp = head;
    
    while (temp)
    {
        res->next = temp->next;
        temp->next = temp->next->next;
        res = res->next;
        temp = temp->next;
    }

    return dummy->next;
}

ListNode *copyRandomList(ListNode *head)
{
    if (!head)
        return nullptr;

    insertNodeCopiesInBetween(head);

    assignRandomPointers(head);

    return removeNodeCopies(head);
}

int main()
{
    ListNode *head = new ListNode(7);
    head->next = new ListNode(14);
    head->next->next = new ListNode(21);
    head->next->next->next = new ListNode(28);

    head->random = head->next->next;
    head->next->random = head;
    head->next->next->random = head->next->next->next;
    head->next->next->next->random = head->next;

    cout << "Original Linked List with Random Pointers:" << endl;
    printClonedLinkedList(head);

    ListNode *clonedList = copyRandomList(head);

    cout << "\nCloned Linked List with Random Pointers:" << endl;
    printClonedLinkedList(clonedList);

    return 0;
}