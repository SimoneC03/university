#include <math.h>
#include <iostream>

class Dot2D {
    
    public:

        double x;
        double y;
        
        Dot2D() {
            x = 10;
            y = 10;
        }

        Dot2D(double x, double y) {
            this->x = x;
            this->y = y;
        }

};

class Rectangle {
    
    private:
        double base;
        double height;
        Dot2D top_left;
        Dot2D bottom_right;

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

        Rectangle(Dot2D top_left, Dot2D bottom_right) {
            this->top_left = top_left;
            this->bottom_right = bottom_right;
            base = bottom_right.x - top_left.x;
            height = top_left.y - bottom_right.y;
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

        /* Return true if a given dot is located inside the area of the rectangle */
        bool contains(Dot2D d) {
            return d.x >= top_left.x && d.x <= bottom_right.x && d.y <= top_left.y && d.y >= bottom_right.y;
        }

        /* Return true if a given rectangle is located inside the area of the rectangle */
        bool contains(Rectangle *r) {
            if(r == NULL) return 0;
            return r->top_left.x >= top_left.x && r->bottom_right.x <= bottom_right.x && r->top_left.y <= top_left.y && r->bottom_right.y >= bottom_right.y;
        }

        /* Return true if a given rectangle is located inside the area of the rectangle */
        bool contains(Rectangle r) {
            return r.top_left.x >= top_left.x && r.bottom_right.x <= bottom_right.x && r.top_left.y <= top_left.y && r.bottom_right.y >= bottom_right.y;
        }
};

using namespace std;

int main() {
    Dot2D dot = {10,20};
    Rectangle B({10,20},{50,10});
    cout << "Is the dot (" << dot.x << ", " << dot.y << ") contained in the rectangle B? " << (B.contains(dot) ? "Yes" : "No") << endl;
    return 0;
}