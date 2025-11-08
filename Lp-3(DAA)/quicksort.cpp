#include<bits/stdc++.h>
using namespace std;

class QuickSort {

    // Single partition function (works when pivot is at arr[low])
    int partitionFunc(vector<int> &arr, int low, int high) {
        int pivot = arr[low];
        int left = low + 1;
        int right = high;

        while (true) {
            while (left <= right && arr[left] <= pivot) left++;
            while (left <= right && arr[right] >= pivot) right--;

            if (left > right) break;
            swap(arr[left], arr[right]);
        }
        swap(arr[low], arr[right]); // place pivot in correct position
        return right;
    }

public:

    // Deterministic Quick Sort (pivot = first element)
    void deterministicQuickSort(vector<int> &arr, int low, int high,
                                int &comparisons, int &swaps) {
        if(low < high) {
            int pivotIndex = partitionFunc(arr, low, high);

            comparisons += (high - low);
            swaps += 2;

            deterministicQuickSort(arr, low, pivotIndex - 1, comparisons, swaps);
            deterministicQuickSort(arr, pivotIndex + 1, high, comparisons, swaps);
        }
    }

    // Randomized Quick Sort (pivot chosen randomly)
    void randomQuickSort(vector<int> &arr, int low, int high,
                         int &comparisons, int &swaps) {
        if(low < high) {
            int randomIndex = low + rand() % (high - low + 1);
            swap(arr[low], arr[randomIndex]); // put random element at pivot position
            swaps++;

            int pivotIndex = partitionFunc(arr, low, high);

            comparisons += (high - low);
            swaps += 1;  // only one pivot swap counted (the above swap)

            randomQuickSort(arr, low, pivotIndex - 1, comparisons, swaps);
            randomQuickSort(arr, pivotIndex + 1, high, comparisons, swaps);
        }
    }
};


int main() {
    srand(time(0));
    QuickSort qs;

    vector<int> x = {15, 10, 12, 20, 1, 4, 17, 16, 11};
    int compDet = 0, swapsDet = 0;

    qs.deterministicQuickSort(x, 0, x.size()-1, compDet, swapsDet);

    cout << "Deterministic Sorted Array: ";
    for(int v : x) cout << v << " ";
    cout << "\nDeterministic Comparisons: " << compDet;
    cout << "\nDeterministic Swaps: " << swapsDet << endl;


    x = {15, 10, 12, 20, 1, 4, 17, 16, 11};
    int compRand = 0, swapsRand = 0;

    qs.randomQuickSort(x, 0, x.size()-1, compRand, swapsRand);

    cout << "\nRandomized Sorted Array: ";
    for(int v : x) cout << v << " ";
    cout << "\nRandomized Comparisons: " << compRand;
    cout << "\nRandomized Swaps: " << swapsRand << endl;

    return 0;
}


/*
==================== QUICK SORT COMPLEXITY ANALYSIS ====================

Quick Sort works by choosing a pivot, partitioning the array around it,
and then recursively sorting the left and right subarrays.

-----------------------------------------------------------------------
1) DETERMINISTIC QUICK SORT
   (Pivot is fixed — usually the first or last element)

   Best Case:
   - Pivot divides the array into two nearly equal halves.
   - Recursion depth = O(log n)
   - Work per level = O(n)
   - Time Complexity = O(n log n)

   Average Case:
   - Random distribution of elements
   - Expected balanced partitions
   - Time Complexity = O(n log n)

   Worst Case:
   - Pivot is always smallest or largest element
   - Happens for sorted / reverse sorted / nearly sorted arrays
   - Recursion depth becomes O(n)
   - Time Complexity = O(n^2)

   Space Complexity:
   - O(log n) in best/average case (for recursion stack)
   - O(n) in worst case (skewed recursion)

-----------------------------------------------------------------------
2) RANDOMIZED QUICK SORT
   (Pivot is chosen randomly)

   Best Case:
   - Same as deterministic, partitions are balanced
   - Time Complexity = O(n log n)

   Average Case:
   - Random pivot reduces chances of repeated worst-case splits
   - Time Complexity = O(n log n)   (more stable than deterministic)

   Worst Case:
   - Still O(n^2), but extremely rare because pivot is chosen randomly

   Space Complexity:
   - Same as deterministic:
     O(log n) average, O(n) worst

-----------------------------------------------------------------------
COMPARISON SUMMARY:

| Case          | Deterministic Quick Sort | Randomized Quick Sort |
|---------------|--------------------------|------------------------|
| Best Case     | O(n log n)               | O(n log n)             |
| Average Case  | O(n log n)               | O(n log n)  (more stable) |
| Worst Case    | O(n^2)                   | O(n^2) but very rare   |
| Space         | O(log n) avg, O(n) worst | O(log n) avg, O(n) worst |

-----------------------------------------------------------------------
Key Point:
Randomized Quick Sort prevents consistently bad pivots
and therefore avoids worst-case time on already sorted input.
*/
