#include <iostream>

using namespace std;

template <typename T>
struct Node {
    T value;
    Node<T> *next;
    Node<T> *prev;
};

template <typename T>
class CircularDoublyLinkedList {

    public:
        Node<T> *start;

        void insertBegin(T value) {
            Node<T> *newNode = new Node<T>;
            if(newNode == nullptr) exit(137);
            newNode->value = value;
            if(start == nullptr) {
                start = newNode;
                return;
            }
            newNode->prev = (start->prev == nullptr) ? start : start->prev;
            newNode->next = start;
            if(start->prev != nullptr) start->prev->next = newNode;
            start->prev = newNode;
            start = newNode;
        }

        void insertEnd(T value) {
            Node<T> *newNode = new Node<T>;
            if(newNode == nullptr) exit(137);
            newNode->value = value;
            if(start == nullptr) {
                start = newNode;
                return;
            }
            newNode->prev = start->prev;
            newNode->next = start;
            if(start->prev != nullptr) start->prev->next = newNode;
            start->prev = newNode;
        }

        Node<T> *find(T value) {
            Node<T> *current = start;
            while(current->next != start) {
                if(current->value == value) return current;
                current = current->next;
            }
            return nullptr;
        }
        
        void remove(T value) {
            if(start == nullptr) return;
            if(start->value == value) {
                Node<T> *toRemove = start;
                start = start->next;
                if(toRemove->prev != nullptr) toRemove->prev->next = start;
                start->prev = toRemove->prev;
                delete toRemove;
                return;
            }
            Node<T> *current = start;
            while(current->next != start) {
                if(current->value == value) {
                    Node<T> *toRemove = current;
                    current = current->next;
                    if(toRemove->prev != nullptr) toRemove->prev->next = current;
                    current->prev = toRemove->prev;
                    delete toRemove;
                    return;
                }
                current = current->next;
            }
            if(current->value == value) {
                Node<T> *toRemove = current;
                current = current->next;
                if(toRemove->prev != nullptr) toRemove->prev->next = current;
                current->prev = toRemove->prev;
                delete toRemove;
                return;
            }
        }

        void deallocate() {
            if(start == nullptr)
                return;
            Node<T> *current = start;
            while(current->next != start) {
                Node<T> *temp = current;
                current = current->next;
                delete temp;
            }
            delete current;
            start = nullptr;
        }

        friend ostream &operator<<(ostream &os, CircularDoublyLinkedList<T> &l) {
            int i = 0;
            Node<T> *current = l.start;
            while( current->next != l.start) {
                os << "CircularDoublyLinkedList["<< i <<"] = " << current->value << "\n";
                i++;
                current = current->next;
            }
            os << "CircularDoublyLinkedList["<< i <<"] = " << current->value << "\n";
            return os;
        }
};

int main() {
    CircularDoublyLinkedList<int> l;
    l.insertBegin(1);
    l.insertBegin(2);
    l.insertBegin(3);
    l.insertEnd(4);
    l.insertEnd(5);
    l.remove(5);
    cout << l;
    int toFind = 2;
    cout << "Searching " << toFind << "...\n";
    Node<int> *found = l.find(toFind);
    if(found != NULL) cout << "Value " << toFind << " found at " << found << "!\n";
    else cout << "Value "<< toFind << " was not found\n";
    l.deallocate();
    return 0;
}