// ==================================================
// PROBLEM
// - Implement a Trie (prefix tree) class for lowercase English strings.
// - insert(word): store the word in the trie.
// - search(word): return true only if the exact word was inserted before.
// - startsWith(prefix): return true if any inserted word begins with prefix.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// TRIE (PREFIX TREE) APPROACH
//
// Idea:
// - Store each character of a word as an edge between nodes.
// - Words that share a prefix share the same path.
// - Each node holds 26 child links, one per letter 'a' to 'z'.
// - A null link means that letter does not continue the path.
// - Each node also holds an end flag. It marks that a  complete word finishes at that node.
// - search() walks the path and checks the end flag.
// - startsWith() only needs the whole path to exist.
//
// Time Complexity: O(L) per insert, search, and startsWith, where L is the string length.
// Space Complexity: O(26 * N * L) worst case for N inserted words, since each node holds 26 links.
// ==================================================

// Trie node: one character position along a word's path.
struct Node
{
private:
    // links[i] points to the child for the letter 'a' + i. Null means no such child.
    Node *links[26] = {nullptr};

    // True if a complete inserted word ends at this node.
    bool flag = false;

public:
    // Check whether a child node exists for the given character.
    bool contains(char ch)
    {
        return links[ch - 'a'] != nullptr;
    }

    // Attach a child node to the slot for the given character.
    void setReference(char ch, Node *newNode)
    {
        links[ch - 'a'] = newNode;
    }

    // Return the child node for the given character (may be null).
    Node *getNextReference(char ch)
    {
        return links[ch - 'a'];
    }

    // Mark that a complete word ends at this node.
    void markEnd()
    {
        flag = true;
    }

    // Check whether a complete word ends at this node.
    bool isEnd()
    {
        return flag;
    }
};

class Trie
{
    // Root is an empty sentinel node. It holds no character itself.
    Node *root;

public:
    // Create the empty root node.
    Trie()
    {
        root = new Node();
    }

    // NOTE: Assumes lowercase 'a'-'z' only. Other characters index out of bounds.
    void insert(const string &word)
    {
        Node *reference = root;

        for (int i = 0; i < word.length(); i++)
        {
            // Create the child node only when this letter is not on the path yet
            if (!reference->contains(word[i]))
                reference->setReference(word[i], new Node());

            // Move down to the child for this letter
            reference = reference->getNextReference(word[i]);
        }

        // The last node reached marks the end of a complete word
        reference->markEnd();
    }

    bool search(const string &word)
    {
        Node *reference = root;

        for (int i = 0; i < word.length(); i++)
        {
            // A missing link means the word was never inserted
            if (!reference->contains(word[i]))
                return false;

            reference = reference->getNextReference(word[i]);
        }

        // The path exists, but it must also end a complete word.
        // Example: "app" is a prefix of "apple" but not a word unless inserted.
        return reference->isEnd();
    }

    bool startsWith(const string &prefix)
    {
        Node *reference = root;

        for (int i = 0; i < prefix.size(); i++)
        {
            // A missing link means no inserted word has this prefix
            if (!reference->contains(prefix[i]))
                return false;

            reference = reference->getNextReference(prefix[i]);
        }

        // The whole prefix exists as a path, so the end flag does not matter
        return true;
    }
};

int main()
{
    Trie *trie = new Trie();

    vector<string> operations = {"Trie", "insert", "search", "search", "startsWith", "insert", "search"};
    vector<vector<string>> arguments = {{}, {"apple"}, {"apple"}, {"app"}, {"app"}, {"app"}, {"app"}};

    // Expected output: null, null, true, false, true, null, true
    vector<string> output;
    for (int i = 0; i < operations.size(); i++)
    {
        if (operations[i] == "Trie")
        {
            output.push_back("null");
        }
        else if (operations[i] == "insert")
        {
            trie->insert(arguments[i][0]);
            output.push_back("null");
        }
        else if (operations[i] == "search")
        {
            bool result = trie->search(arguments[i][0]);
            output.push_back(result ? "true" : "false");
        }
        else if (operations[i] == "startsWith")
        {
            bool result = trie->startsWith(arguments[i][0]);
            output.push_back(result ? "true" : "false");
        }
    }

    for (string res : output)
    {
        cout << res << endl;
    }

    delete trie;
    return 0;
}