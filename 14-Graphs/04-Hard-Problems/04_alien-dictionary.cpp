// ==================================================
// PROBLEM
// - Given a sorted dictionary of an alien language with N words and K alphabets, find a valid character order.
// - If the given arrangement is inconsistent with any possible letter ordering, return an empty string.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// ALIEN DICTIONARY — TOPOLOGICAL SORT (KAHN'S ALGORITHM) APPROACH
//
// Idea:
// - Compare adjacent words in the dictionary to find the first differing character, which establishes a directed edge (u -> v) in our alphabet graph.
// - Build an adjacency list for the K characters and perform a topological sort (BFS/Kahn's) to find a valid character sequence.
//
// Time Complexity: O(N * L + K) - Where N is the number of words, L is the max word length, and K is the number of alphabets.
// Space Complexity: O(K) - For the adjacency list, in-degree array, queue, and output sequence.
// ==================================================

vector<int> topologicalSort(int K, vector<vector<int>> &adj)
{
    vector<int> indegree(K);

    for (int i = 0; i < K; i++)
    {
        for (int adjNode : adj[i])
        {
            indegree[adjNode]++;
        }
    }

    queue<int> q;

    for (int i = 0; i < K; i++)
    {
        if (indegree[i] == 0)
            q.push(i);
    }

    vector<int> res;

    while (!q.empty())
    {
        int node = q.front();
        q.pop();

        res.push_back(node);

        for (int adjNode : adj[node])
        {
            indegree[adjNode]--;

            if (indegree[adjNode] == 0)
                q.push(adjNode);
        }
    }

    return res;
}

string findOrder(const vector<string> &dict, int N, int K)
{
    // Adjacency list for K alphabets
    vector<vector<int>> adj(K);

    // Build the graph by comparing adjacent words
    for (int i = 0; i < N - 1; i++)
    {
        string s1 = dict[i], s2 = dict[i + 1];

        int len = min(s1.size(), s2.size());

        bool elemCompared = false;

        // Find the first mismatching character to deduce relative order
        for (int ptr = 0; ptr < len; ptr++)
        {
            if (s1[ptr] != s2[ptr])
            {
                // Create a directed edge from the earlier character to the later one
                adj[s1[ptr] - 'a'].push_back(s2[ptr] - 'a');
                elemCompared = true;
                break;
            }
        }

        // Edge case: If s1 is a prefix of s2 but s1 is longer, the dictionary is invalid
        // (e.g., "abcd" appearing before "abc" is impossible in a sorted dictionary)
        if (!elemCompared && (s1.size() > s2.size()))
            return "";
    }

    // Retrieve the valid character ordering using Kahn's algorithm
    vector<int> topoSort = topologicalSort(K, adj);

    // If the graph contains a cycle, a valid topological sort is impossible
    if (topoSort.size() != K)
        return "";

    string res = "";

    // Convert integer representations back to characters
    for (int it : topoSort)
    {
        res += char(it + 'a');
    }

    return res;
}

int main()
{
    int N = 5, K = 4;

    vector<string> dict = {
        "baa", "abcd", "abca", "cab", "cad"};

    string ans = findOrder(dict, N, K);

    cout << "The order to characters as per alien dictionary is: " << ans;

    return 0;
}
