#include <math.h>
#include <iostream>

class Rectangle {
    
    private:
        double base;
        double height;

    public:
        double getBase() {
            return base;
        }

        double getHeight() {
            return height;
        }

        void setBase(double b) {
            base = b;
        }

        void setHeight(double h) {
            height = h;
        }

        Rectangle() {
            base = 10;
            height = 10;
        }

        Rectangle(double b, double h) {
            base = b;
            height = h;
        }

        double getArea() {
            return base*height;
        }

        double getPerimeter() {
            return (base+height)*2;
        }

        double getDiagonal() {
            return sqrt((base*base)+(height*height));
        }

        bool isSquare() {
            return base == height;
        }
};

using namespace std;

int main() {
    Rectangle *r1 = new Rectangle();
    Rectangle *r2 = new Rectangle(2,4);
    cout << "r1 area is: " << r1->getArea() << endl;
    cout << "r1 diagonal is: " << r1->getDiagonal() << endl;
    cout << "Is r1 a square? " << ((r1->isSquare() == 1) ? "Yes" : "No") << endl;
    cout << "r2 area is: " << r2->getArea() << endl;
    cout << "r2 diagonal is: " << r2->getDiagonal() << endl;
    cout << "Is r2 a square? " << ((r2->isSquare() == 1) ? "Yes" : "No") << endl;
    return 0;
}