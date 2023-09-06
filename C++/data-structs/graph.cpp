#include <iostream>

using std::cout;

/* Struct representing a Node of a Linked list with a pointer to the next element */
template <typename T>
struct Node {
    T value;
    Node<T> *next;
};

/* A Linked list to store all edges of the vertices */
template <typename T>
class LinkedList {
    public:
        Node<T> *head;

        LinkedList() : head(nullptr) {}

        /* Push a `value` at the end of the list */
        void push_back(T value) {
            Node<T> *newNode = new Node<T>;
            if(newNode == nullptr) exit(137);
            newNode->value = value;
            if(head == nullptr) {
                head = newNode;
                return;
            }
            Node<T> *current = head;
            while(current->next != nullptr) current = current->next;
            current->next = newNode;
        }

        /* Remove a node with a given `value` from the list */
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

        /* Print all values of the list */
        friend std::ostream &operator<<(std::ostream &os, LinkedList<T> *l) {
            for(Node<T> *current = l->head; current != nullptr; current = current->next) {
                os << current->value << ", ";
            }
            return os;
        }
};

/* Struct representing a Node of a Linked list with a pointer to the next element */
template <typename T>
struct Vertex {
    T value;
    Vertex<T> *next;
    LinkedList<T> *edges;
};

template <typename T>
class Graph {
    public:
        Vertex<T> *initial;

        Graph() : initial(nullptr) {}

        /* Push a new vertex with a given `value` at the end of the Graph's list */
        void addVertex(T value) {
            Vertex<T> *newVertex = new Vertex<T>;
            if(newVertex == nullptr) return;
            newVertex->value = value;
            newVertex->edges = new LinkedList<T>;
            if(initial == nullptr) {
                initial = newVertex;
                return;
            }
            Vertex<T> *current = initial;
            while(current->next != nullptr) current = current->next;
            current->next = newVertex;
        }

        /* Create a new edge linking a `from` vertex with a `to` vertex. It can be bidirectional if specified */
        void addEdge(T from, T to, bool bidirectional = false) {
            if(initial == nullptr) return;
            Vertex<T> *fromV = findVertex(from);
            Vertex<T> *toV = findVertex(to);
            if(fromV == nullptr) {
                addVertex(from);
                fromV = findVertex(from);
            }
            if(toV == nullptr) {
                addVertex(to);
                toV = findVertex(to);
            }
            fromV->edges->push_back(to);
            if(bidirectional) toV->edges->push_back(from);
        }

        /* Return a pointer to a vertex with a given `value` if exists */
        Vertex<T> *findVertex(T value) {
            if(initial == nullptr) return nullptr;
            for(Vertex<T> *current = initial; current != nullptr; current = current->next) {
                if(current->value == value) {
                    return current;
                }
            }
            return nullptr;
        }

        /* Remove an edge between the `from` and the `to` vertices if exists */
        void removeEdge(T from, T to) {
            if(initial == nullptr) return;
            Vertex<T> *fromV = findVertex(from);
            Vertex<T> *toV = findVertex(to);
            if(fromV == nullptr || toV == nullptr) return;
            fromV->edges->remove(to);
            toV->edges->remove(from);
        }

        /* Remove a vertex with a given `value` from the graph */
        void removeVertex(T value) {
            if(initial == nullptr) return;
            Vertex<T> *toRemove = findVertex(value);
            if(toRemove == nullptr) return;
            for(Vertex<T> *current = initial; current != nullptr; current = current->next) {
                current->edges->remove(value);
            }
            if(initial->value == value) {
                Vertex<T> *toRemove = initial;
                initial = initial->next;
                delete toRemove->edges;
                delete toRemove;
                return;
            }
            Vertex<T> *current = initial;
            while(current->next != nullptr) {
                if(current->next->value == value) {
                    Vertex<T> *toRemove = current->next;
                    current->next = current->next->next;
                    delete toRemove->edges;
                    delete toRemove;
                    return;
                } else current = current->next;
            }
        }

        /* Print the graph */
        friend std::ostream &operator<<(std::ostream &os, Graph<T> *g) {
            int i = 0;
            for(Vertex<T> *current = g->initial; current != nullptr; current = current->next) {
                os << "Vertex " << i << ":   " << current->value << " -> " << current->edges << "\n";
                i++;
            }
            return os;
        }
};

int main() {
    Graph<int> *g = new Graph<int>;
    g->addVertex(1);
    g->addEdge(1, 2, true);
    g->addEdge(2, 3, true);
    g->addEdge(4, 2, true);
    g->addEdge(1, 3, true);
    g->addEdge(1, 4, true);
    g->addEdge(5, 4, false);
    cout << "Graph:\n";
    cout << g;
    cout << "Removing vertex with 4 value\n";
    g->removeVertex(4);
    cout << g;
}