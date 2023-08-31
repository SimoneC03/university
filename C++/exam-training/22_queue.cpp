#include <iostream>

using std::cout;

template <typename T>
struct Node {
    Node<T> *next;
    T value;
};

template <typename T>
class Queue {
    public:
        Node<T> *head;

        Queue() : head(nullptr) {}

        void enqueue(T value) {
            Node<T> *newNode = new Node<T>;
            if(newNode == nullptr) exit(137);
            newNode->value = value;
            if(isEmpty()) {
                head = newNode;
                return;
            }
            Node<T> *current = head;
            while(current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }

        void dequeue() {
            if(isEmpty()) {
                cout << "Cannot dequeue: queue is empty.\n";
            }
            Node<T> *toRemove = head;
            head = head->next;
            delete toRemove;
        }

        T *front() {
            int *value = nullptr;
            if(!isEmpty()) {
                value = &head->value;
            }
            return value;
        }

        bool isEmpty() {
            return head == nullptr;
        }

        friend std::ostream &operator<<(std::ostream &os, Queue<T> &queue) {
            int i = 0;
            for(Node<T> *current = queue.head; current != nullptr; current = current->next) {
                os << "Queue[" << i << "] = " << current->value << (i == 0 ? " (HEAD)\n" : (current->next == nullptr) ? " (TAIL)\n" : "\n");
                i++;
            }
            return os;
        }
};

int main() {
    Queue<int> queue;
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    queue.enqueue(4);
    cout << queue;
    cout << "Dequeue first element\n";
    queue.dequeue();
    cout << queue;
}