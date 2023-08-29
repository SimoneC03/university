#include <iostream>

using namespace std;

template <typename T>
struct Node {
    T value;
    Node<T> *next;
};

template <typename T>
class SortedLinkedList {
    public:
        Node<T> *head;

        SortedLinkedList(): head(nullptr) {}

        void insert(T value) {
            Node<T> *newNode = new Node<T>;
            if(newNode == nullptr) exit(137);
            newNode->value = value;
            if(head == nullptr) {
                head = newNode;
                return;
            }
            if(value <= head->value) {
                newNode->next = head;
                head = newNode;
                return;
            }
            Node<T> *current = head;
            if(current->next == nullptr) {
                current->next = newNode;
                return;
            }
            while(current->next != nullptr) {
                if(value <= current->next->value) {
                    newNode->next = current->next;
                    current->next = newNode;
                    return;
                }
                current = current->next;
            }
            current->next = newNode;
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

        friend ostream &operator<<(ostream &os, SortedLinkedList<T> &l) {
            int i = 0;
            for(Node<T> *current = l.head; current != nullptr; current = current->next) {
                os << "SortedList[" << i <<"] = " << current->value << "\n";
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
    SortedLinkedList<int> l;
    l.insert(4);
    l.insert(2);
    l.insert(11);
    l.insert(81);
    l.insert(10);
    l.insert(123);
    l.insert(15);
    l.insert(3);
    l.insert(-1);
    l.removeElement(3);
    cout << l;
    int toFind = 2;
    cout << "Searching " << toFind << "...\n";
    Node<int> *found = l.findElement(toFind);
    if(found != NULL) cout << "Value " << toFind << " found at " << found << "!\n";
    l.deallocateList();
    return 0;
}