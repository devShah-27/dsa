// ==================================================
// PROBLEM
// - Implement a Trie that supports duplicate words, for lowercase English strings.
// - insert(word): add one occurrence of the word.
// - countWordsEqualTo(word): return how many times the word was inserted.
// - countWordsStartingWith(prefix): return how many inserted words begin with prefix.
// - erase(word): remove one occurrence of the word.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// TRIE WITH PREFIX AND END COUNTERS
//
// Idea:
// - Store each character of a word as an edge between nodes.
// - Words that share a prefix share the same path.
// - Each node keeps prefixCount, the number of inserted words passing through that node.
// - Each node also keeps endCount, the number of inserted words that finish exactly at that node.
// - insert() increments prefixCount along the path and endCount at the last node. 
// - erase() reverses exactly those updates.
// - Counting queries walk the path and read one counter.
// - endCount gives exact matches, prefixCount gives prefix matches.
//
// Time Complexity: O(L) per operation, where L is the string length.
// Space Complexity: O(26 * N * L) worst case for N inserted words, since each node holds 26 links.
// ==================================================

// Trie node: one character position along a word's path.
struct Node
{
private:
    // links[i] points to the child for the letter 'a' + i. Null means no such child.
    Node *links[26] = {nullptr};

public:
    // endCount: number of words ending at this node.
    // prefixCount: number of words passing through this node (including those ending here).
    int endCount = 0, prefixCount = 0;

    // Check whether a child node exists for the given character.
    bool containsKey(char ch)
    {
        return links[ch - 'a'] != nullptr;
    }

    // Attach a child node to the slot for the given character.
    void insertKey(char ch, Node *node)
    {
        links[ch - 'a'] = node;
    }

    // Return the child node for the given character (may be null).
    Node *getNextReference(char ch)
    {
        return links[ch - 'a'];
    }

    // One more inserted word passes through this node.
    void increasePrefixCount()
    {
        prefixCount++;
    }

    // One more inserted word ends at this node.
    void increaseEndCount()
    {
        endCount++;
    }

    // One fewer word passes through this node (used by erase).
    void decreasePrefixCount()
    {
        prefixCount--;
    }

    // One fewer word ends at this node (used by erase).
    void decreaseEndCount()
    {
        endCount--;
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

    // NOTE: Assumes lowercase 'a'-'z' only. Other characters index out of bounds.
    void insert(const string &word)
    {
        Node *referenceNode = root;

        for (int i = 0; i < word.size(); i++)
        {
            // Create the child node only when this letter is not on the path yet
            if (!referenceNode->containsKey(word[i]))
                referenceNode->insertKey(word[i], new Node());

            // Move down, then count this word as passing through the child
            referenceNode = referenceNode->getNextReference(word[i]);
            referenceNode->increasePrefixCount();
        }

        // The last node reached marks one more complete occurrence of the word
        referenceNode->increaseEndCount();
    }

    int countWordsEqualTo(const string &word)
    {
        Node *referenceNode = root;

        for (int i = 0; i < word.size(); i++)
        {
            // A missing link means the word was never inserted
            if (!referenceNode->containsKey(word[i]))
                return 0;

            referenceNode = referenceNode->getNextReference(word[i]);
        }

        // Number of words that end exactly at this node
        return referenceNode->endCount;
    }

    int countWordsStartingWith(const string &prefix)
    {
        Node *referenceNode = root;

        for (int i = 0; i < prefix.size(); i++)
        {
            // A missing link means no inserted word has this prefix
            if (!referenceNode->containsKey(prefix[i]))
                return 0;

            referenceNode = referenceNode->getNextReference(prefix[i]);
        }

        // Number of words that pass through the node reached by the prefix
        return referenceNode->prefixCount;
    }

    void erase(const string &word)
    {
        // Guard: erasing a word that does not exist must not corrupt the counters
        if (countWordsEqualTo(word) == 0)
            return;

        Node *referenceNode = root;

        for (int i = 0; i < word.size(); i++)
        {
            // NOTE: Unreachable after the guard above, kept as a defensive check.
            if (!referenceNode->containsKey(word[i]))
                return;

            // Undo the prefix count added by insert along the path
            referenceNode = referenceNode->getNextReference(word[i]);
            referenceNode->decreasePrefixCount();
        }

        // Remove one occurrence of the word at its last node
        referenceNode->decreaseEndCount();
    }
};

int main()
{
    Trie trie;
    trie.insert("apple");
    trie.insert("apple");
    cout << "Inserting strings 'apple' twice into Trie" << endl;

    // Expected: 2
    cout << "Count Words Equal to 'apple': ";
    cout << trie.countWordsEqualTo("apple") << endl;

    // Expected: 2
    cout << "Count Words Starting With 'app': ";
    cout << trie.countWordsStartingWith("app") << endl;

    cout << "Erasing word 'apple' from trie" << endl;
    trie.erase("apple");

    // Expected: 1
    cout << "Count Words Equal to 'apple': ";
    cout << trie.countWordsEqualTo("apple") << endl;

    // Expected: 1
    cout << "Count Words Starting With 'app': ";
    cout << trie.countWordsStartingWith("app") << endl;

    cout << "Erasing word 'apple' from trie" << endl;
    trie.erase("apple");

    // Expected: 0
    cout << "Count Words Starting With 'app': ";
    cout << trie.countWordsStartingWith("app") << endl;
    return 0;
}