// ==================================================
// PROBLEM
// - Given nums (non-negative integers) and queries[i] = [xi, mi].
// - For each query, return the maximum of nums[j] XOR xi where nums[j] <= mi.
// - If every element of nums is larger than mi, the answer is -1.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// OFFLINE QUERIES + BINARY TRIE APPROACH
//
// Idea:
// - Sort nums in ascending order so the valid elements form a prefix.
// - Sort the queries by their limit mi, remembering each original index.
// - Process queries in increasing mi and insert only elements that are <= mi into the trie.
// - Because mi never decreases, each element is inserted into the trie exactly once.
// - If no element has been inserted yet, the answer is -1.
// - Otherwise, walk the trie from bit 31 down to bit 0, preferring the opposite bit at each level.
// - Store each answer at its original query index.
//
// Time Complexity: O(N log N + Q log Q + 32 * (N + Q)) - Sorting plus 32-bit trie work per insert and query.
// Space Complexity: O(32 * N + Q) - Trie nodes for N numbers plus storage for the sorted queries and answers.
// ==================================================

// Trie node: one bit position along a number's path.
struct Node
{
private:
    // links[0] is the child for bit 0, links[1] is the child for bit 1.
    Node *links[2] = {nullptr};

public:
    // Recursively free the whole subtree below this node.
    // Deleting a null child is safe, so no explicit null check is needed.
    ~Node()
    {
        for (auto &child : links)
        {
            delete child;
        }
    }

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
    Node *nextReferenceNode(int bit)
    {
        return links[bit];
    }
};

class Trie
{
private:
    // Root is an empty sentinel node. It holds no bit itself.
    Node *root;

public:
    // Create the empty root node.
    Trie()
    {
        root = new Node();
    }

    // Deleting the root triggers ~Node() recursively, which frees every node in the trie.
    ~Trie()
    {
        delete root;
    }

    // Insert a number into the trie, from the most significant bit to the least significant bit.
    void insert(int num)
    {
        Node *referenceNode = root;

        for (int i = 31; i >= 0; i--)
        {
            int bit = (num >> i) & 1;

            // Create the child node only when this bit is not on the path yet
            if (!referenceNode->containsKey(bit))
                referenceNode->insertKey(bit, new Node());

            // Move down to the child for this bit
            referenceNode = referenceNode->nextReferenceNode(bit);
        }
    }

    // Returns the maximum XOR of num with any number already inserted.
    int getMaxXOR(int num)
    {
        Node *referenceNode = root;

        // Builds the XOR result bit by bit
        int maxi = 0;

        for (int i = 31; i >= 0; i--)
        {
            int bit = (num >> i) & 1;

            if (!referenceNode->containsKey(!bit))
            {
                // No opposite bit available, so this XOR bit stays 0
                referenceNode = referenceNode->nextReferenceNode(bit);
            }
            else
            {
                // Opposite bit exists, so this XOR bit becomes 1
                maxi |= (1 << i);
                referenceNode = referenceNode->nextReferenceNode(!bit);
            }
        }

        return maxi;
    }
};

vector<int> maximizeXor(vector<int> &nums, vector<vector<int>> &queries)
{
    sort(nums.begin(), nums.end());

    // Each entry is {mi, {xi, original query index}}
    vector<pair<int, pair<int, int>>> offlineQueries;

    int idx = 0;
    for (auto &it : queries)
    {
        offlineQueries.push_back({it[1], {it[0], idx++}});
    }

    // Sort by mi so the set of valid elements only grows from query to query
    sort(offlineQueries.begin(), offlineQueries.end());

    // Reuse idx as the pointer to the next element of nums to insert
    idx = 0;

    int n = nums.size();

    Trie trie;

    vector<int> ans(queries.size(), 0);

    for (auto &it : offlineQueries)
    {
        int mI = it.first;
        int xI = it.second.first;
        int queryIdx = it.second.second;

        // Insert every element that is within the current limit
        while (idx < n && nums[idx] <= mI)
        {
            trie.insert(nums[idx++]);
        }

        // Nothing was inserted, so every element exceeds mi
        if (idx == 0)
            ans[queryIdx] = -1;
        else
            ans[queryIdx] = trie.getMaxXOR(xI);
    }

    return ans;
}

int main()
{
    vector<int> nums = {0, 1, 2, 3, 4};

    vector<vector<int>> queries = {{3, 1}, {1, 3}, {5, 6}};

    vector<int> result = maximizeXor(nums, queries);

    // Expected: 3, 3, 7
    cout << "Result of Max XOR Queries:" << endl;
    for (int i = 0; i < result.size(); ++i)
    {
        cout << "Query " << i + 1 << ": " << result[i] << endl;
    }

    return 0;
}