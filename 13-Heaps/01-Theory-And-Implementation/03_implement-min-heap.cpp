// Problem:
// Implement a Min Heap with operations to insert, get, remove, and update elements.
// Support checking the heap size and whether it is empty, along with initializing the heap.
// All operations should maintain the min-heap property.

// ==================================================
// MIN HEAP IMPLEMENTATION
// Idea:
// - Store the heap in an array and use the parent/child index relationships to maintain the min-heap property.
// - Insertions and decreased keys are fixed using heapify up, while removals and increased keys are fixed using heapify down.
// - The minimum element is always present at the root (index 0).
//
// Time Complexity:
// insert     -> O(log N)
// getMin     -> O(1)
// extractMin -> O(log N)
// changeKey  -> O(log N)
// heapSize   -> O(1)
// isEmpty    -> O(1)
//
// Space Complexity: O(N)
// ==================================================

#include <bits/stdc++.h>
using namespace std;

class MinHeap
{
    vector<int> arr;
    int size;

    void heapify_down(int ind)
    {
        int lChild = (2 * ind) + 1, rChild = (2 * ind) + 2;
        int smallest = ind;

        if (lChild < size && arr[lChild] < arr[smallest])
            smallest = lChild;

        if (rChild < size && arr[rChild] < arr[smallest])
            smallest = rChild;

        // Move the current value down until the min-heap property is restored.
        if (smallest != ind)
        {
            swap(arr[ind], arr[smallest]);
            heapify_down(smallest);
        }
    }

    void heapify_up(int ind)
    {
        if (ind == 0)
            return;

        int parent = (ind - 1) / 2;

        // Move the current value up while it is smaller than its parent.
        if (arr[ind] < arr[parent])
        {
            swap(arr[ind], arr[parent]);
            heapify_up(parent);
        }
    }

public:
    void initializeHeap()
    {
        arr.clear();
        size = 0;
    }

    void insert(int key)
    {
        // Add the new value at the end, then move it up to its correct position.
        arr.emplace_back(key);
        size++;
        heapify_up(size - 1);
    }

    void changeKey(int index, int new_val)
    {
        // Increasing a value can violate the heap property with its children.
        if (arr[index] < new_val)
        {
            arr[index] = new_val;
            heapify_down(index);
        }
        // Decreasing a value can violate the heap property with its parent.
        else
        {
            arr[index] = new_val;
            heapify_up(index);
        }
    }

    void extractMin()
    {
        if (size == 0)
            return;

        // Replace the root with the last element, remove the last element, and restore the heap downward.
        swap(arr[0], arr[size - 1]);
        arr.pop_back();
        size--;
        heapify_down(0);
    }

    bool isEmpty()
    {
        return (size == 0);
    }

    int getMin()
    {
        if (size == 0)
            return -1;

        return arr[0];
    }

    int heapSize()
    {
        return size;
    }
};

int main()
{
    MinHeap newHeap;
    newHeap.initializeHeap();

    cout << "========== TEST 1: INSERTIONS ==========\n";

    vector<int> values = {
        50, 20, 40, 10, 30,
        5, 60, 1, 25, 15,
        35, 45, 2, 2, 100,
        -5, -10, 0, 20, 10};

    for (int x : values)
    {
        cout << "Inserting " << x << "\n";
        newHeap.insert(x);

        cout << "Current minimum: " << newHeap.getMin() << "\n";
        cout << "Current size: " << newHeap.heapSize() << "\n";
    }

    cout << "\n========== TEST 2: BASIC STATE ==========\n";

    cout << "Minimum: " << newHeap.getMin() << "\n";
    cout << "Size: " << newHeap.heapSize() << "\n";
    cout << "Is empty: " << newHeap.isEmpty() << "\n";

    cout << "\n========== TEST 3: CHANGE KEY DOWNWARD ==========\n";

    // Change an internal value to something much smaller.
    // This should force heapify-up.
    cout << "Changing index 10 to -100\n";
    newHeap.changeKey(10, -100);

    cout << "Minimum after changeKey: "
         << newHeap.getMin() << "\n";

    cout << "\n========== TEST 4: CHANGE KEY UPWARD ==========\n";

    // Change the root to a very large value.
    // This should force heapify-down.
    cout << "Changing root index 0 to 999\n";
    newHeap.changeKey(0, 999);

    cout << "Minimum after changing root: "
         << newHeap.getMin() << "\n";

    cout << "\n========== TEST 5: MORE CHANGE KEY TESTS ==========\n";

    cout << "Changing index 5 to -500\n";
    newHeap.changeKey(5, -500);

    cout << "Minimum: " << newHeap.getMin() << "\n";

    cout << "Changing index 8 to 700\n";
    newHeap.changeKey(8, 700);

    cout << "Minimum: " << newHeap.getMin() << "\n";

    cout << "Changing index 3 to -50\n";
    newHeap.changeKey(3, -50);

    cout << "Minimum: " << newHeap.getMin() << "\n";

    cout << "\n========== TEST 6: EXTRACT MIN REPEATEDLY ==========\n";

    int previous = INT_MIN;

    while (!newHeap.isEmpty())
    {
        int currentMin = newHeap.getMin();

        cout << "Minimum: " << currentMin
             << " | Size before extraction: "
             << newHeap.heapSize() << "\n";

        // Critical correctness check:
        // extracted values must be non-decreasing.
        if (currentMin < previous)
        {
            cout << "ERROR: Heap property violated!\n";
            return 1;
        }

        previous = currentMin;

        newHeap.extractMin();
    }

    cout << "\nHeap completely emptied.\n";
    cout << "Final size: " << newHeap.heapSize() << "\n";
    cout << "Is empty: " << newHeap.isEmpty() << "\n";

    cout << "\n========== TEST 7: SINGLE ELEMENT ==========\n";

    newHeap.insert(42);

    cout << "Minimum: " << newHeap.getMin() << "\n";
    cout << "Size: " << newHeap.heapSize() << "\n";

    newHeap.extractMin();

    cout << "Size after extraction: "
         << newHeap.heapSize() << "\n";

    cout << "Is empty: "
         << newHeap.isEmpty() << "\n";

    cout << "\n========== TEST 8: DUPLICATES ==========\n";

    newHeap.insert(5);
    newHeap.insert(5);
    newHeap.insert(5);
    newHeap.insert(5);
    newHeap.insert(5);

    cout << "Minimum: " << newHeap.getMin() << "\n";
    cout << "Size: " << newHeap.heapSize() << "\n";

    while (!newHeap.isEmpty())
    {
        cout << "Extracting: "
             << newHeap.getMin() << "\n";

        newHeap.extractMin();
    }

    cout << "\n========== ALL TESTS COMPLETED ==========\n";

    return 0;
}