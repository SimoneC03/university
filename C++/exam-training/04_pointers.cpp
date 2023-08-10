#include <iostream>

using namespace std;

void transformArray(int *, int);
/* Transform the elements of a given array, duplicating elements 
*  with even indexes and triplicating elements with odd indexes */
void transformArray(int *arr, int length) {
    for(int i = 0; i < length; i++) {
        if(i % 2 == 0) arr[i] *= 2;
        else arr[i] *= 3;
    }
}

void printArray(int *, int);
/* Print every element of a given array */
void printArray(int *arr, int length) {
    for(int i = 0; i < length; i++) {
        cout << "arr[" << i << "]" << " = " << arr[i] << endl;
    }
}

int main() {
    int size = 10;
    int array[size] = {0,1,2,3,4,5,6,7,8,9};
    cout << "Array before transformation: " << endl;
    printArray(array, size);
    transformArray(array, size);
    cout << "Array after transformation: " << endl;
    printArray(array, size);
    cout << "Array after a second transformation: " << endl;
    int *arrPointer = array;
    transformArray(arrPointer, size);
    printArray(arrPointer, size);
    return 0;
}