#include <iostream>

using std::cout;
class Rectangle {
    private:
        double base;
        double height;
    public:

        Rectangle(const double base, const double height) : base(base), height(height) {}

        double getArea() const {
            return base * height;
        }
};

template <typename T>
bool compare(const T &a, const T &b) {
    return a > b;
}

template <>
bool compare(const Rectangle &a, const Rectangle &b) {
    return a.getArea() > b.getArea();
}

template <typename T>
void swap(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}

/* Sort a given array with n elements */
template <typename T>
void sortArray(T array[], int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n-1-i; j++ ) {
            if(compare(array[j], array[j+1])) {
                swap(array[j], array[j+1]);
            }
        }
    }
}

/* Print a given array with n elements */
template <typename T>
void printArray(const T arr[], int n) {
    for(int i = 0; i < n; i++) {
        cout << "arr[" << i <<"] = " << arr[i] << "\n";
    }
    cout << "\n";
}

/* Print a given array with n elements of type Rectangle */
template <>
void printArray(const Rectangle arr[], int n) {
    for(int i = 0; i < n; i++) {
        cout << "arr[" << i <<"] = " << arr[i].getArea() << "  (rectangle's area)\n";
    }
    cout << "\n";
}

int main() {
    int arrInt[3] = {2,8,1};
    char arrChar[3] = {'b', 'e', 'a'};
    Rectangle arrRect[] = {
        Rectangle(2.0, 15.0),
        Rectangle(3.0, 4.0),
        Rectangle(4.0, 6.0),
    };
    cout << "Printing arrays before sorting\n";
    printArray(arrInt, 3);
    printArray(arrChar, 3);
    printArray(arrRect, 3);
    sortArray(arrInt, 3);
    sortArray(arrChar, 3);
    sortArray(arrRect, 3);
    cout << "Printing arrays after sorting\n";
    printArray(arrInt, 3);
    printArray(arrChar, 3);
    printArray(arrRect, 3);

    return 0;
}