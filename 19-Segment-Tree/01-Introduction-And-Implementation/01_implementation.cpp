// ==================================================
// SEGMENT TREE (RANGE SUM + POINT UPDATE)
//
// Problem:
// - Given an integer array nums, support range sum queries and point updates efficiently.
// - query(l, r): Return the sum of nums[l...r] (inclusive).
// - update(idx, val): Set nums[idx] = val.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// SEGMENT TREE
//
// Idea:
// - Each node stores the sum of its corresponding array segment.
// - The root represents the entire array.
// - Each internal node has two children representing the left and right halves of its segment.
// - Build the tree recursively, then use it for queries and updates.
//
// Time Complexity:
// - Build: O(N)
// - Point Update: O(log N)
// - Range Sum Query: O(log N)
//
// Space Complexity: O(N) - Segment tree array of size 4 * N.
// ==================================================

class SegTree {
  private:
    int n;
    vector<long long> tree;

    // Builds the segment tree for the inclusive range [l, r]
    void build(vector<int> &nums, int node, int l, int r) {
        // Base case: leaf node represents a single array element
        if (l == r) {
            tree[node] = nums[l];
            return;
        }

        int mid = l + (r - l) / 2;

        // Build the left and right subtrees
        build(nums, 2 * node + 1, l, mid);
        build(nums, 2 * node + 2, mid + 1, r);

        // Merge the children by summing their segment sums
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }

    // Updates nums[idx] to val and fixes sums along the path to the root
    void update(int node, int l, int r, int idx, int val) {
        // Base case: reached the leaf representing idx
        if (l == r) {
            tree[node] = val;
            return;
        }

        int mid = l + (r - l) / 2;

        // Recurse into the child containing idx
        if (idx <= mid)
            update(2 * node + 1, l, mid, idx, val);
        else
            update(2 * node + 2, mid + 1, r, idx, val);

        // Recalculate the current node after updating its child
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }

    // Returns the sum of the intersection between [l, r] and [ql, qr]
    long long query(int node, int l, int r, int ql, int qr) {
        // No overlap: the current segment is outside the query range
        if (qr < l || r < ql)
            return 0;

        // Complete overlap: the current segment lies entirely inside the query
        if (ql <= l && r <= qr)
            return tree[node];

        // Partial overlap: query both children and combine their results
        int mid = l + (r - l) / 2;

        long long leftSum = query(2 * node + 1, l, mid, ql, qr);
        long long rightSum = query(2 * node + 2, mid + 1, r, ql, qr);

        return leftSum + rightSum;
    }

  public:
    // Initializes the segment tree and builds it from nums
    SegTree(vector<int> &nums) {
        n = nums.size();
        tree.resize(4 * n, 0);

        if (n > 0)
            build(nums, 0, 0, n - 1);
    }

    // Public point update: set nums[idx] = val
    void update(int idx, int val) {
        if (n > 0 && idx >= 0 && idx < n)
            update(0, 0, n - 1, idx, val);
    }

    // Public range sum query for the inclusive range [l, r]
    long long query(int l, int r) {
        if (n == 0 || l < 0 || r >= n || l > r)
            return 0;

        return query(0, 0, n - 1, l, r);
    }
};

int main() {
    vector<int> nums = {1, 3, 5, 7, 9, 11};

    SegTree st(nums);

    cout << st.query(1, 3) << endl;

    st.update(2, 10);

    cout << st.query(1, 3) << endl;

    cout << st.query(0, 5) << endl;

    return 0;
}
