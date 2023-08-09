#include <iostream>
#include <math.h>

using namespace std;

bool isPerfect(int);
/* Return true if a given number is perfect */
bool isPerfect(int n) {
    int i = 1;
    float max = n/2;
    int sum = 0;
    while(i <= max) {
        if(n % i == 0) sum += i;
        i++;
    }
    if(sum == n) return true;
    else return false;
}

int main() {
    cout<<"Is 8 a perfect number?"<<endl;
    if(isPerfect(8))
        cout<<"Yes"<<endl;
    else
        cout<<"No"<<endl;
    cout<<"Is 6 a perfect number?"<<endl;
    if(isPerfect(6))
        cout<<"Yes"<<endl;
    else
        cout<<"No"<<endl;
    return 0;
}