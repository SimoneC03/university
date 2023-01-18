#include <stdio.h>

void insertionSort(int[], int);

void main() {
  int v[] = {1,5,2,9,2,15,7,12,13,4,144,56};
  int length = 12;
  insertionSort(v, length);
  for(int i = 0; i < length; i++) 
    printf("v[%d] = %d\n", i, v[i]);
}

void insertionSort(int arr[], int length) {
  for(int i = 1; i < length; i++) {
    int key = arr[i];
    int j = i - 1;
    while(j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j -= 1;
    }
    arr[j+1] = key;
  }
}