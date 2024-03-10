#include <iostream>

using std::cout, std::string;

class Fruit {
    private:
        string name, color, season;
    
    public:
        Fruit(const string &name, const string &color, const string season) : name(name), color(color), season(season) {}

        string getName() {return name;}

        string getColor() {return color;}

        string getSeason() {return season;}

        friend std::ostream &operator<<(std::ostream &os, Fruit &fruit) {
            os << "Name: " << fruit.name << "\nColor: " << fruit.color << "\nSeason: " << fruit.season;
            return os;
        }

        virtual string getTaste() const = 0;
};

class Apple : public Fruit {
    public:
        string taste;
        Apple(const string &name, const string &color, const string &season, const string &taste) : Fruit(name, color, season), taste(taste) {};

        string getTaste() const override {
            return taste;
        }

        friend std::ostream &operator<<(std::ostream &os, Apple &apple) {
            os << static_cast<Fruit &>(apple)  << "\nTaste: " << apple.getTaste();
            return os;
        }
};

class Orange : public Fruit {
    public:
        string taste;
        Orange(const string &name, const string &color, const string &season, const string &taste) : Fruit(name, color, season), taste(taste) {};

        string getTaste() const override {
            return taste;
        }

        friend std::ostream &operator<<(std::ostream &os, Orange &orange) {
            os << static_cast<Fruit &>(orange)  << "\nTaste: " << orange.getTaste();
            return os;
        }
};

template <typename T>
struct Node {
    T value;
    Node<T> *next;
};

template <typename T>
class Queue {
    private:
        Node<T> *head;
        Node<T> *tail;
        int size;
    public:
        Queue(): head(nullptr) {}

        void enqueue(T value) {
            Node<T> *newNode = new Node<T>;
            if(newNode == nullptr) exit(137);
            newNode->value = value;
            if(isEmpty()) {
                head = newNode;
                tail = newNode;
                return;
            }
            tail->next = newNode;
            tail = newNode;
        }

        T dequeue() {
            if(isEmpty()) {
                // queue is empty
                exit(139);
            }
            Node<T> *toRemove = head;
            head = head->next;
            T temp = toRemove->value;
            delete toRemove;
            return temp;
        }

        T front() {
            if(isEmpty()) {
                // queue is empty
                exit(139);
            }
            return head->value;
        }

        bool isEmpty() {
            return head == nullptr;
        }

        void print() {
            int i = 0;
            for(Node<T> *current = head; current != nullptr; current = current->next) {
                Apple *apple = dynamic_cast<Apple *>(current->value);
                Orange *orange = dynamic_cast<Orange *>(current->value);
                if(apple != nullptr) cout << "Queue[" << i << "]:\n" << *apple << "\n\n";
                else if(orange != nullptr) cout << "Queue[" << i << "]:\n" << *orange << "\n\n";
                else cout << "Queue[" << i << "]:\n" << *current->value << "\n\n";
                i++;
            }
        }

        void removeFruitType(const string &type) {
            if(head == nullptr) return;
            Apple *apple = dynamic_cast<Apple *>(head->value);
            Orange *orange = dynamic_cast<Orange *>(head->value);
            // if type match head value type, delete it
            if((apple != nullptr && type.compare("apple") == 0) || (orange != nullptr && type.compare("orange") == 0)) {
                this->dequeue();
            }
            Node<T> *current = head;
            while(current->next != nullptr) {
                Apple *apple = dynamic_cast<Apple *>(current->next->value);
                Orange *orange = dynamic_cast<Orange *>(current->next->value);
                // if type match current element value type, delete it
                if((apple != nullptr && type.compare("apple") == 0) || (orange != nullptr && type.compare("orange") == 0)) {
                    current->next = current->next->next;
                } else {
                    current = current->next;
                }
            } 
        }
};

int main() {

    Queue<Fruit *> q = Queue<Fruit *>();
    q.enqueue(new Apple("Granny Smith", "Green", "Autumn", "Sour"));
    q.enqueue(new Orange("Tarocco", "Orange", "Winter", "Sweet"));
    q.enqueue(new Apple("Golden Delicious", "Yellow", "Winter", "Sweet"));
    q.enqueue(new Orange("Navel", "Orange", "Winter", "Sweet-acid"));
    q.enqueue(new Apple("Fuji", "Green", "Autumn", "Sweet"));
    q.enqueue(new Orange("Valencia", "Orange", "Summer", "Acid"));
    q.removeFruitType("orange");
    q.print();
}