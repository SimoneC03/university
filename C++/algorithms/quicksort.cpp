#include <iostream>

using std::cout;

/* Print an array `arr` with a given `size` */
template <typename T>
void printArr(T &arr, const int size) {
    for(int i = 0; i < size; i++)
        cout << "arr[" << i << "] = " << arr[i] << "\n";
}

/* Swap two array's elements */
template <typename T>
void swap(T *a, T *b) {
    T temp = *a;
    *a = *b;
    *b = temp;
}

/*  Create a partition and return the pivot array element's index */
template <typename T>
int partition(T *arr, const int start, const int end) {
    int pivot = arr[end];
    int i = start - 1;
    for(int j = start; j < end; j++) {
        if(arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    i++;
    swap(&arr[i], &arr[end]);
    return i;
}

/* Sort generic type array in ascending order using the quicksort algorithm. */
template <typename T>
void quicksort(T *arr, const int start, const int end) {
    if(start < end) {
        int pivot = partition(arr, start, end);
        quicksort(arr, start, pivot - 1);
        quicksort(arr, pivot + 1, end);
    }
}

int main() {
    const int size = 5;
    int arr[size] = {1,2,8,4,6};
    cout << "Array:\n";
    printArr(arr, size);
    cout << "Sorted array:\n";
    quicksort(arr, 0, size-1);
    printArr(arr, size);
}