#include <iostream>

using std::cout;

/* Sort a given array `arr` with a given `size`, containing only integer values 
 * between 0 and `k`, returning a pointer to a sorted array using the 
 * Counting Sort algorithm with a time complexity of O(n+k) */
int *countingSort(int *arr, const int size, const int k) {
    // counter array to keep track of `arr` elements occurrences
    int *counter = new int[k+1];
    // initialize counter cells to 0
    for(int i = 0; i < k+1; i++) counter[i] = 0;
    // store all the `arr` elements occurrences
    for(int i = 0; i < size; i++) counter[arr[i]]++;
    // calculate cumulative sums
    for(int i = 1; i < k+1; i++) counter[i] += counter[i - 1];
    // build final array
    int *res = new int[size];
    for(int i = size-1; i >= 0; i--) {
        res[counter[arr[i]] - 1] = arr[i]; // - 1 to skip offset of array indeces starting from 0
        counter[arr[i]]--;
    }
    delete[] counter;
    return res;
}

int main() {
    const int size = 6;
    int arr[size] = {1,2,8,4,6,2};
    const int maxValue = 8;
    cout << "Array: [";
    for(const int el : arr) {
        cout << el << ", ";
    }
    int *sorted = countingSort(arr, size, maxValue);
    cout << "]\nSorted array: [";
    for(int i = 0; i < size; i++) {
        cout << sorted[i] << ", ";
    }
    cout << "]\n";
    delete[] sorted;
}