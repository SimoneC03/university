#include <iostream>
#include <vector>

using std::cout, std::cin;

template<typename T>
struct Node {
    Node<T> *left;
    Node<T> *right;
    Node<T> *father;
    T value;
};

template<typename T>
class BinaryTree {

    private: 

    /* Recursive method to insert a newNode after a given node. */
    void insertAfter(Node<T> *n, Node<T> *newNode) {
        if(newNode == nullptr || n == nullptr) return;
        if(newNode->value < n->value) {
            if(n->left == nullptr) {
                newNode->father = n;
                n->left = newNode;
            } else insertAfter(n->left, newNode);
        }
        else {
            if(n->right == nullptr) {
                newNode->father = n;
                n->right = newNode;
            } else insertAfter(n->right, newNode);
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
            newNode->father = nullptr;
            return newNode;
        }

        void insertRecursive(T value) {
            Node<T> *newNode = createNode(value);
            if(root == nullptr) {
                root = newNode;
                return;
            }
            insertAfter(root, newNode);
        }

        void insert(T value) {
            Node<T> *newNode = createNode(value);
            if(root == nullptr) {
                root = newNode;
                return;
            }
            Node<T> *current = root;
            Node<T> *currentFather = nullptr;
            while(current != nullptr) {
                currentFather = current;
                if(value < current->value) current = current->left;
                else current = current->right;
            }
            newNode->father = currentFather;
            if(value < currentFather->value) currentFather->left = newNode;
            else currentFather->right = newNode;
        }

        Node<T> *min(Node<T> *n) {
            if(n == nullptr) return nullptr;
            Node<T> *current = n;
            while(current->left != nullptr) current = current->left;
            return current;
        }

        Node<T> *max(Node<T> *n) {
            if(n == nullptr) return nullptr;
            Node<T> *current = n;
            while(current->right != nullptr) current = current->right;
            return current;
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

        Node<T> *successor(Node<T> *n) {
            if(n->right != nullptr)
                return min(n->right);
            Node<T> *current = n->father;
            while(current != nullptr && n == current->right) {
                n = current;
                current = current->father;
            }
            return current;
        }

        /* Replace a subtree of root u with a new one of root n */
        void transplant(Node<T> *u, Node<T> *n) {
            if(u->father == nullptr) root = n;
            else if(u == u->father->left) u->father->left = n;
            else u->father->right = n;
            if(n != nullptr) n->father = u->father;
        }

        void deleteNode(Node<T> *n) {
            if(n == nullptr) return;
            if(n->left == nullptr) transplant(n, n->right);
            else if(n->right == nullptr) transplant(n, n->left);
            else {
                Node<T> *m = min(n->right);
                if(m->father != n) {
                    transplant(m, m->right);
                    m->right = n->right;
                    m->right->father = m;
                }
                transplant(n, m);
                m->left = n->left;
                m->left->father = m;
            }
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
    cout << "Successor of " << tree->root->right->value << " is: " << tree->successor(tree->root->right)->value << "\n";
    cout << "Deleting " << tree->root->right->value << "...\n";
    tree->deleteNode(tree->root->right);
    tree->print();
    return 0;
}