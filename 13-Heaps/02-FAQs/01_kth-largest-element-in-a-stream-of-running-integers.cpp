// Problem:
// Implement a KthLargest class that tracks the kth largest element in a stream of numbers.
// Initialize it with k and an initial array, then return the kth largest element after each new value is added.

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// OPTIMAL APPROACH
// Idea:
// - Maintain a min-heap containing only the k largest elements seen so far.
// - The smallest element among these k elements is at the root, which is exactly the kth largest element.
// - For every new value, add it only if it belongs to the current k largest elements.
//
// Time Complexity:
// Constructor -> O(N log K), where N is the number of initial elements
// add()       -> O(log K)
// Space Complexity: O(K)
// ==================================================

class KthLargest
{
    priority_queue<int, vector<int>, greater<int>> pq;
    int k;

public:
    KthLargest(int k, vector<int> &nums)
    {
        this->k = k;

        // Keep only the k largest elements from the initial stream.
        for (int i = 0; i < nums.size(); i++)
        {
            if (pq.size() < k)
            {
                pq.push(nums[i]);
            }
            else
            {
                if (nums[i] > pq.top())
                {
                    pq.pop();
                    pq.push(nums[i]);
                }
            }
        }
    }

    int add(int val)
    {
        // If fewer than k elements exist, the new value must be included.
        if (pq.size() < k)
        {
            pq.push(val);
            return pq.top();
        }

        // Replace the current kth largest if the new value is larger.
        if (val > pq.top())
        {
            pq.pop();
            pq.push(val);
        }

        return pq.top();
    }
};

int main()
{
    int k = 3;
    vector<int> nums = {1, 2, 3, 4};

    KthLargest kthLargest(k, nums);

    cout << "Kth Largest element after adding 5 is: " << kthLargest.add(5) << endl;
    cout << "Kth Largest element after adding 2 is: " << kthLargest.add(2) << endl;
    cout << "Kth Largest element after adding 7 is: " << kthLargest.add(7) << endl;

    return 0;
}