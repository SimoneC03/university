#include <iostream>
#include <string.h>

using namespace std;

void printElements(double *, int);
/* Print every element of a given array */
void printElements(double *arr, int length) {
    for(int i = 0; i < length; i++) {
        cout << "arr[" << i <<"] = " << arr[i] << endl;
    }
}

void readElements(double *&, int &);
/* Initialize array's values with numbers inserted from the user.
*  Enter '0' to stop the program */
void readElements(double *&arr, int &length) {
    string input;
    do {
        cout << "Please, enter a value to push inside the array: " << endl;
        cin >> input;
        try {
            double toInsert = stod(input);
            if(toInsert != 0) {
                double *newArr = new double[length + 1];
                for(int i = 0; i < length; i++)
                    newArr[i] = arr[i];
                delete [] arr;
                arr = newArr;
                for(int i = 0; i < length; i++) {
                    arr[i] = newArr[i];
                }
                arr[length] = toInsert;
                length = length + 1;
                printElements(arr, length);
            }
        } catch(...) {
            cout << "Value provided is not valid, only numeric values are supported: " << endl;
        }
    } while(input.compare("0") != 0);
}



int main() {
    int length = 0;
    double *arr = nullptr;
    readElements(arr, length);
    cout << "Inserted elements: " << endl;
    printElements(arr, length);
    delete [] arr;
    return 0;
}