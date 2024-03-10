#include <iostream>

using std::cout, std::string, std::cin;

bool isNumeric(string);
/* Return whether a string is numeric or not */
bool isNumeric(string str) {
    for (int i = 0; i < str.length(); i++)
        if (isdigit(str[i]) == false)
            return false;
    return true;
}

class Dot {
    public:
        int x;
        int y;

        Dot(const int x, const int y) : x(x), y(y) {}
        
};

/* Return the index of found element otherwise return -1 */
template <typename T>
int search(const T &el, T arr[], int n) {
    for(int i = 0; i < n; i++) {
        if(arr[i] == el) {
            return i;
        }
    }
    return -1;
}

/* Return the index of found Dot element otherwise return -1 */
template <>
int search(const Dot &el, Dot arr[], int n) {
    for(int i = 0; i < n; i++) {
        if(arr[i].x == el.x && arr[i].y == el.y) {
            return i;
        }
    }
    return -1;
}

/* Print a given array of n elements */
template <typename T>
void printArray(const T arr[], int n) {
    for(int i = 0; i < n; i++)
        cout << "arr[" << i <<"] = " << arr[i] << "\n";
    cout << "\n";
}

/* Print a given array of n Dot elements */
template <>
void printArray(const Dot arr[], int n) {
    for(int i = 0; i < n; i++)
        cout << "arr[" << i <<"] = (" << arr[i].x << "," << arr[i].y << ")\n";
    cout << "\n";
}

int main() {
    int arrInt[3] = {1,2,3};
    char arrChar[3] = {'a', 'b', 'c'};
    Dot arrDot[3] = {
        Dot(1,2),
        Dot(2,8),
        Dot(1,7)
    };
    string input;
    askforint:
    cout << "\nPlease, insert an integer to find: ";
    cin >> input;
    if(isNumeric(input)) {
        int foundIndex = search(stoi(input), arrInt, 3);
        if(foundIndex != -1) cout << "Integer " << input << " has been found at index: " << foundIndex << "\n";
        else cout << "Integer " << input << " was not found\n";
    } else {
        cout << "Invalid integer value.\n";
        goto askforint;
    }
    askforchar:
    cout << "\nPlease, insert a char to find: ";
    cin >> input;
    if(input.length() == 1) {
        int foundIndex = search(input[0], arrChar, 3);
        if(foundIndex != -1) cout << "Char " << input << " has been found at index: " << foundIndex << "\n";
        else cout << "Char " << input << " was not found\n";
    } else {
        cout << "Invalid char length.\n";
        goto askforchar;
    }
    askfordot:
    cout << "\nPlease, insert a dot to find (ex. 0,0): ";
    cin >> input;
    string delimiter = ",";
    if(input.find(delimiter) > 0) {
        string x = input.substr(0, input.find(delimiter));
        string y = input.substr(input.find(delimiter)+1, input.length());
        if(isNumeric(x) && isNumeric(y)) {
            Dot toFind(stoi(x),stoi(y));
            int foundIndex = search(toFind, arrDot, 3);
            if(foundIndex != -1) cout << "Dot (" << x << "," << y << ") has been found at index: " << foundIndex << "\n";
            else cout << "Dot (" << x << "," << y << ") was not found\n";
        } else {
            cout << "Invalid dot syntax\n";
            goto askfordot;
        }        
    } else {
        cout << "Invalid dot syntax\n";
        goto askfordot;
    }

    cout << "Printing arrays:\n";
    printArray(arrInt, 3);
    printArray(arrChar, 3);
    printArray(arrDot, 3);
    return 0;
}