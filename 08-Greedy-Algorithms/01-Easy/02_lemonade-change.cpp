// Problem:
// Given customers paying with $5, $10, or $20 bills for a $5 lemonade, determine whether correct change can be provided to every customer in order.
// Return true if all transactions can be completed successfully, otherwise false.

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// GREEDY APPROACH
//
// Idea:
// Maintain the count of available $5 and $10 bills while processing customers in order.
// For a $20 bill, prefer using one $10 and one $5 as change because preserving $5 bills gives more flexibility for future transactions.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// ==================================================

bool lemonadeChange(vector<int> &bills)
{
    int fiveChange = 0, tenChange = 0;

    for (int it : bills)
    {
        if (it == 5)
        {
            fiveChange++;
        }
        else if (it == 10)
        {
            if (fiveChange)
            {
                fiveChange--;
                tenChange++;
            }
            else
            {
                return false;
            }
        }
        else
        {
            if (tenChange && fiveChange)
            {
                fiveChange--;
                tenChange--;
            }
            else if (fiveChange >= 3)
            {
                fiveChange -= 3;
            }
            else
            {
                return false;
            }
        }
    }

    return true;
}

int main()
{
    vector<int> bills = {5, 5, 5, 10, 20};
    cout << "Queues of customers: ";

    for (int bill : bills)
    {
        cout << bill << " ";
    }
    cout << endl;

    bool ans = lemonadeChange(bills);

    if (ans)
        cout << "It is possible to provide change for all customers." << endl;
    else
        cout << "It is not possible to provide change for all customers." << endl;

    return 0;
}