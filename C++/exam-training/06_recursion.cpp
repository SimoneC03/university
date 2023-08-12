#include <iostream>

using namespace std;

void printArray(int *, int);
/* Print every element of a given array */
void printArray(int *arr, int length) {
    for(int i = 0; i < length; i++) {
        cout << "arr[" << i << "]" << " = " << arr[i] << endl;
    }
}

int findMax(int[], int);
/* Find recursively the max element inside a given array */
int findMax(int array[], int n) {
    if(n==1) return array[0];
    return max(array[n-1], findMax(array, n-1));
}

int findMin(int[], int);
/* Find recursively the min element inside a given array */
int findMin(int array[], int n) {
    if(n==1) return array[0];
    return min(array[n-1], findMin(array, n-1));
}

void swap(int *,int *);
/* Swap two array's elements */
void swap(int *a,int *b) {
    int temp = *a;
    *a=*b;
    *b = temp;
}
int partition (int[], int, int);
/*  Create a partition and return the pivot array element's index */
int partition (int A[], int p, int r) {
    int x = A[r];
    int i = p - 1;
    for (int j = p; j <= r- 1; j++) {
        if (A[j] <= x) {
            i++;
            swap (&A[i], &A[j]);
        }
    }
    swap (&A[i + 1], &A[r]);
    return (i + 1);
}
 
void quickSort(int[], int, int);
/* Sort a given array using recursively the Quick Sort sorting algorithm */
void quickSort(int A[], int p, int r) {
    if (p < r) {
        int q = partition(A, p,r);
        quickSort(A, p, q - 1);
        quickSort(A, q + 1, r);
    }
}

int main() {
    int array[] = {1,4,-2,-6,12,-34,234,213};
    int n = sizeof(array) / sizeof(int);
    cout << "The max element in the array is " << findMax(array, n) << endl;
    cout << "The min element in the array is " << findMin(array, n) << endl;
    cout << "Sorted array is:  " << endl;
    quickSort(array, 0, n-1);
    printArray(array, n);
    return 0;
}