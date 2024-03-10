#include <iostream>

using std::cout;

/* Print an array `arr` with a given `size` */
template <typename T>
void printArr(T &arr, const int size) {
    for(int i = 0; i < size; i++)
        cout << "arr[" << i << "] = " << arr[i] << "\n";
}

/* Merge the splitted array `arr` by picking neatly elements from the leftArray and the rightArray */
template <typename T>
void merge(T *leftArr, T *rightArr, T *arr, const int size) {
    const int leftSize = size / 2;
    const int rightSize = size - leftSize;
    int i = 0, l = 0, r = 0;
    while(l < leftSize && r < rightSize) {
        if(leftArr[l] < rightArr[r]) {
            arr[i] = leftArr[l];
            i++;
            l++;
        } else {
            arr[i] = rightArr[r];
            i++;
            r++;
        }
    }
    while(l < leftSize) {
        arr[i] = leftArr[l];
        i++;
        l++;
    }
    while(r < rightSize) {
        arr[i] = rightArr[r];
        i++;
        r++;
    }
}

/* Sort generic type array in ascending order using the Mergesort algorithm.
*  Split recursively the array `arr` in more subarrays and then neatly merge
*  all the elements. */
template <typename T>
void mergeSort(T *arr, const int size) {
    if(size <= 1) return;
    const int middle = size / 2;
    int i = 0; // left array index
    int j = 0; // right array index
    T *leftArr = new T[middle];
    T *rightArr = new T[size - middle];
    for(; i < size; i++) {
        if(i < middle) {
            leftArr[i] = arr[i];
        } else {
            rightArr[j] = arr[i];
            j++;
        }
    }
    mergeSort(leftArr, middle);
    mergeSort(rightArr, size - middle);
    merge(leftArr, rightArr, arr, size);
}

int main() {
    const int size = 5;
    int arr[size] = {1,2,8,4,6};
    cout << "Array:\n";
    printArr(arr, size);
    cout << "Sorted array:\n";
    mergeSort(arr, size);
    printArr(arr, size);
}