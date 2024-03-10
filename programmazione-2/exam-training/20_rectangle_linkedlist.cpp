#include <iostream>

using std::string, std::cout, std::cin;

template<typename T>
struct Node {
    T value;
    Node<T> *next;
};

template<typename T>
class LinkedList {
    public:
        Node<T> *head;

        LinkedList() : head(nullptr) {}

        
        void push(T r) {
            Node<T> *newNode = new Node<T>;
            if(newNode == nullptr) {
                cout << "Memory is full.\n";
                exit(137);
            }
            newNode->value = r;
            if(head == nullptr) {
                head = newNode;
                return;
            }
            Node<T> *current = head;
            while(current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }

        void remove(Node<T> *n) {
            if(head == nullptr) {return;}
            if(head == n) {
                Node<T> *toRemove = head;
                head = head->next;
                delete toRemove->value; // Deallocate Rectangle object
                delete toRemove;        // Deallocate node
                return;
            }
            for(Node<T> *current = head; current->next != nullptr; current = current->next) {
                if(current->next == n) {
                    Node<T> *toRemove = current->next;
                    current->next = current->next->next;
                    delete toRemove->value; // Deallocate Rectangle object
                    delete toRemove;        // Deallocate node
                    delete current;        
                    return;
                }
            }
        }

        friend std::ostream &operator<<(std::ostream &os, LinkedList<T> &l) {
            int i = 0;
            for(Node<T> *current = l.head; current != nullptr; current = current->next) {
                if(current->value != nullptr)
                    os << "LinkedList[" << i << "] = Base: " << current->value->base << ", Height: " << current->value->height << "\n";
                i++;
            }
            return os;
        }
};  

bool isNumeric(string &s) {
    for(int i = 0; i < s.length(); i++)
        if(isdigit(s[i]) == false && s[i] != '.')
            return false;
    return true;
}

class Rectangle {
    public:
        double base;
        double height;
        
        Rectangle(): base(0), height(0) {}
        
        Rectangle(double b, double h): base(b), height(h) {}

        double getArea() {
            return base*height;
        }

        static Rectangle *create() {
            askforbase:
            cout << "Insert the base value: ";
            string input;
            cin >> input;
            if(isNumeric(input)) {
                Rectangle *r = new Rectangle();
                r->base = stod(input);
                askforheight:
                cout << "Insert the height value: ";
                string input;
                cin >> input;
                if(isNumeric(input)) {
                    r->height = stod(input);
                    return r;
                } else {
                    goto askforheight;
                }
            } else {
                cout << "Invalid number.\n";
                goto askforbase;
            }
        }

        static void insertRectangles(LinkedList<Rectangle *> &list) {
            cout << "How many rectangles do you want to insert?\n";
            string input;
            cin >> input;
            if(isNumeric(input)) {
                for(int i = 0; i < stoi(input); i++) {
                    Rectangle *r = Rectangle::create();
                    list.push(r);
                }
            }
        }

        static void deleteRectangles(LinkedList<Rectangle *> *list, const double minArea, const double maxArea) {
            deleteels:
            if(list->head == nullptr) {return;}
            if(list->head->value != nullptr && list->head->value->getArea() >= minArea && list->head->value->getArea() <= maxArea) {
                list->remove(list->head);
                goto deleteels;
            }
            for(Node<Rectangle *> *current = list->head; current->next != nullptr; current = current->next) {
                if(current->next->value != nullptr && current->next->value->getArea() >= minArea && current->next->value->getArea() <= maxArea) {
                    list->remove(current->next);
                    goto deleteels;
                }
            }
        }

        static void deleteRectangles2(LinkedList<Rectangle *> *list, const double minArea, const double maxArea) {
            Node<Rectangle *> *current = list->head;
            Node<Rectangle *> *prev = nullptr;
            while (current != nullptr) {
                if (current->value != nullptr && current->value->getArea() >= minArea && current->value->getArea() <= maxArea) {
                    if (prev == nullptr) {
                        list->head = current->next;
                    } else {
                        prev->next = current->next;
                    }
                    delete current->value; // Deallocate Rectangle object
                    delete current;        // Deallocate node
                    current = (prev == nullptr) ? list->head : prev->next;
                } else {
                    prev = current;
                    current = current->next;
                }
            }
        }
};

int main() {
    LinkedList<Rectangle *> rectangles;
    Rectangle::insertRectangles(rectangles);
    cout << "Inserted rectangles: \n" << rectangles;
    string min, max;
    cout << "Min area: ";
    cin >> min;
    cout << "Max area: ";
    cin >> max;
    Rectangle::deleteRectangles(&rectangles, stod(min), stod(max));
    cout << "Remaining rectangles: \n" << rectangles;
    return 0;
}