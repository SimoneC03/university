#include <iostream>

using std::cout;

template <typename T>
void printArr(T &arr, const int size) {
    for(int i = 0; i < size; i++)
        cout << "arr[" << i << "] = " << arr[i] << "\n";
}

template <typename T>
/* Sort generic type array in ascending order using the Bubblesort algorithm */
void bubbleSort(T *arr, const int size) {
    T temp;
    for(int i = 0; i < size; i++) 
        for(int j = 0; j < size-i-1; j++)
            if(arr[j] > arr[j+1]) {
                temp = arr[j+1];
                arr[j+1] = arr[j];
                arr[j] = temp;
            }
}

int main() {
    const int size = 5;
    int arr[size] = {1,2,8,4,6};
    cout << "Array:\n";
    printArr(arr, size);
    cout << "Sorted array:\n";
    bubbleSort(arr, size);
    printArr(arr, size);
}