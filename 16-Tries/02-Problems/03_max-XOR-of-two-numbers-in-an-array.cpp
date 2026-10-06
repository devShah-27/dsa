// ==================================================
// PROBLEM
// - Given an integer array nums, return the maximum value of nums[i] XOR nums[j].
// - The indices must satisfy 0 <= i <= j < n.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// BINARY TRIE APPROACH
//
// Idea:
// - Insert every number into a binary trie, one bit at a time, from the most significant bit (bit 31) down to bit 0.
// - To maximize XOR with a number, each bit of the result should be 1, so we want the opposite bit at every level.
// - For each number, walk the trie from the top bit down.
// - Go to the opposite bit if that child exists.
// - If the opposite child is missing, follow the same bit and  that result bit stays 0.
// - The answer is the maximum XOR found across all numbers.
//
// Time Complexity: O(32 * N) - Each insert and each query walks 32 bits.
// Space Complexity: O(32 * N) - Up to 32 new nodes per inserted number.
// ==================================================

// Trie node: one bit position along a number's path.
struct Node
{
private:
    // links[0] is the child for bit 0, links[1] is the child for bit 1.
    Node *links[2] = {nullptr};

public:
    // Check whether a child node exists for the given bit.
    bool containsKey(int bit)
    {
        return (links[bit] != nullptr);
    }

    // Attach a child node to the slot for the given bit.
    void insertKey(int bit, Node *nextNode)
    {
        links[bit] = nextNode;
    }

    // Return the child node for the given bit (may be null).
    Node *getNextReference(int bit)
    {
        return links[bit];
    }
};

class Trie
{
    // Root is an empty sentinel node. It holds no bit itself.
    Node *root;

public:
    // Create the empty root node.
    Trie()
    {
        root = new Node();
    }

    void insert(int num)
    {
        Node *referenceNode = root;

        // Process bits from the most significant to the least significant
        for (int i = 31; i >= 0; i--)
        {
            int bit = (num >> i) & 1;

            // Create the child node only when this bit is not on the path yet
            if (!referenceNode->containsKey(bit))
                referenceNode->insertKey(bit, new Node());

            // Move down to the child for this bit
            referenceNode = referenceNode->getNextReference(bit);
        }
    }

    // Returns the maximum XOR of num with any number already inserted.
    int getMax(int num)
    {
        Node *referenceNode = root;

        // Builds the XOR result bit by bit
        int maxi = 0;

        for (int i = 31; i >= 0; i--)
        {
            int bit = (num >> i) & 1;

            if (!referenceNode->containsKey(1 - bit))
            {
                // No opposite bit available, so this XOR bit stays 0
                referenceNode = referenceNode->getNextReference(bit);
            }
            else
            {
                // Opposite bit exists, so this XOR bit becomes 1
                maxi = maxi | (1 << i);
                referenceNode = referenceNode->getNextReference(1 - bit);
            }
        }

        return maxi;
    }
};

int findMaximumXOR(vector<int> &nums)
{
    Trie trie;

    // Build the trie from all numbers
    for (auto &it : nums)
    {
        trie.insert(it);
    }

    // Starting from 0 is safe because XOR of any pair is non-negative here
    int maxRes = 0;

    // Query the best XOR partner for every number
    for (auto &it : nums)
    {
        maxRes = max(maxRes, trie.getMax(it));
    }

    return maxRes;
}

int main()
{
    vector<int> nums = {3, 10, 5, 25, 2, 8};

    cout << "Input: ";
    for (int num : nums)
    {
        cout << num << " ";
    }
    cout << endl;

    int result = findMaximumXOR(nums);

    cout << "Maximum XOR value: " << result << endl;

    return 0;
}