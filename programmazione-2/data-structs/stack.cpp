#include <iostream>

using std::cout;

template <typename T>
struct Node {
    Node<T> *next;
    T value;
};

template <typename T>
class Stack {
    Node<T> *head;
    
    public:
        Stack() : head(nullptr) {}

        /* Push a new `value` at the end of the stack */
        void push(T value) {
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

        /* Remove and return the last pushed element inside the list */
        T pop() {
            if(head == nullptr) {
                cout << "Stack is empty.\n";
                exit(1);
            }
            if(head->next == nullptr) {
                Node<T> *toRemove = head;
                T value = toRemove->value;
                head = nullptr;
                delete toRemove;
                return value;
            }
            Node<T> *current = head;
            while(current->next->next != nullptr) {
                current = current->next;
            }
            Node<T> *toRemove = current->next;
            T value = toRemove->value;
            current->next = nullptr;
            delete toRemove;
            return value;
        }

        friend std::ostream &operator<<(std::ostream &os, Stack<T> &stack) {
            int i = 0;
            for(Node<T> *current = stack.head; current != nullptr; current = current->next) {
                os << "Stack[" << i << "] = " << current->value << "\n";
                i++;
            }
            return os;
        }
};

int main() {
    Stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    cout << stack;
    cout << "Last element " << stack.pop() << " removed\n";
    cout << stack;
    return 0;
}