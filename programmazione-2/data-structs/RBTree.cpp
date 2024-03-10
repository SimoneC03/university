/* Red-Black Tree implementation */
#include <iostream>

using std::cout;

template <typename T>
class Node {
    public:
    Node *left;
    Node *right;
    Node *p; // parent
    bool red;
    T value;

    Node(T value) : left(nullptr), right(nullptr), p(nullptr), red(true), value(value) {}
};

template <typename T>
class RBTree {
private:
    Node<T> *root;

    /* Replace the subtree `n` with the subtree `newNode` */
    void transplant(Node<T> *n, Node<T> *newNode) {
        if(n == nullptr) return;
        if(n->p == nullptr) root = newNode;
        else if(n->p->left == n) n->p->left = newNode;
        else n->p->right = newNode;
        if(newNode != nullptr) newNode->p = n->p;
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
    void insertNode(Node<T> *z) {
        if(z == nullptr) return;

        Node<T> *y = nullptr;
        Node<T> *x = root;

        while (x != nullptr) {
            y = x;
            if (z->value < x->value)
                x = x->left;
            else
                x = x->right;
        }

        z->p = y;
        if (y == nullptr)
            root = z;
        else if (z->value < y->value)
            y->left = z;
        else
            y->right = z;
        insertFixup(z);
    }

    /* Perform recolor and rotate operations on the tree after a new node 
     * insertion to keep all the RB trees properties valid */
    void insertFixup(Node<T> *z) {
        while (z->p != nullptr && z->p->red) {
            if (z->p == z->p->p->left) {
                Node<T> *y = z->p->p->right;
                if (y != nullptr && y->red) {
                    z->p->red = false;
                    y->red = false;
                    z->p->p->red = true;
                    z = z->p->p;
                } else {
                    if (z == z->p->right) {
                        z = z->p;
                        leftRotate(z);
                    }
                    z->p->red = false;
                    z->p->p->red = true;
                    rightRotate(z->p->p);
                }
            } else {
                Node<T> *y = z->p->p->left;
                if (y != nullptr && y->red) {
                    z->p->red = false;
                    y->red = false;
                    z->p->p->red = true;
                    z = z->p->p;
                } else {
                    if (z == z->p->left) {
                        z = z->p;
                        rightRotate(z);
                    }
                    z->p->red = false;
                    z->p->p->red = true;
                    leftRotate(z->p->p);
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
    void deleteNode(Node<T> *z) {
        if (z == nullptr) return;
        Node<T> *y = z;
        Node<T> *x;
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
            
            if (y != z->right) {
                transplant(y, y->right);
                y->right = z->right;
                if (y->right != nullptr) y->right->p = y;
            } else if (x != nullptr) x->p = y;
            transplant(z, y);
            y->left = z->left;
            if (y->left != nullptr) y->left->p = y;
            y->red = z->red;
        }
        delete z;
        if (!yOriginalColor) deleteFixup(x);
    }

    /* Recolor the tree after a new node deletion to keep all the RB trees properties valid */
    void deleteFixup(Node<T> *x) {
        while (x != nullptr && x != root && !x->red) {
            if (x->p != nullptr && x == x->p->left) {
                Node<T> *w = x->p->right;
                if (w->red) {
                    w->red = false;
                    x->p->red = true;
                    leftRotate(x->p);
                    w = x->p->right;
                }
                if ((w->left == nullptr || !w->left->red) &&
                    (w->right == nullptr || !w->right->red)) {
                    w->red = true;
                    x = x->p;
                } else {
                    if (w->right == nullptr || !w->right->red) {
                        if (w->left != nullptr) w->left->red = false;
                        w->red = true;
                        rightRotate(w);
                        w = x->p->right;
                    }
                    w->red = x->p->red;
                    x->p->red = false;
                    if (w->right != nullptr) w->right->red = false;
                    leftRotate(x->p);
                    x = root;
                }
            } else {
                Node<T> *w = x->p->left;
                if (w->red) {
                    w->red = false;
                    x->p->red = true;
                    rightRotate(x->p);
                    w = x->p->left;
                }
                if ((w->right == nullptr || !w->right->red) &&
                    (w->left == nullptr || !w->left->red)) {
                    w->red = true;
                    x = x->p;
                } else {
                    if (w->left == nullptr || !w->left->red) {
                        if (w->right != nullptr) w->right->red = false;
                        w->red = true;
                        leftRotate(w);
                        w = x->p->left;
                    }
                    w->red = x->p->red;
                    x->p->red = false;
                    if (w->left != nullptr) w->left->red = false;
                    rightRotate(x->p);
                    x = root;
                }
            }
        }
        if (x != nullptr) x->red = false;
    }

    /* Rotate a node `x` to the left */
    void leftRotate(Node<T> *x) {
        Node<T> *y = x->right;
        x->right = y->left;
        if (y->left != nullptr)
            y->left->p = x;
        y->p = x->p;
        if (x->p == nullptr)
            root = y;
        else if (x == x->p->left)
            x->p->left = y;
        else
            x->p->right = y;
        y->left = x;
        x->p = y;
    }

    /* Delete a node with a given `value` from the tree */
    void remove(T value) {
        Node<T> *z = searchNode(value);
        if (z != nullptr) deleteNode(z);
    }

    /* Rotate a node `x` to the right */
    void rightRotate(Node<T> *x) {
        Node<T> *y = x->left;
        x->left = y->right;
        if (y->right != nullptr)
            y->right->p = x;
        y->p = x->p;
        if (x->p == nullptr)
            root = y;
        else if (x == x->p->right)
            x->p->right = y;
        else
            x->p->left = y;
        y->right = x;
        x->p = y;
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
    cout << "RB Tree is:\n(preorder view)\n";
    cout << rb_tree;
    cout << "Removing 8 and 9 from the tree:\n(preorder view)\n";
    rb_tree->remove(4);
    rb_tree->remove(5);
    cout << rb_tree;
    return 0;
}