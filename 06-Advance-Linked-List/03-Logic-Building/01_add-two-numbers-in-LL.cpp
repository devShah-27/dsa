// Problem:
// Given two non-empty linked lists representing two non-negative integers, add the two numbers and return the sum as a linked list.
// Digits are stored in reverse order, with each node containing a single digit.

#include <bits/stdc++.h>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;

    // Default constructor.
    ListNode()
    {
        val = 0;
        next = NULL;
    }

    // Constructor to initialize node value.
    ListNode(int data1)
    {
        val = data1;
        next = NULL;
    }

    // Constructor to initialize node value and next pointer.
    ListNode(int data1, ListNode *next1)
    {
        val = data1;
        next = next1;
    }
};

void printList(ListNode *head)
{
    while (head != NULL)
    {
        cout << head->val << " ";
        head = head->next;
    }

    cout << endl;
}

// ============================================================================
// ADD TWO NUMBERS USING LINKED LIST TRAVERSAL
//
// Idea:
// Traverse both linked lists simultaneously and add corresponding digits along with the carry from the previous addition.
// Create a new node for each resulting digit and continue until both lists and the remaining carry are processed.
//
// Time Complexity: O(max(N, M))
// Space Complexity: O(max(N, M))   // Space used by the result linked list.
// ============================================================================

ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
{
    // Dummy node simplifies handling the result list's first node.
    ListNode *dummyNode = new ListNode(-1);

    ListNode *curr = dummyNode;

    int carry = 0;

    ListNode *temp1 = l1;
    ListNode *temp2 = l2;

    while (temp1 != NULL || temp2 != NULL || carry)
    {
        int digitSum = carry;

        // Add current digit from first linked list.
        if (temp1)
            digitSum += temp1->val;

        // Add current digit from second linked list.
        if (temp2)
            digitSum += temp2->val;

        // Extract current digit and carry for next position.
        int addDigit = digitSum % 10;
        carry = digitSum / 10;

        ListNode *newSumDigit = new ListNode(addDigit);

        curr->next = newSumDigit;

        // Move to next digits.
        if (temp1)
            temp1 = temp1->next;

        if (temp2)
            temp2 = temp2->next;

        curr = curr->next;
    }

    return dummyNode->next;
}

int main()
{
    // l1 represents: 9999999999
    ListNode *l1 = new ListNode(
        9,
        new ListNode(
            9,
            new ListNode(
                9,
                new ListNode(
                    9,
                    new ListNode(
                        9,
                        new ListNode(
                            9,
                            new ListNode(
                                9,
                                new ListNode(
                                    9,
                                    new ListNode(9)))))))));

    // l2 represents: 1
    ListNode *l2 = new ListNode(1);

    ListNode *result = addTwoNumbers(l1, l2);

    printList(result);

    return 0;
}