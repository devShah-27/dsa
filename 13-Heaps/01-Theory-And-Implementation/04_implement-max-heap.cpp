// Problem:
// Implement a Max Heap with operations to insert, get, remove, and update elements.
// Support checking the heap size and whether it is empty, along with initializing the heap.
// When extracting max, if both children are equal, the left child should be chosen.

// ==================================================
// MAX HEAP IMPLEMENTATION
// Idea:
// - Store the heap in an array and maintain the max-heap property using parent-child index relationships.
// - Insertions and increased keys are fixed using heapify up, while removals and decreased keys are fixed using heapify down.
// - The maximum element is always present at the root (index 0).
//
// Time Complexity:
// insert     -> O(log N)
// getMax     -> O(1)
// extractMax -> O(log N)
// changeKey  -> O(log N)
// heapSize   -> O(1)
// isEmpty    -> O(1)
//
// Space Complexity: O(N)
// ==================================================

#include <bits/stdc++.h>
using namespace std;

class MaxHeap
{
    vector<int> list;
    int size;

    void heapify_down(int ind)
    {
        int lChild = (2 * ind) + 1, rChild = (2 * ind) + 2;
        int largest = ind;

        if (lChild < size && list[lChild] > list[largest])
            largest = lChild;

        if (rChild < size && list[rChild] > list[largest])
            largest = rChild;

        // If a child is greater than the current node, swap and continue downward.
        // When both children are equal, the left child is selected because 
        // the right child is updated only when it is strictly greater.
        if (largest != ind)
        {
            swap(list[largest], list[ind]);
            heapify_down(largest);
        }
    }

    void heapify_up(int ind)
    {
        if (ind == 0)
            return;

        int parent = (ind - 1) / 2;

        // Move the current value upward until the max-heap property is restored.
        if (list[ind] > list[parent])
        {
            swap(list[ind], list[parent]);
            heapify_up(parent);
        }
    }

public:
    void initializeHeap()
    {
        list.clear();
        size = 0;
    }

    void insert(int key)
    {
        // Insert at the end and move the element upward to its correct position.
        list.emplace_back(key);
        size++;
        heapify_up(size - 1);
    }

    void changeKey(int index, int new_val)
    {
        // Increasing a value may violate the heap property with the parent.
        if (list[index] < new_val)
        {
            list[index] = new_val;
            heapify_up(index);
        }
        // Decreasing a value may violate the heap property with the children.
        else
        {
            list[index] = new_val;
            heapify_down(index);
        }
    }

    void extractMax()
    {
        if (size == 0)
            return;

        // Replace root with the last element, remove the last element, 
        // then restore the heap property by moving the new root downward.
        swap(list[0], list[size - 1]);
        list.pop_back();

        size--;

        heapify_down(0);
    }

    bool isEmpty()
    {
        return (size == 0);
    }

    int getMax()
    {
        if (size == 0)
            return -1;

        return list[0];
    }

    int heapSize()
    {
        return size;
    }
};

int main()
{
    MaxHeap heap;
    heap.initializeHeap();

    cout << "========== TEST 1: INSERTIONS ==========\n";

    vector<int> values = {
        50, 20, 40, 10, 30,
        5, 60, 1, 25, 15,
        35, 45, 2, 2, 100,
        -5, -10, 0, 20, 10};

    for (int x : values)
    {
        cout << "Inserting " << x << "\n";
        heap.insert(x);

        cout << "Current maximum: " << heap.getMax() << "\n";
        cout << "Current size: " << heap.heapSize() << "\n";
    }

    cout << "\n========== TEST 2: BASIC STATE ==========\n";

    cout << "Maximum: " << heap.getMax() << "\n";
    cout << "Size: " << heap.heapSize() << "\n";
    cout << "Is empty: " << heap.isEmpty() << "\n";

    cout << "\n========== TEST 3: CHANGE KEY UPWARD ==========\n";

    // Increase value -> should heapify UP
    cout << "Changing index 10 to 1000\n";
    heap.changeKey(10, 1000);

    cout << "Maximum after changeKey: "
         << heap.getMax() << "\n";

    cout << "\n========== TEST 4: CHANGE KEY DOWNWARD ==========\n";

    // Decrease root -> should heapify DOWN
    cout << "Changing root index 0 to -999\n";
    heap.changeKey(0, -999);

    cout << "Maximum after changing root: "
         << heap.getMax() << "\n";

    cout << "\n========== TEST 5: MORE CHANGE KEY TESTS ==========\n";

    cout << "Changing index 5 to 5000\n";
    heap.changeKey(5, 5000);

    cout << "Maximum: " << heap.getMax() << "\n";

    cout << "Changing index 8 to -500\n";
    heap.changeKey(8, -500);

    cout << "Maximum: " << heap.getMax() << "\n";

    cout << "Changing index 3 to 2000\n";
    heap.changeKey(3, 2000);

    cout << "Maximum: " << heap.getMax() << "\n";

    cout << "\n========== TEST 6: EXTRACT MAX REPEATEDLY ==========\n";

    int previous = INT_MAX;

    while (!heap.isEmpty())
    {
        int currentMax = heap.getMax();

        cout << "Maximum: " << currentMax
             << " | Size before extraction: "
             << heap.heapSize() << "\n";

        // Extracted values must be non-increasing
        if (currentMax > previous)
        {
            cout << "ERROR: Max Heap property violated!\n";
            return 1;
        }

        previous = currentMax;

        heap.extractMax();
    }

    cout << "\nHeap completely emptied.\n";
    cout << "Final size: " << heap.heapSize() << "\n";
    cout << "Is empty: " << heap.isEmpty() << "\n";

    cout << "\n========== TEST 7: SINGLE ELEMENT ==========\n";

    heap.insert(42);

    cout << "Maximum: " << heap.getMax() << "\n";
    cout << "Size: " << heap.heapSize() << "\n";

    heap.extractMax();

    cout << "Size after extraction: "
         << heap.heapSize() << "\n";

    cout << "Is empty: "
         << heap.isEmpty() << "\n";

    cout << "\n========== TEST 8: DUPLICATES ==========\n";

    heap.insert(5);
    heap.insert(5);
    heap.insert(5);
    heap.insert(5);
    heap.insert(5);

    cout << "Maximum: " << heap.getMax() << "\n";
    cout << "Size: " << heap.heapSize() << "\n";

    while (!heap.isEmpty())
    {
        cout << "Extracting: "
             << heap.getMax() << "\n";

        heap.extractMax();
    }

    cout << "\n========== ALL TESTS COMPLETED ==========\n";

    return 0;
}