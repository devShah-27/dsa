// Problem:
// Design an LRU cache that supports get and put operations in O(1) average time.
// When capacity is exceeded, evict the least recently used key.

#include <bits/stdc++.h>
using namespace std;

// =============================================================
// OPTIMAL APPROACH
//
// Idea:
// Use a doubly linked list to maintain usage order and an unordered_map to locate nodes in O(1) average time. The most recently used node stays after head, while the least recently used node stays before tail.
//
// Time Complexity:
// O(1) average for both get() and put().
//
// Space Complexity:
// O(N), where N is the cache capacity, for the hash map and linked list.
//
// =============================================================

class Node
{
public:
    int key, val;
    Node *next;
    Node *prev;

    Node()
    {
        key = val = -1;
        next = prev = NULL;
    }

    Node(int k, int value)
    {
        key = k;
        val = value;
        next = prev = NULL;
    }
};

class LRUCache
{
    unordered_map<int, Node *> mpp;
    int capacity;
    Node *head, *tail;

    // Removes a node from its current position in the linked list.
    void deleteNode(Node *node)
    {
        Node *previousNode = node->prev;
        Node *nextNode = node->next;

        previousNode->next = nextNode;
        nextNode->prev = previousNode;
    }

    // Inserts a node immediately after the dummy head.
    // This position represents the most recently used entry.
    void insertNodeAfterHead(Node *node)
    {
        Node *nodeAfterHead = head->next;
        head->next = node;
        node->prev = head;

        node->next = nodeAfterHead;
        nodeAfterHead->prev = node;
    }

public:
    LRUCache(int capacity_)
    {
        mpp.clear();
        capacity = capacity_;

        // Dummy nodes simplify insertion and deletion at both ends.
        head = new Node(-1, -1);
        tail = new Node(-1, -1);

        head->next = tail;
        tail->prev = head;
    }

    int get(int key_)
    {
        if (mpp.find(key_) == mpp.end())
            return -1;

        Node *node = mpp[key_];

        int val = node->val;

        // Accessing a key makes it the most recently used entry.
        deleteNode(node);
        insertNodeAfterHead(node);

        return val;
    }

    void put(int key_, int value)
    {
        if (mpp.find(key_) != mpp.end())
        {
            // Update existing key and mark it as most recently used.
            Node *node = mpp[key_];
            node->val = value;

            deleteNode(node);
            insertNodeAfterHead(node);
        }
        else
        {
            if (mpp.size() == capacity)
            {
                // The node immediately before tail is the least recently used.
                Node *lastNode = tail->prev;

                mpp.erase(lastNode->key);
                deleteNode(lastNode);
            }

            Node *newNode = new Node(key_, value);

            mpp[key_] = newNode;
            insertNodeAfterHead(newNode);
        }
    }
};

int main()
{
    LRUCache cache(2);

    cache.put(1, 1);
    cache.put(2, 2);

    cout << cache.get(1) << " ";

    cache.put(3, 3);

    cout << cache.get(2) << " ";

    cache.put(4, 4);

    cout << cache.get(1) << " ";
    cout << cache.get(3) << " ";
    cout << cache.get(4) << " ";

    return 0;
}