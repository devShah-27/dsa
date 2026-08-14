// Design and implement a data structure for a Least Frequently Used (LFU) cache.

// Implement the LFUCache class with the following functions:

// LFUCache(int capacity): Initialize the object with the specified capacity.
// int get(int key): Retrieve the value of the key if it exists in the cache; otherwise, return -1.
// void put(int key, int value): Update the value of the key if it is present in the cache, or insert the key if it is not already present. If the cache has reached its capacity, invalidate and remove the least frequently used key before inserting a new item. In case of a tie (i.e., two or more keys with the same frequency), invalidate the least recently used key.

// A use counter is maintained for each key in the cache to determine the least frequently used key. The key with the smallest use counter is considered the least frequently used.

// When a key is first inserted into the cache, its use counter is set to 1 due to the put operation. The use counter for a key in the cache is incremented whenever a get or put operation is called on it.

// Ensure that the functions get and put run in O(1) average time complexity.

#include <bits/stdc++.h>
using namespace std;

/*
    Node stores:
    key, value, frequency count
    and pointers for doubly linked list.
*/
struct Node
{
    int key;
    int value;
    int frequency;

    Node *next;
    Node *prev;

    Node(int key, int value)
    {
        this->key = key;
        this->value = value;
        frequency = 1;

        next = nullptr;
        prev = nullptr;
    }
};

/*
    Doubly linked list for nodes having same frequency.

    Front  -> Most recently used
    Back   -> Least recently used
*/
class List
{
public:
    int size;

    Node *head;
    Node *tail;

    List()
    {
        size = 0;

        // Dummy nodes to avoid edge cases
        head = new Node(-1, -1);
        tail = new Node(-1, -1);

        head->next = tail;
        tail->prev = head;
    }

    // Add node at front (most recently used)
    void addFront(Node *node)
    {
        Node *firstNode = head->next;

        node->next = firstNode;
        node->prev = head;

        head->next = node;
        firstNode->prev = node;

        size++;
    }

    // Remove any node from list
    void removeNode(Node *node)
    {
        Node *previousNode = node->prev;
        Node *nextNode = node->next;

        previousNode->next = nextNode;
        nextNode->prev = previousNode;

        size--;
    }
};

class LFUCache
{

private:
    // key -> node address
    unordered_map<int, Node *> keyNodeMap;

    // frequency -> list of nodes having that frequency
    unordered_map<int, List *> frequencyListMap;

    int capacity;
    int currentSize;

    // Smallest frequency currently present
    int minFrequency;

public:
    LFUCache(int capacity)
    {
        this->capacity = capacity;

        currentSize = 0;
        minFrequency = 0;
    }

    /*
        Increase node frequency:

        Remove from old frequency list
        Add to new frequency list
    */
    void updateFrequency(Node *node)
    {
        int oldFrequency = node->frequency;

        // Remove from old frequency group
        frequencyListMap[oldFrequency]->removeNode(node);

        // If minimum frequency list becomes empty
        if (oldFrequency == minFrequency &&
            frequencyListMap[oldFrequency]->size == 0)
        {
            minFrequency++;
        }

        node->frequency++;

        int newFrequency = node->frequency;

        // Create new frequency list if required
        if (frequencyListMap.find(newFrequency) ==
            frequencyListMap.end())
        {
            frequencyListMap[newFrequency] = new List();
        }

        // Add node to new frequency group
        frequencyListMap[newFrequency]->addFront(node);
    }

    int get(int key)
    {
        // Key does not exist
        if (keyNodeMap.find(key) == keyNodeMap.end())
        {
            return -1;
        }

        Node *node = keyNodeMap[key];

        int value = node->value;

        // Access increases frequency
        updateFrequency(node);

        return value;
    }

    void put(int key, int value)
    {
        if (capacity == 0)
            return;

        // Key already exists
        if (keyNodeMap.find(key) != keyNodeMap.end())
        {
            Node *node = keyNodeMap[key];

            node->value = value;

            updateFrequency(node);

            return;
        }

        // Remove LFU node if cache is full
        if (currentSize == capacity)
        {
            List *leastFrequencyList =
                frequencyListMap[minFrequency];

            // Back node = least recently used
            Node *nodeToRemove =
                leastFrequencyList->tail->prev;

            keyNodeMap.erase(nodeToRemove->key);

            leastFrequencyList->removeNode(nodeToRemove);

            currentSize--;
        }

        // Insert new node
        Node *newNode = new Node(key, value);

        minFrequency = 1;

        // Create frequency 1 list if missing
        if (frequencyListMap.find(1) ==
            frequencyListMap.end())
        {
            frequencyListMap[1] = new List();
        }

        frequencyListMap[1]->addFront(newNode);

        keyNodeMap[key] = newNode;

        currentSize++;
    }
};

int main()
{
    LFUCache cache(2);

    cache.put(1, 1);
    cache.put(2, 2);

    cout << cache.get(1) << " ";

    cache.put(3, 3);

    cout << cache.get(2) << " ";
    cout << cache.get(3) << " ";

    cache.put(4, 4);

    cout << cache.get(1) << " ";
    cout << cache.get(3) << " ";
    cout << cache.get(4) << " ";

    return 0;
}