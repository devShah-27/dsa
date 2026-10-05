// ==================================================
// PROBLEM
// - Given a string s, count its distinct substrings, including the empty substring.
// - A substring is formed by removing characters from the start and end of s.
// - Two substrings are different if they differ at any index.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// BRUTE FORCE APPROACH
//
// Idea:
// - Generate every substring by fixing a start index i and extending the end index j one character at a time.
// - Insert each substring into a set, which discards duplicates.
// - Insert the empty string separately, because the loops never build it.
// - The final set size is the number of distinct substrings.
//
// Time Complexity: O(N^3 log N) - O(N^2) substrings, each insert costs O(N log N) comparisons.
// Space Complexity: O(N^3) - The set stores every distinct substring in the worst case.
// ==================================================

int countDistinctSubstring(const string &s)
{
    int n = s.size();

    // Stores each distinct substring exactly once
    set<string> st;

    for (int i = 0; i < n; i++)
    {
        string temp = "";

        for (int j = i; j < n; j++)
        {
            // Extend the current substring by one character, then store it
            temp += s[j];
            st.insert(temp);
        }
    }

    // The empty substring is valid but never built by the loops above
    st.insert("");

    return st.size();
}

// ==================================================
// OPTIMAL APPROACH (TRIE)
//
// Idea:
// - Insert every suffix of s into a trie, one character at a time.
// - Every substring is a prefix of some suffix, so each trie node represents one distinct substring.
// - Increment the counter only when a new node is created.
// - Reusing an existing node means that substring was already counted.
// - Add 1 at the end to include the empty substring.
//
// Time Complexity: O(N^2) - Each of the N suffixes is inserted in O(N).
// Space Complexity: O(26 * N^2) worst case - Up to N^2 nodes, each holding 26 links.
// ==================================================

// Trie node: one character position along a substring's path.
struct Node
{
private:
    // links[i] points to the child for the letter 'a' + i. Null means no such child.
    Node *links[26] = {nullptr};

public:
    // Recursively free the whole subtree below this node.
    // Deleting a null child is safe, so no explicit null check is needed.
    ~Node()
    {
        for (Node *child : links)
            delete child;
    }

    // Check whether a child node exists for the given character.
    bool containsKey(char ch)
    {
        return links[ch - 'a'] != nullptr;
    }

    // Attach a child node to the slot for the given character.
    void insertReference(char ch, Node *nextNode)
    {
        links[ch - 'a'] = nextNode;
    }

    // Return the child node for the given character (may be null).
    Node *getNextReference(char ch)
    {
        return links[ch - 'a'];
    }
};

// NOTE: Assumes lowercase 'a'-'z' only. Other characters index out of bounds.
int countDistinctSubstring(const string &s)
{
    int n = s.size();

    Node *root = new Node();

    // Counts the non-empty distinct substrings (one per newly created node)
    int cnt = 0;

    for (int i = 0; i < n; i++)
    {
        // Restart from the root for the suffix beginning at index i
        Node *newNode = root;

        for (int j = i; j < n; j++)
        {
            // A missing link means this substring appears for the first time
            if (!newNode->containsKey(s[j]))
            {
                cnt++;
                newNode->insertReference(s[j], new Node());
            }

            // Move down to the child for this letter
            newNode = newNode->getNextReference(s[j]);
        }
    }

    delete root;

    // Add 1 for the empty substring
    return cnt + 1;
}

int main()
{
    string input = "abc";

    cout << "Number of distinct substrings: " << countDistinctSubstring(input) << endl;

    return 0;
}