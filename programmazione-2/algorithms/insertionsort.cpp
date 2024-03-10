#include <iostream>

using std::cout;

/* Print an array `arr` with a given `size` */
template <typename T>
void printArr(T &arr, const int size) {
    for(int i = 0; i < size; i++)
        cout << "arr[" << i << "] = " << arr[i] << "\n";
}

/* Sort generic type array in ascending order using the Insertionsort algorithm.  */
template <typename T>
void insertionsort(T *arr, const int size) {
    for(int i=1; i<size; i++) {
        T temp = arr[i];
        int j = i-1;
        while(j >= 0 && arr[j] > temp) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = temp;
    }
}

int main() {
    const int size = 6;
    int arr[size] = {1,2,8,4,6,3};
    cout << "Array:\n";
    printArr(arr, size);
    cout << "Sorted array:\n";
    insertionsort(arr, size);
    printArr(arr, size);
}