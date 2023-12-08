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

    /* Replace the subtree `n` with the subtree `newNode` */
    void transplant(Node<T> *n, Node<T> *newNode) {
        if(n == nullptr) return;
        if(n->parent == nullptr) root = newNode;
        else if(n->parent->left == n) n->parent->left = newNode;
        else n->parent->right = newNode;
        if(newNode != nullptr) newNode->parent = n->parent;
    }

    /* Search a node with a given `value` inside the tree */
    Node<T> *searchNode(T value) {
        Node<T> *current = root;
        while (current != nullptr && current->value != value) {
            if (value < current->value)
                current = current->left;
            else
                current = current->right;
        }
        return current;
    }

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

    /* Recolor the tree after a new node insertion to keep all the RB trees properties valid */
    void insertFixup(Node<T>* z) {
        while (z->parent != nullptr && z->parent->red) {
            if (z->parent == z->parent->parent->left) {
                Node<T>* y = z->parent->parent->right;
                if (y != nullptr && y->red) {
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
                if (y != nullptr && y->red) {
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

    Node<T> *min(Node<T> *n) {
        if(n == nullptr) return nullptr;
        Node<T> *current = n;
        while(current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    /* Delete a node `z` from the tree */
    void deleteNode(Node<T>* z) {
        if (z == nullptr) return;
        Node<T>* y = z;
        Node<T>* x;
        bool yOriginalColor = y->red;

        if (z->left == nullptr) {
            // Case 1
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == nullptr) {
            // Case 2
            x = z->left;
            transplant(z, z->left);
        } else {
            // Case 3
            y = min(z->right);
            yOriginalColor = y->red;
            x = y->right;
            
            if (y->parent == z) {
                if (x != nullptr) x->parent = y;
            } else {
                transplant(y, y->right);
                if (y->right != nullptr) y->right->parent = y;
                y->right = z->right;
                if (y->right != nullptr) y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            if (y->left != nullptr) y->left->parent = y;
            y->red = z->red;
        }
        delete z;
        if (!yOriginalColor) deleteFixup(x);
    }

    /* Recolor the tree after a new node deletion to keep all the RB trees properties valid */
    void deleteFixup(Node<T>* x) {
        while (x != root && !x->red) {
            if (x == x->parent->left) {
                Node<T>* w = x->parent->right;
                if (w->red) {
                    w->red = false;
                    x->parent->red = true;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if ((w->left == nullptr || !w->left->red) &&
                    (w->right == nullptr || !w->right->red)) {
                    w->red = true;
                    x = x->parent;
                } else {
                    if (w->right == nullptr || !w->right->red) {
                        if (w->left != nullptr) w->left->red = false;
                        w->red = true;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    w->red = x->parent->red;
                    x->parent->red = false;
                    if (w->right != nullptr) w->right->red = false;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                Node<T>* w = x->parent->left;
                if (w->red) {
                    w->red = false;
                    x->parent->red = true;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                if ((w->right == nullptr || !w->right->red) &&
                    (w->left == nullptr || !w->left->red)) {
                    w->red = true;
                    x = x->parent;
                } else {
                    if (w->left == nullptr || !w->left->red) {
                        if (w->right != nullptr) w->right->red = false;
                        w->red = true;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->red = x->parent->red;
                    x->parent->red = false;
                    if (w->left != nullptr) w->left->red = false;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        if (x != nullptr) x->red = false;
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

    /* Delete a node with a given `value` from the tree */
    void remove(T value) {
        Node<T>* z = searchNode(value);
        if (z != nullptr) deleteNode(z);
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
        if (n->red)
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
    rb_tree->insert(8);
    rb_tree->insert(9);
    cout << "RB Tree is:\n";
    cout << rb_tree;
    cout << "Removing 8 and 9 from the tree:\n";
    rb_tree->remove(8);
    rb_tree->remove(9);
    cout << rb_tree;
    return 0;
}