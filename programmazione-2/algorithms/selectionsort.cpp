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

/* Sort generic type array in ascending order using the Selectionsort algorithm.  */
template <typename T>
void selectionSort(T *arr, const int size) {
    for(int i = 0; i < size; i++) {
        T min = i;
        for(int j=i+1; j < size; j++) {
            if(arr[min] > arr[j]) min = j;
        }
        swap(&arr[i], &arr[min]);
    }
}

int main() {
    const int size = 6;
    int arr[size] = {1,2,8,4,6,3};
    cout << "Array:\n";
    printArr(arr, size);
    cout << "Sorted array:\n";
    selectionSort(arr, size);
    printArr(arr, size);
}