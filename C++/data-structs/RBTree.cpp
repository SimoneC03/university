/* Red-Black Tree implementation */
#include <iostream>

using std::cout;

template <typename T>
class Node {
    public:
    Node *left;
    Node *right;
    Node *parent;
    bool red;
    T value;

    Node(T value) : left(nullptr), right(nullptr), parent(nullptr), red(true), value(value) {}
};

template <typename T>
class RBTree {
private:
    Node<T> *root;

public:
    RBTree() : root(nullptr) {}

    Node<T> *createNode(T value) {
        Node<T> *newNode = new Node<T>(value);
        if (newNode == nullptr)
            exit(137);
        return newNode;
    }

    /* Insert a new node `z` */
    void insertNode(Node<T>* z) {
        Node<T>* y = nullptr;
        Node<T>* x = root;

        while (x != nullptr) {
            y = x;
            if (z->value < x->value)
                x = x->left;
            else
                x = x->right;
        }

        z->parent = y;
        if (y == nullptr)
            root = z;
        else if (z->value < y->value)
            y->left = z;
        else
            y->right = z;
        insertFixup(z);
    }

    /* Recolor the tree after a new node insertion to keep all the RB trees properties */
    void insertFixup(Node<T>* z) {
        while (z->parent != nullptr && z->parent->red == true) {
            if (z->parent == z->parent->parent->left) {
                Node<T>* y = z->parent->parent->right;
                if (y != nullptr && y->red == true) {
                    z->parent->red = false;
                    y->red = false;
                    z->parent->parent->red = true;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->red = false;
                    z->parent->parent->red = true;
                    rightRotate(z->parent->parent);
                }
            } else {
                Node<T>* y = z->parent->parent->left;
                if (y != nullptr && y->red == true) {
                    z->parent->red = false;
                    y->red = false;
                    z->parent->parent->red = true;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->red = false;
                    z->parent->parent->red = true;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->red = false;
    }

    /* Rotate a node `x` to the left */
    void leftRotate(Node<T>* x) {
        Node<T>* y = x->right;
        x->right = y->left;
        if (y->left != nullptr)
            y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    /* Rotate a node `x` to the right */
    void rightRotate(Node<T>* x) {
        Node<T>* y = x->left;
        x->left = y->right;
        if (y->right != nullptr)
            y->right->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

    /* Store a new `value` inside the tree */
    void insert(T value)
    {
        Node<T> *toInsert = createNode(value);
        insertNode(toInsert);
    }

    static void preorderPrint(Node<T> *n) {
        if (n == nullptr)
            return;
        if (n->red == true)
            cout << "\x1B[31m" << n->value << "\033[0m\n";
        else
            cout << n->value << "\n";
        preorderPrint(n->left);
        preorderPrint(n->right);
    }

    friend void operator<<(std::ostream &os, RBTree<T> *t) {
        if (t->root != nullptr) {
            preorderPrint(t->root);
        }
    }
};

int main() {
    RBTree<int> *rb_tree = new RBTree<int>();
    rb_tree->insert(1);
    rb_tree->insert(2);
    rb_tree->insert(3);
    rb_tree->insert(4);
    rb_tree->insert(5);
    rb_tree->insert(6);
    rb_tree->insert(7);
    cout << rb_tree;
    return 0;
}