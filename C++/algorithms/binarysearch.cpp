#include <iostream>

using std::cout;

/* Print an array `arr` with a given `size` */
template <typename T>
void printArr(T &arr, const int size) {
    for(int i = 0; i < size; i++)
        cout << "arr[" << i << "] = " << arr[i] << "\n";
}

/* Search `target` inside `arr` using the Binary Search algorithm */
template <typename T>
int binarySearch(T *arr, const int size, T target) {
    int low = 0;
    int high = size-1;
    while(low <= high) {
        int middle = low + (high-low) / 2;
        if(target < arr[middle]) low = middle - 1;
        else if(target > arr[middle]) low = middle + 1;
        else return middle;
    }
    return -1;
}

int main() {
    const int size = 5;
    int arr[size] = {1,2,8,4,6};
    cout << "Array:\n";
    printArr(arr, size);
    int found = binarySearch(arr, size, 8);
    if(found != -1)
        cout << "8 found at index: " << found << "\n";
    else
        cout << "8 not found";
}