#include <iostream>

using std::cout;

/* Sort a given `arr`, containing only integer values between 0 and k, inside the `sorted` array
 * using the Counting Sort algorithm with a time complexity of O(n) */
void countingSort(int *arr, int **sorted, const int k, const int size) {
    int *counter = new int[k+1];
    if(counter == nullptr) exit(137);
    for(int i = 0; i < size; i++) {
        counter[arr[i]]++; // count elements occurrences
    }
    for(int i = 1; i < k+1; i++) {
        counter[i] += counter[i-1]; // cumulative counts
    }
    for(int i = size-1; i >= 0; i--) {
        (*sorted)[counter[arr[i]]-1] = arr[i];
        counter[arr[i]]--;
    }
    delete[] counter;
}

int main() {
    const int size = 15;
    int arr[size] = {1,2,8,4,6,2,43,13,34,24,11,23,24,23,0};
    int *sorted = new int[size];
    if(sorted == nullptr) exit(137);
    cout << "Array: [";
    for(const int el : arr) {
        cout << el << ", ";
    }
    int maxValue = 43;
    countingSort(arr, &sorted, maxValue, size);
    cout << "]\nSorted array: [";
    for(int i = 0; i < size; i++) {
        cout << sorted[i] << ", ";
    }
    cout << "]\n";
    delete[] sorted;
}