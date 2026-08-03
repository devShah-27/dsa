// Each lemonade at a booth sells for $5. Consumers are lining up to place individual orders, following the billing order. Every consumer will purchase a single lemonade and may pay with a $5, $10, or $20 bill. Each customer must receive the appropriate change so that the net transaction is $5. Initially, there is no change available.

// Determine if it is possible to provide the correct change to every customer. Return true if the correct change can be given to every customer, and false otherwise.

// Given an integer array bills, where bills[i] is the bill the ith customer pays, return true if the correct change can be given to every customer, and false otherwise.

#include <bits/stdc++.h>
using namespace std;

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
