#include <iostream>

using namespace std;

template <typename T>
struct Node {
    T value;
    Node<T> *next;
};

template <typename T>
class LinkedList {
    public:
        Node<T> *head;

        LinkedList() : head(nullptr) {}

        /* Add an element in head position */
        void insertHead(T value) {
            Node<T> *newNode = new Node<T>;
            if(newNode == NULL) exit(137);
            newNode->value = value;
            newNode->next = head;
            head = newNode;
        }

        /* Add an element at the end/tail position */
        void insertEnd(T value) {
            Node<T> *newNode = new Node<T>;
            if(newNode == nullptr) exit(137);
            newNode->value = value;
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

        void insertAfter(Node<T> *n, T value) {
            if(n == nullptr) {
                cout << "Node cannot be null\n";
                return;
            }
            Node<T> *newNode = new Node<T>;
            if(newNode == nullptr) exit(137);
            newNode->value = value;
            Node<T> *temp = n->next;
            n->next = newNode;
            newNode->next = temp;
        }

        void removeElement(T value) {
            if(head == nullptr) {
                return;
            }
            if(head->value == value) {
                Node<T> *toRemove = head;
                head = head->next;
                delete toRemove;
                return;
            }
            for(Node<T> *current = head; current->next != nullptr; current = current->next) {
                if(current->next->value == value) {
                    Node<T> *toRemove = current->next;
                    current->next = current->next->next;
                    delete toRemove;
                    return;
                }
            }
        }

        Node<T> *findElement(int value) {
            for(Node<T> *current = head; current != NULL; current = current->next) {
                if(current->value == value) {
                    return current;
                }
            }
            return NULL;
        }

        friend ostream &operator<<(ostream &os, LinkedList<T> &l) {
            int i = 0;
            for(Node<T> *current = l.head; current != nullptr; current = current->next) {
                os << "List[" << i << "] = " << current->value << "\n";
                i++;
            }
            return os;
        }

        void deallocateList() {
            if(head == NULL)
                return;
            Node<T> *current = head;
            while(current != NULL) {
                Node<T> *temp = current;
                current = current->next;
                delete temp;
            }
            head = NULL;
        }
};

int main() {
    LinkedList<int> l;
    l.insertHead(1);
    l.insertHead(2);
    l.insertEnd(3);
    l.insertAfter(l.head, 8);
    l.removeElement(1);
    cout << l;
    int toFind = 2;
    cout << "Searching " << toFind << "...\n";
    Node<int> *found = l.findElement(toFind);
    if(found != NULL) cout << "Value " << toFind << " found at " << found << "!\n";
    else cout << "Value " << toFind << " not found\n";
    l.deallocateList();
    return 0;
}