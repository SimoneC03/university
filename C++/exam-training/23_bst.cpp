#include <iostream>
#include <vector>

using std::cout, std::cin;

template<typename T>
struct Node {
    Node<T> *left;
    Node<T> *right;
    T value;
};

template<typename T>
class BinaryTree {

    private: 

    void insertAfter(Node<T> *n, Node<T> *newNode) {
        if(newNode == nullptr || n == nullptr) return;
        if(newNode->value < n->value) {
            if(n->left == nullptr) n->left = newNode;
            else insertAfter(n->left, newNode);
        }
        else {
            if(n->right == nullptr) n->right = newNode;
            else insertAfter(n->right, newNode);
        }
    }

    Node<T> *searchAfter(Node<T> *n, T value) {
        if(n == nullptr) return nullptr;
        else if(n->value == value) return n;
        return value < n->value ? searchAfter(n->left, value) : searchAfter(n->right, value);
    }

    public:
        Node<T> *root;

        BinaryTree() : root(nullptr) {}

        Node<T> *createNode(T value) {
            Node<T> *newNode = new Node<T>;
            if(newNode == nullptr) {
                cout << "Memory is full.\n";
                exit(137);
            }
            newNode->value = value;
            newNode->left = nullptr;
            newNode->right = nullptr;
            return newNode;
        }

        void insert(T value) {
            Node<T> *newNode = createNode(value);
            if(root == nullptr) {
                root = newNode;
                return;
            }
            insertAfter(root, newNode);
        }
        
        Node<T> *min() {
            if(root == nullptr) return nullptr;
            Node<T> *current = root;
            while(current->left != nullptr) current = current->left;
            return current;
        }

        Node<T> *max() {
            if(root == nullptr) return nullptr;
            Node<T> *current = root;
            while(current->right != nullptr) current = current->right;
            return current;
        }

        Node<T> *search(T value) {
            if(root == nullptr) return nullptr;
            else return searchAfter(root, value);
        }

        /* Print view of the BinaryTree using the Preorder algorithm */
        void preorder(Node<T> *n) {
            if(n == nullptr) return;
            cout << n->value << "\n";
            preorder(n->left);
            preorder(n->right);
        }

        /* Print view of the BinaryTree using the Inorder algorithm */
        void inorder(Node<T> *n) {
            if(n == nullptr) return;
            inorder(n->left);
            cout << n->value << "\n";
            inorder(n->right);
        }

        /* Print view of the BinaryTree using the Postorder algorithm */
        void postorder(Node<T> *n) {
            if(n == nullptr) return;
            postorder(n->left);
            postorder(n->right);
            cout << n->value << "\n";
        }

        void print() {
            preorder(root);
        }

};

int main() {
    BinaryTree<int> *tree = new BinaryTree<int>;
    tree->insert(8);
    tree->insert(2);
    tree->insert(5);
    tree->insert(1);
    tree->insert(9);
    tree->insert(13);
    tree->insert(19);
    tree->print();
    cout << "Min value is: " << tree->min()->value << "\n";
    cout << "Max value is: " << tree->max()->value << "\n";
    int toFind = 2;
    cout << "Searching " << toFind << "...\n";
    Node<int> *found = tree->search(toFind);
    if(found != NULL) cout << "Value " << toFind << " found at " << found << "!\n";
    else cout << "Value "<< toFind << " was not found.\n";
    return 0;
}