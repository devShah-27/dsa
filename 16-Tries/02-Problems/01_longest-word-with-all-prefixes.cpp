// ==================================================
// PROBLEM
// - Given a string array nums, a string is complete if every prefix of it is also in nums.
// - Find the longest complete string in nums.
// - On equal length, return the lexicographically smallest one.
// - If no complete string exists, return "None".
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// TRIE APPROACH
//
// Idea:
// - Insert every word of nums into a trie.
// - Mark the node where each word ends.
// - A word is complete only if every node along its path is marked as a word end.
// - Walk each word through the trie and stop at the first node that is not a word end.
// - Keep the best complete word so far. 
// - Prefer the longer one, and on equal length prefer the smaller one.
//
// Time Complexity: O(N * L) - N words of max length L, inserted once and checked once.
// Space Complexity: O(26 * N * L) worst case - each trie node holds 26 links.
// ==================================================

// Trie node: one character position along a word's path.
struct Node
{
private:
    // links[i] points to the child for the letter 'a' + i. Null means no such child.
    Node *links[26] = {nullptr};

    // True if an inserted word ends at this node.
    bool wordEnd = false;

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
    void setReference(char ch, Node *nextReference)
    {
        links[ch - 'a'] = nextReference;
    }

    // Return the child node for the given character (may be null).
    Node *getNextReference(char ch)
    {
        return links[ch - 'a'];
    }

    // Mark that an inserted word ends at this node.
    void setWordEnd()
    {
        wordEnd = true;
    }

    // Check whether an inserted word ends at this node.
    bool doesWordEnd()
    {
        return wordEnd;
    }
};

class Trie
{
private:
    // Root is an empty sentinel node. It holds no character itself.
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

    // NOTE: Assumes lowercase 'a'-'z' only. Other characters index out of bounds.
    void insertWord(string &word)
    {
        Node *reference = root;

        for (int i = 0; i < word.size(); i++)
        {
            // Create the child node only when this letter is not on the path yet
            if (!reference->containsKey(word[i]))
                reference->setReference(word[i], new Node());

            // Move down to the child for this letter
            reference = reference->getNextReference(word[i]);
        }

        // The last node reached marks the end of an inserted word
        reference->setWordEnd();
    }

    // Returns true only if every prefix of the word (including the word itself) was inserted.
    bool containsWord(string &word)
    {
        Node *reference = root;

        for (int i = 0; i < word.size(); i++)
        {
            // NOTE: Never taken for words already inserted into this trie, kept as a defensive check.
            if (!reference->containsKey(word[i]))
                return false;

            reference = reference->getNextReference(word[i]);

            // This prefix was never inserted as a word, so the string is not complete
            if (reference->doesWordEnd() == false)
                return false;
        }

        return true;
    }
};

string completeString(vector<string> &nums)
{
    Trie trie;

    // Build the trie from all words
    for (auto &word : nums)
    {
        trie.insertWord(word);
    }

    string longestWord = "";

    // Check every word and track the best complete one
    for (auto &word : nums)
    {
        if (trie.containsWord(word))
        {
            // Prefer the longer word. On equal length, prefer the lexicographically smaller one.
            if ((word.size() > longestWord.size()) ||
                (word.size() == longestWord.size() && word < longestWord))
            {
                longestWord = word;
            }
        }
    }

    // No complete string found
    if (longestWord == "")
        return "None";

    return longestWord;
}

int main()
{
    vector<vector<string>> testCases = {
        {"n", "ni", "nin", "ninj", "ninja"},
        {"n", "ni", "nin", "ninj", "ninja", "ninga"},
        {"a", "ap", "app", "appl", "apple", "apply"},
        {"w", "wo", "wor", "worl", "world", "banana"},
        {"ab", "abc", "abcd"},
        {"cat", "ca", "c"},
        {"a", "b", "c"},
        {"apple", "app", "ap", "a", "banana", "ban", "b"}};

    for (int i = 0; i < testCases.size(); i++)
    {
        cout << "Test Case " << i + 1 << ": ";

        for (string word : testCases[i])
            cout << word << " ";

        cout << "\n";

        string ans = completeString(testCases[i]);

        cout << "Answer: " << ans << "\n\n";
    }

    return 0;
}