#include <iostream>

using std::cout;

template<typename T>
struct Node {
    T value;
    Node<T> *next;
};

template<typename T>
class LinkedList {
    public:
        Node<T> *head;

        LinkedList(): head(nullptr) {}

        void push_head(T value) {
            Node<T> *newNode = new Node<T>;
            if(newNode == nullptr) {
                cout << "Memory is full\n";
                return;
            }
            newNode->value = value;
            newNode->next = head;
            head = newNode;
        }

        void push_back(T value) {
            Node<T> *newNode = new Node<T>;
            if(newNode == nullptr) {
                cout << "Memory is full\n";
                return;
            }
            newNode->value = value;
            if(head == nullptr) {
                head = newNode;
                return;
            }
            Node<T> *current = head;
            while(current->next != nullptr) current = current->next;
            current->next = newNode;
        }

        void remove(T value) {
            if(head == nullptr) return;
            if(head->value == value) {
                Node<T> *toRemove = head;
                head = head->next;
                delete toRemove;
                return;
            }
            Node<T> *current = head;
            while(current->next != nullptr) {
                if(current->next->value == value) {
                    Node<T> *toRemove = current->next;
                    current->next = current->next->next;
                    delete toRemove;
                    return;
                } else current = current->next;
            }
        }

        friend std::ostream &operator<<(std::ostream &os, LinkedList *l) {
            int i = 0;
            for(Node<T> *current = l->head; current != nullptr; current = current->next) {
                os << "LinkedList[" << i << "] = " << current->value << "\n";
                i++;
            }
            return os;
        }
};


int main() {
    LinkedList<int> *l = new LinkedList<int>;
    l->push_back(1);
    l->push_back(2);
    l->push_back(3);
    l->push_head(4);
    cout << "LinkedList:\n";
    cout << l;
    l->remove(2);
    cout << "Removing 2...\n";
    cout << l;
    return 0;
}