// ==================================================
// PROBLEM
// - Design a Disjoint Set (Union-Find) data structure supporting initialization of n elements, union by rank, union by size, path compression, and connectivity queries between any two elements.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// DISJOINT SET UNION (DSU) — PATH COMPRESSION WITH RANK & SIZE HEURISTICS
//
// Idea:
// - Represent sets as trees where each node points to its parent.
// - Path compression flattens the tree during find queries by linking visited nodes directly to the root.
// - Union by rank/size attaches the smaller/shallower tree under the root of the larger tree to keep tree height minimal.
//
// Time Complexity: O(4 * α) ≈ O(1) amortized per find/union operation, where α is the Inverse Ackermann function.
// Space Complexity: O(N) - For parent, rank, and size vectors.
// ==================================================

class DisjointSet
{
    vector<int> rank_;
    vector<int> size_;
    vector<int> parent_;

private:
    // Finds the ultimate representative (root) of the set with path compression
    int findUltimateParent(int node)
    {
        // Base case: If the node is its own parent, it is the root
        if (parent_[node] == node)
            return node;

        // Path compression: Connect current node directly to the set's root
        return parent_[node] = findUltimateParent(parent_[node]);
    }

public:
    // Initialize 1-based indexing for parent, rank, and size tracking
    DisjointSet(int n)
    {
        rank_.resize(n + 1, 0);

        size_.resize(n + 1, 1);

        parent_.resize(n + 1);

        // Initially, each element is its own parent
        for (int i = 0; i <= n; i++)
        {
            parent_[i] = i;
        }
    }

    // Check if elements u and v belong to the same connected component
    bool find(int u, int v)
    {
        int uRoot = findUltimateParent(u);
        int vRoot = findUltimateParent(v);

        return uRoot == vRoot;
    }

    // NOTE: Mixing unionByRank and unionBySize on the same DSU instance does not update both rank and size metadata simultaneously.
    void unionByRank(int u, int v)
    {
        int uRoot = findUltimateParent(u);
        int vRoot = findUltimateParent(v);

        // Already in the same set
        if (uRoot == vRoot)
            return;

        // Attach smaller rank tree under larger rank tree
        if (rank_[uRoot] < rank_[vRoot])
        {
            parent_[uRoot] = vRoot;
        }
        else if (rank_[vRoot] < rank_[uRoot])
        {
            parent_[vRoot] = uRoot;
        }
        // If ranks are equal, attach arbitrarily and increment the root's rank
        else
        {
            parent_[vRoot] = uRoot;
            rank_[uRoot]++;
        }
    }

    // Merge components based on the total number of nodes in each subtree
    void unionBySize(int u, int v)
    {
        int uRoot = findUltimateParent(u);
        int vRoot = findUltimateParent(v);

        // Already in the same set
        if (uRoot == vRoot)
            return;

        // Attach smaller sized tree under larger sized tree and aggregate sizes
        if (size_[uRoot] < size_[vRoot])
        {
            parent_[uRoot] = vRoot;
            size_[vRoot] += size_[uRoot];
        }
        else
        {
            parent_[vRoot] = uRoot;
            size_[uRoot] += size_[vRoot];
        }
    }
};

int main()
{
    DisjointSet ds(10);

    // ==================================================
    // COMPONENT 1: {1, 2, 3, 4}
    // ==================================================

    ds.unionByRank(1, 2);
    ds.unionByRank(2, 3);
    ds.unionByRank(3, 4);

    cout << boolalpha;

    cout << "1 and 4 connected: "
         << ds.find(1, 4) << '\n'; // true

    cout << "1 and 5 connected: "
         << ds.find(1, 5) << '\n'; // false

    // ==================================================
    // COMPONENT 2: {5, 6, 7}
    // ==================================================

    ds.unionBySize(5, 6);
    ds.unionBySize(6, 7);

    cout << "5 and 7 connected: "
         << ds.find(5, 7) << '\n'; // true

    cout << "4 and 7 connected: "
         << ds.find(4, 7) << '\n'; // false

    // ==================================================
    // MERGE COMPONENT 1 + COMPONENT 2
    // Result: {1, 2, 3, 4, 5, 6, 7}
    // ==================================================

    ds.unionByRank(4, 5);

    cout << "1 and 7 connected after merge: "
         << ds.find(1, 7) << '\n'; // true

    cout << "2 and 6 connected after merge: "
         << ds.find(2, 6) << '\n'; // true

    // ==================================================
    // REDUNDANT UNION
    // Should do nothing because they're already connected
    // ==================================================

    ds.unionByRank(1, 7);
    ds.unionBySize(2, 6);
    ds.unionByRank(3, 5);

    cout << "1 and 7 after redundant unions: "
         << ds.find(1, 7) << '\n'; // true

    // ==================================================
    // ISOLATED COMPONENTS
    // {8}, {9}, {10}
    // ==================================================

    cout << "8 and 9 connected: "
         << ds.find(8, 9) << '\n'; // false

    cout << "8 and 8 connected: "
         << ds.find(8, 8) << '\n'; // true

    // ==================================================
    // BUILD COMPONENT 3
    // {8, 9, 10}
    // ==================================================

    ds.unionBySize(8, 9);
    ds.unionBySize(9, 10);

    cout << "8 and 10 connected: "
         << ds.find(8, 10) << '\n'; // true

    // ==================================================
    // MERGE TWO LARGE COMPONENTS
    //
    // Component A: {1,2,3,4,5,6,7}
    // Component B: {8,9,10}
    //
    // Final component: {1...10}
    // ==================================================

    ds.unionBySize(7, 8);

    cout << "1 and 10 connected: "
         << ds.find(1, 10) << '\n'; // true

    cout << "4 and 9 connected: "
         << ds.find(4, 9) << '\n'; // true

    cout << "3 and 10 connected: "
         << ds.find(3, 10) << '\n'; // true

    // ==================================================
    // FINAL CHECK
    // Every element should now belong to the same set.
    // ==================================================

    cout << "\nFinal connectivity:\n";

    for (int i = 1; i <= 10; i++)
    {
        for (int j = i + 1; j <= 10; j++)
        {
            if (!ds.find(i, j))
            {
                cout << "ERROR: "
                     << i << " and " << j
                     << " are not connected.\n";
                return 1;
            }
        }
    }

    cout << "All 10 elements belong to the same component.\n";

    return 0;
}
