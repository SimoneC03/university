#include <iostream>
#include <math.h>

using std::cout, std::cin, std::string;

bool isNumeric(string &s) {
    for(int i = 0; i < s.length(); i++) {
        if(isdigit(s[i]) == false && s[i] != '.') return false;
    }
    return true;
}

class Shape {
    public:
        virtual double getArea() const = 0;
};

class Rectangle : public Shape {
    private:
        double base, height;
        
    public:
        Rectangle() {}

        Rectangle(const double base, const double height) : base(base), height(height) {}

        double getArea() const override {
            return base * height;
        }
};

class Circumference : public Shape {
    private:
        double radius;
        
    public:
        Circumference() {}

        Circumference(const double radius) : radius(radius) {}

        double getArea() const override {
            return 2*radius*M_PI;
        }
};

class Triangle : public Shape {
    private:
        double base, height;

    public:
        Triangle() {}

        Triangle(const double base, const double height) : base(base), height(height) {}

        double getArea() const override {
            return (base*height)/2;
        }
};

template <typename T>
struct Node {
    T value;
    Node<T> *left;
    Node<T> *right;
    Node<T> *father;
};

template <typename T>
class BST {
    private:
        void insertAfter(Node<T> *n, Node<T> *newNode) {
            if(n == nullptr || newNode == nullptr) return;
            // compare area if `value` is a Shape's subclass
            Rectangle *rect = dynamic_cast<Rectangle *>(n->value);
            Circumference *circ = dynamic_cast<Circumference *>(n->value);
            Triangle *tri = dynamic_cast<Triangle *>(n->value);
            Rectangle *newRect = dynamic_cast<Rectangle *>(newNode->value);
            Circumference *newCirc = dynamic_cast<Circumference *>(newNode->value);
            Triangle *newTri = dynamic_cast<Triangle *>(newNode->value);
            if((rect != nullptr || circ != nullptr || tri != nullptr) && (newRect != nullptr || newCirc != nullptr || newTri != nullptr)) {
                double area = (rect != nullptr) ? rect->getArea() : (circ != nullptr) ? circ->getArea() : tri->getArea(); 
                double newArea = (newRect != nullptr) ? newRect->getArea() : (newCirc != nullptr) ? newCirc->getArea() : newTri->getArea();
                if(newArea < area) {
                    if(n->left == nullptr) {
                        newNode->father = n;
                        n->left = newNode;
                    } else insertAfter(n->left, newNode);
                } else {
                    if(n->right == nullptr) {
                        newNode->father = n;
                        n->right = newNode;
                    } else insertAfter(n->right, newNode);
                }
            } else {
                if(newNode->value < n->value) {
                    if(n->left == nullptr) {
                        newNode->father = n;
                        n->left = newNode;
                    } else insertAfter(n->left, newNode);
                } else {
                    if(n->right == nullptr) {
                        newNode->father = n;
                        n->right = newNode;
                    } else insertAfter(n->right, newNode);
                }
            }
        }

        /* Replace a subtree `n` with a subtree `newNode` */
        void transplant(Node<T> *n, Node<T> *newNode) {
            if(n == nullptr) return;
            if(n->father == nullptr) root = newNode;
            else if(n->father->left == n) n->father->left = newNode;
            else n->father->right = newNode;
            if(newNode != nullptr) newNode->father = n->father;
        }
    
    public:
        Node<T> *root;
    
        BST(): root(nullptr) {}

        Node<T> *createNode(T value) {
            Node<T> *newNode = new Node<T>;
            if(newNode == nullptr) exit(137);
            newNode->value = value;
            newNode->father = nullptr;
            newNode->left = nullptr;
            newNode->right = nullptr;
            return newNode;
        }

        void insert(T value) {
            Node<T> *newNode = createNode(value);
            if(root == nullptr) {
                root = newNode;
                return;
            }
            insertAfter(root, newNode);
        }

        Node<T> *min(Node<T> *n) {
            if(n == nullptr) return nullptr;
            Node<T> *current = n;
            while(current->left != nullptr) {
                current = current->left;
            }
            return current;
        }

        Node<T> *max(Node<T> *n) {
            if(n == nullptr) return nullptr;
            Node<T> *current = n;
            while(current->right != nullptr) {
                current = current->right;
            }
            return current;
        }

        void deleteNode(Node<T> *n) {
            if(n == nullptr) return;
            if(n->left == nullptr) transplant(n, n->right);
            else if(n->right == nullptr) transplant(n, n->left);
            else {
                Node<T> *mi = min(n->right);
                if(mi->father != n) {
                    transplant(mi, mi->right);
                    mi->right = n->right;
                    mi->right->father = mi;
                }
                transplant(n, mi);
                mi->left = n->left;
                mi->left->father = mi;
            }
        }

        void removeWithArea(const double area) {
            this->preorderArea(root, area);
        }

        /* Copy all elements inside a new `tree` of generic shapes */
        void fill(BST<Shape *> **tree) {
            this->preorderFill(root, tree);
        }

        /* Traverse the tree and insert each element inside a `tree` of generic shapes */
        void preorderFill(Node<T> *n, BST<Shape *> **tree) {
            if(n == nullptr) return;
            Rectangle *rect = dynamic_cast<Rectangle *>(n->value);
            Circumference *circ = dynamic_cast<Circumference *>(n->value);
            Triangle *tri = dynamic_cast<Triangle *>(n->value);
            if(rect != nullptr) {
                (*tree)->insert(rect);
            } else if(circ != nullptr) {
                (*tree)->insert(circ);
            } else if(tri != nullptr) {
                (*tree)->insert(tri);
            }
            preorderFill(n->left, tree);
            preorderFill(n->right, tree);

        }

        /* Traverse the tree, search for shapes with area lower than `area` and delete them */
        void preorderArea(Node<T> *n, const double area) {
            if(n == nullptr) return;
            Rectangle *rect = dynamic_cast<Rectangle *>(n->value);
            Circumference *circ = dynamic_cast<Circumference *>(n->value);
            Triangle *tri = dynamic_cast<Triangle *>(n->value);
            if(rect != nullptr) {
                if(rect->getArea() < area) deleteNode(n);
            } else if(circ != nullptr) {
                if(circ->getArea() < area) deleteNode(n);
            } else if(tri) {
                if(tri->getArea() < area) deleteNode(n);
            }
            preorderArea(n->left, area);
            preorderArea(n->right, area);
        }

        static void preorderPrint(Node<T> *n) {
            if(n == nullptr) return;
            Rectangle *rect = dynamic_cast<Rectangle *>(n->value);
            Circumference *circ = dynamic_cast<Circumference *>(n->value);
            Triangle *tri = dynamic_cast<Triangle *>(n->value);
            if(rect != nullptr) {
                cout << "Rectangle (area: " << rect->getArea() << ")\n";
            } else if(circ != nullptr) {
                cout << "Circumference (area: " << circ->getArea() << ")\n";
            } else if(tri) {
                cout << "Triangle (area: " << tri->getArea() << ")\n";
            } else cout << n->value << "\n";
            preorderPrint(n->left);
            preorderPrint(n->right);
        }        

        friend void operator<<(std::ostream &os, BST<T> &tree) {
            preorderPrint(tree.root);
        }

        friend void operator<<(std::ostream &os, BST<T> *tree) {
            preorderPrint(tree->root);
        }
};


int main() {
    BST<Rectangle *> rectangles;
    BST<Circumference *> circumferences;
    BST<Triangle *> triangles;
    cout << "Enter a number of shapes to create.\n";
    string input;
    cin >> input;
    if(isNumeric(input)) {
        for(int i = 0; i < abs(stoi(input)); i++) {
            // creating shapes
            cout << "Shape " << (i+1) << "\n"
                << "Select a type:\n1 - Rectangle\n2 - Circumference\n3 - Triangle\n";
            string type;
            cin >> type;
            if(isNumeric(type)) {
                if(stoi(type) == 1) {
                    string base, height;
                    cout << "Base: ";
                    cin >> base;
                    if(isNumeric(base)) {
                        cout << "Height: ";
                        cin >> height;
                        if(isNumeric(height)) {
                            Rectangle *r = new Rectangle(stod(base), stod(height));
                            rectangles.insert(r);
                        } else {
                            cout << "Invalid number.\n";
                        }
                    } else {
                        cout << "Invalid number.\n";
                    }
                } else if(stoi(type) == 2) {
                    string radius;
                    cout << "Radius: ";
                    cin >> radius;
                    if(isNumeric(radius)) {
                        Circumference *c = new Circumference(stod(radius));
                        circumferences.insert(c);
                    } else {
                        cout << "Invalid number.\n";
                    }
                } else if(stoi(type) == 3) {
                    string base, height;
                    cout << "Base: ";
                    cin >> base;
                    if(isNumeric(base)) {
                        cout << "Height: ";
                        cin >> height;
                        if(isNumeric(height)) {
                            Triangle *t= new Triangle(stod(base), stod(height));
                            triangles.insert(t);
                        } else {
                            cout << "Invalid number.\n";
                        }
                    } else {
                        cout << "Invalid number.\n";
                    }
                } else {
                    cout << "Invalid number.\n";
                }
            } else {
                cout << "Invalid number.\n";
            }
        }
    } else {
        cout << "Invalid number.\n";
    }
    cout << rectangles;
    cout << circumferences;
    cout << triangles;
    cout << "Delete all shapes with area lower than: ";
    cin >> input;
    if(isNumeric(input)) {
        rectangles.removeWithArea(stod(input));
        circumferences.removeWithArea(stod(input));
        triangles.removeWithArea(stod(input));
    } else {
        cout << "Invalid number.\n";
    }
    // insert remaining shapes inside a new BST
    BST<Shape *> *shapes = new BST<Shape *>;
    rectangles.fill(&shapes);
    circumferences.fill(&shapes);
    triangles.fill(&shapes);
    cout << "Remaining shapes:\n";
    cout << shapes;
    delete shapes;
    return 0;
}
