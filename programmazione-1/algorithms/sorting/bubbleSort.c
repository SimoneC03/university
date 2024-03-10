#include <stdio.h>

void bubbleSort(int[], int);

void main()
{
  int v[] = {1, 5, 2, 9, 2, 15, 7, 12, 13, 4, 144, 56};
  int length = 12;
  bubbleSort(v, length);
  for (int i = 0; i < length; i++)
    printf("v[%d] = %d\n", i, v[i]);
}

void bubbleSort(int arr[], int length)
{
  for (int i = 0; i < length; i++)
    for (int j = 0; j < length - 1 - i; j++)
      if (arr[j] > arr[j + 1])
      {
        int temp = arr[j + 1];
        arr[j + 1] = arr[j];
        arr[j] = temp;
      }
}