#include <iostream>

using std::cout;

template <typename T>
struct Node {
    Node<T> *next;
    T value;
};

template <typename T>
class Queue {
    Node<T> *head;
    public:
        Queue() : head(nullptr) {}

        /* Insert a new `value` at the end of the queue */
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

        /* Remove the first element inserted inside the list */
        void dequeue() {
            if(isEmpty()) {
                cout << "Cannot dequeue: queue is empty.\n";
            }
            Node<T> *toRemove = head;
            head = head->next;
            delete toRemove;
        }

        /* Return the first element inserted inside the list */
        T *front() {
            int *value = nullptr;
            if(!isEmpty()) {
                value = &head->value;
            }
            return value;
        }

        /* Return whether the queue is empty or not */
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