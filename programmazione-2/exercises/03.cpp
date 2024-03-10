#include <iostream>

using std::cin, std::cout, std::string;

class Animal {
    private:
        string name, breed;
        int age;

    public:
        Animal(const string &name, const string &breed, const int age) : name(name), breed(breed), age(age) {}

        string getName() {
            return name;
        }

        string getBreed() {
            return breed;
        }

        int getAge() {
            return age;
        }

        virtual string sound() const = 0;

        bool operator<(Animal &p) {
            return this->getName().compare(p.getName()) < 0;
        }

        bool operator==(Animal &p) {
            return this->getName().compare(p.getName()) == 0;
        }

        friend std::ostream &operator<<(std::ostream &os, Animal *animal) {
            os << "Name: " << animal->getName() << "\nBreed: " << animal->getBreed() << "\nAge: " << animal->getAge();
            return os;
        }
};

class Dog : public Animal {
    public:
        Dog(const string &name) : Animal(name, "", 0) {}

        Dog(const string &name, const string &breed, const int age): Animal(name, breed, age) {}

        string sound() const override {
            return "Woof!";
        }
        friend std::ostream &operator<<(std::ostream &os, Dog *dog) {
            os << static_cast<Animal *>(dog) << "\nType: Dog\n";
            return os;
        }
};

class Cat : public Animal {
    public:
        Cat(const string &name, const string &breed, const int age): Animal(name, breed, age) {}

        string sound() const override {
            return "Meow!";
        }
        friend std::ostream &operator<<(std::ostream &os, Cat *cat) {
            os << static_cast<Animal *>(cat) << "\nType: Cat\n";
            return os;
        }
};

template <typename T>
struct Node {
    Node<T> *left;
    Node<T> *right;
    Node<T> *father;
    T value;
};

template <typename T> 
class BST {
    private:
        Node<T> *root;
        int size;
        int max;

        void insertAfter(Node<T> *n, Node<T> *newNode) {
            if(n == nullptr || newNode == nullptr) return;
            if(newNode->value < n->value) {
                if(n->left == nullptr) {
                    newNode->father = n;
                    n->left = newNode;
                } else insertAfter(n->left, newNode);
            } else {
                if(n->right == nullptr) {
                    newNode->father = n;
                    n->right = newNode;
                } else insertAfter(n->right, newNode);
            }
        }

        void transplant(Node<T> *n, Node<T> *newNode) {
            if(n == nullptr) return;
            if(n->father->left == n) n->father->left = newNode;
            else n->father->right = newNode;
            if(newNode != nullptr) newNode->father = n->father;
        }

        /* Default animal type `value` is Dog for searching operations  */
        Node<T> *searchAfter(Node<T> *n, T value) {
            if(n == nullptr) return nullptr;
            Dog *d = dynamic_cast<Dog *>(value);
            Dog *nd = dynamic_cast<Dog *>(n->value);
            Cat *nc = dynamic_cast<Cat *>(n->value);
            if(d != nullptr && nd != nullptr) {
                if(*nd == *d) return n;
            } else if(d != nullptr && nc != nullptr) {
                if(*nc == *d) return n;
            } else if(n->value == value) return n;
            return value < n->value ? searchAfter(n->left, value) : searchAfter(n->right, value);
        }

    public:
        BST(): root(nullptr) {}

        void setMaxSize(const int max) {
            this->max = max;
        }

        Node<T> *createNode(T value) {
            Node<T> *newNode = new Node<T>;
            if(newNode == nullptr) exit(137);
            newNode->value = value;
            newNode->left = nullptr;
            newNode->right = nullptr;
            newNode->father = nullptr;
            return newNode;
        }

        void insert(T value) {
            if(size >= max) return;
            Node<T> *newNode = createNode(value);
            size++;
            if(root == nullptr) {
                root = newNode;
                return;
            }
            insertAfter(root, newNode);
        }

        Node<T> *search(T value) {
            if(root == nullptr) return nullptr;
            Dog *d = dynamic_cast<Dog *>(value);
            if(d != nullptr) {
                if(*root->value == *value) return root;
            } else {
                if(root->value == value) return root;
            }
            return searchAfter(root, value);
        }

        Node<T> *min(Node<T> *n) {
            if(n == nullptr) return nullptr;
            Node<T> *current = n;
            while (current->left != nullptr) current = current->left;
            return current;
        }

        void deleteNode(Node<T> *n) {
            if(n == nullptr) return;
            if(n->left == nullptr) transplant(n, n->right);
            else if(n->right == nullptr) transplant(n, n->left);
            else {
                Node<T> *mi = min(n->right);
                if(mi->father != n) {
                    transplant(mi, mi->right);
                    mi->right = n->right;
                    mi->right->father = mi;
                }
                transplant(n, mi);
                mi->left = n->left;
                mi->left->father = mi;
            }
            size--;
        }

        void preorder(Node<T> *n) {
            if(n == nullptr) return;
            Dog *d = dynamic_cast<Dog *>(n->value);
            Cat *c = dynamic_cast<Cat *>(n->value);
            if(d != nullptr) cout << d << "\n";
            else if(c != nullptr) cout << c << "\n";
            else cout << n->value << "\n";
            preorder(n->left);
            preorder(n->right);
        }

        void print() {
            this->preorder(root);
        }
        
        ~BST() {}
};

int main() {
    BST<Animal *> *tree = new BST<Animal *>;
    tree->setMaxSize(10);
    Dog *dog1 = new Dog("Fido", "Labrador", 3);
    Dog *dog2 = new Dog("Rex", "Pastore Tedesco", 5);
    Dog *dog3 = new Dog("Milo", "Beagle", 1);
    Cat *cat1 = new Cat("Luna", "Siamese", 2);
    Cat *cat2 = new Cat("Leo", "Persiano", 4);
    Cat *cat3 = new Cat("Nala", "Maine Coon", 3);
    tree->insert(dog1);
    tree->insert(cat1);
    tree->insert(dog2);
    tree->insert(cat2);
    tree->insert(dog3);
    tree->insert(cat3);
    cout << "Animals:\n";
    tree->print();
    cout << "Enter a name of an animal to search: ";
    string name;
    cin >> name;
    Dog *toSearch = new Dog(name); // default type where the type to search is unknow
    Node<Animal *> *found = tree->search(toSearch);
    if(found != nullptr) {
        Dog *d = dynamic_cast<Dog *>(found->value);
        Cat *c = dynamic_cast<Cat *>(found->value);
        if(d != nullptr) {
            cout << d->getName() << " is a " << d->getAge() << " years old dog.\n";
            cout << d->getName() << "'s sound is: " << d->sound() << "\n";
        } else if(c != nullptr) {
            cout << c->getName() << " is a " << c->getAge() << " years old cat.\n";
            cout << c->getName() << "'s sound is: " << c->sound() << "\n";
        }
    } else {
        cout << "No animal having that name found.\n";
    }
    return 0;
}