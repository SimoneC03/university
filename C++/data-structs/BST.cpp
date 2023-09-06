#include <iostream>

using std::cin, std::cout;

template <typename T>
struct Node {
    T value;
    Node<T> *left;
    Node<T> *right;
    Node<T> *father;
};

/* Binary Search Tree */
template <typename T>
class BST {
    private:
    
        /* Recursive method to insert a newNode after a given node. */
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

        /* Replace the subtree `n` with the subtree `newNode` */
        void transplant(Node<T> *n, Node<T> *newNode) {
            if(n == nullptr) return;
            if(n->father == nullptr) root = newNode;
            else if(n->father->left == n) n->father->left = newNode;
            else n->father->right = newNode;
            if(newNode != nullptr) newNode->father = n->father;
        }

        /* Recursively search a value after a node */
        Node<T> *searchAfter(Node<T> *n, T value) {
            if(n == nullptr) return nullptr;
            if(value == n->value) return n;
            return (value < n->value) ? searchAfter(n->left, value) : searchAfter(n->right, value);
        }

    public:
        Node<T> *root;

        BST(): root(nullptr) {}

        Node<T> *min(Node<T> *n) {
            if(n == nullptr) return nullptr;
            Node<T> *current = n;
            while(current->left != nullptr) {
                current = current->left;
            }
            return current;
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
            Node<T> *newNode = createNode(value);
            if(root == nullptr) {
                root = newNode;
                return;
            }
            insertAfter(root, newNode);
        }

        void deleteNode(Node<T> *n) {
            if(n == nullptr) return;
            else if(n->left == nullptr) transplant(n, n->right);
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
        }

        Node<T> *search(T value) {
            if(root == nullptr) return nullptr;
            if(root->value == value) return root;
            return searchAfter(root, value);
        }

        void remove(T value) {
            if(root == nullptr) return;
            Node<T> *toRemove = search(value);
            deleteNode(toRemove);
        }

        static void preorderPrint(Node<T> *n) {
            if(n == nullptr) return;
            cout << n->value << "\n";
            preorderPrint(n->left);
            preorderPrint(n->right);
        }

        void inorderPrint(Node<T> *n) {
            if(n == nullptr) return;
            inorderPrint(n->left);
            cout << n->value << "\n";
            inorderPrint(n->right);
        }
        
        void postorderPrint(Node<T> *n) {
            if(n == nullptr) return;
            postorderPrint(n->left);
            postorderPrint(n->right);
            cout << n->value << "\n";
        }

        friend void operator<<(std::ostream &os, BST<T> *bst) {
            preorderPrint(bst->root);
        }
};

int main() {
    BST<int> *tree = new BST<int>();
    tree->insert(1);
    tree->insert(2);
    tree->insert(3);
    tree->insert(4);
    tree->insert(5);
    tree->insert(6);
    tree->remove(6);
    cout << "Tree:\n" << tree;
    int toFind = 2;
    cout << "Searching " << toFind << "...\n";
    Node<int> *found = tree->search(toFind);
    if(found != NULL) cout << "Value " << toFind << " found at " << found << "!\n";
    else cout << "Value "<< toFind << " was not found.\n";
    return 0;
}