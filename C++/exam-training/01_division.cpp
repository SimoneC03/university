#include <iostream>

using namespace std;

int divide(int, int);
/* Integer division between x and y */
int divide(int x, int y) {
    int i = 0;
    while(x >= y) {
        x -= y;
        i++;
    }
    return i;
}

int main() {
    cout<<"8/4 = "<<divide(8,4)<<endl;
    return 0;
}