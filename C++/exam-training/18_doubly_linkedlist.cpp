#include <iostream>

using namespace std;

template <typename T>
struct Node {
    T value;
    Node<T> *prev;
    Node<T> *next;
};

template <typename T>
class DoublyLinkedList {
    public:
        Node<T> *head;

        DoublyLinkedList() : head(nullptr) {}

        void insertHead(T value) {
            Node<T> *newNode = new Node<T>;
            if(newNode == nullptr) exit(137);
            newNode->value = value;
            if(head == nullptr) {
                head = newNode;
                return;
            }
            head->prev = newNode;
            newNode->next = head;
            head = newNode;
        }


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
            newNode->prev = current;
            current->next = newNode;
        }

        void removeElement(T value) {
            if(head == nullptr) {
                return;
            }
            if(head->value == value) {
                Node<T> *toRemove = head;
                head = head->next;
                if (head != nullptr) {
                    head->prev = nullptr;
                }
                delete toRemove;
                return;
            }
            for(Node<T> *current = head; current->next != nullptr; current = current->next) {
                if(current->next->value == value) {
                    Node<T> *toRemove = current->next;
                    current->next = current->next->next;
                    if(current->next != nullptr) {
                        current->next->prev = current;
                    }
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

        friend ostream &operator<<(ostream &os, DoublyLinkedList<T> &l) {
            int i = 0;
            for(Node<T> *current = l.head; current != nullptr; current = current->next) {
                os << "DoublyLinkedList[" << i << "] = " << current->value << "\n";
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
    DoublyLinkedList<int> l;
    l.insertHead(1);
    l.insertHead(2);
    l.insertHead(3);
    l.insertEnd(4);
    l.insertEnd(5);
    l.removeElement(5);
    cout << l;
    int toFind = 2;
    cout << "Searching " << toFind << "...\n";
    Node<int> *found = l.findElement(toFind);
    if(found != NULL) cout << "Value " << toFind << " found at " << found << "!\n";
    l.deallocateList();
    return 0;
}