// ==================================================
// PROBLEM
// - Given a list of accounts where each entry contains a name followed by emails, merge accounts that share at least one common email.
// - Return the merged accounts with the account name first, followed by its emails in sorted order.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// ACCOUNTS MERGE — DISJOINT SET UNION (DSU) & HASH MAP APPROACH
//
// Idea:
// - Treat each account index as a node in a graph.
// - Map each unique email to an account index.
// - If an email has been seen in an earlier account, union the two account indices using DSU.
// - Afterward, group all emails by their ultimate root parent account, sort the emails for each component, and attach the account name.
//
// Time Complexity: O(E * α(N) * L + E * log(E) * L) - Where N is accounts, E is total emails, L is max email length, and α is the Inverse Ackermann function.
// Space Complexity: O(N + E * L) - For the DSU parent/size arrays, hash map, and merged email lists.
// ==================================================

class DisjointSet
{
    vector<int> size, parent;

public:
    // Initialize DSU for n account indices
    DisjointSet(int n)
    {
        size.resize(n + 1, 1);
        parent.resize(n + 1);

        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }

    // Finds the ultimate representative (root) with path compression
    int findUltimateParent(int node)
    {
        if (parent[node] == node)
            return node;

        return parent[node] = findUltimateParent(parent[node]);
    }

    // Merges two components based on subtree size
    void unionBySize(int u, int v)
    {
        int uRoot = findUltimateParent(u);
        int vRoot = findUltimateParent(v);

        // Already in the same connected component
        if (uRoot == vRoot)
            return;

        // Attach smaller tree under larger tree
        if (size[uRoot] < size[vRoot])
        {
            parent[uRoot] = vRoot;
            size[vRoot] += size[uRoot];
        }
        else
        {
            parent[vRoot] = uRoot;
            size[uRoot] += size[vRoot];
        }
    }
};

vector<vector<string>> accountsMerge(const vector<vector<string>> &accounts)
{
    int n = accounts.size();

    DisjointSet ds(n);

    // Map each email to the first account index where it appears
    unordered_map<string, int> emailToIndex;

    // Step 1: Connect accounts sharing common emails
    for (int i = 0; i < n; i++)
    {
        for (int j = 1; j < accounts[i].size(); j++)
        {
            string email = accounts[i][j];

            // If email is encountered for the first time, associate it with current account index
            if (emailToIndex.find(email) == emailToIndex.end())
            {
                emailToIndex[email] = i;
            }
            // If email already exists, union current account with the previously recorded account
            else
            {
                ds.unionBySize(i, emailToIndex[email]);
            }
        }
    }

    // Step 2: Group all unique emails under the ultimate root parent of their account
    vector<vector<string>> indexToEmail(n);

    for (const auto &it : emailToIndex)
    {
        string email = it.first;
        int node = ds.findUltimateParent(it.second);

        indexToEmail[node].push_back(email);
    }

    // Step 3: Format the merged output with sorted emails and account names
    vector<vector<string>> result;

    for (int i = 0; i < indexToEmail.size(); i++)
    {
        // Skip accounts that were merged into other roots
        if (indexToEmail[i].empty())
            continue;

        vector<string> temp;

        // Attach account name corresponding to root index
        temp.push_back(accounts[i][0]);

        // Sort emails lexicographically
        sort(indexToEmail[i].begin(), indexToEmail[i].end());

        for (const string &email : indexToEmail[i])
        {
            temp.push_back(email);
        }

        result.push_back(temp);
    }

    return result;
}

int main()
{
    int n = 4;

    // Input accounts format: [Name, email1, email2, ...]
    vector<vector<string>> accounts = {
        {"John", "johnsmith@mail.com", "john_newyork@mail.com"},
        {"John", "johnsmith@mail.com", "john00@mail.com"},
        {"Mary", "mary@mail.com"},
        {"John", "johnnybravo@mail.com"}};

    vector<vector<string>> ans;

    ans = accountsMerge(accounts);

    cout << "The mareged accounts are:\n";
    for (int i = 0; i < ans.size(); i++)
    {
        for (int j = 0; j < ans[i].size(); j++)
        {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
