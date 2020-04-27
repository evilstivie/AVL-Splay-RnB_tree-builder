#include "backend.h"

#define compLT(a,b) (a < b)
#define compEQ(a,b) (a == b)

#define nllptr &sentinel

Node sentinel = { nullptr, nullptr, 0, BLACK, 0};

Node *rotateLeft(Node *root, Node *x) {
    Node *y = x->right;

    x->right = y->left;
    if (y->left != nullptr) y->left->parent = x;

    if (y != nullptr) {
        y->parent = x->parent;
    }
    if (x->parent) {
        if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
    } else {
        root = y;
    }

    y->left = x;
    if (x != nullptr) {
        x->parent = y;
    }

    return root;
}

Node *rotateRight(Node *root, Node *x) {
    Node *y = x->left;

    x->left = y->right;
    if (y->right != nullptr) {
        y->right->parent = x;
    }

    if (y != nullptr) {
        y->parent = x->parent;
    }
    if (x->parent) {
        if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
    } else {
        root = y;
    }

    y->right = x;
    if (x != nullptr) {
        x->parent = y;
    }

    return root;
}

Node *insertFixup(Node *root, Node *x) {
    while (x != root && x->parent->color == RED) {
        if (x->parent == x->parent->parent->left) {
            Node *y = x->parent->parent->right;

            if (y != nullptr) {
                if (y->color == RED) {
                    x->parent->color = BLACK;
                    y->color = BLACK;
                    x->parent->parent->color = RED;
                    x = x->parent->parent;
                } else {
                    if (x == x->parent->right) {
                        x = x->parent;
                        root = rotateLeft(root, x);
                    }

                    x->parent->color = BLACK;
                    x->parent->parent->color = RED;
                    root = rotateRight(root, x->parent->parent);
                }
            } else {
                if (x == x->parent->right) {
                    x = x->parent;
                    root = rotateLeft(root, x);
                }

                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                root = rotateRight(root, x->parent->parent);
            }
        } else {
            Node *y = x->parent->parent->left;
            if (y != nullptr) {
                if (y->color == RED) {
                    x->parent->color = BLACK;
                    y->color = BLACK;
                    x->parent->parent->color = RED;
                    x = x->parent->parent;
                } else {
                    if (x == x->parent->left) {
                        x = x->parent;
                        root = rotateRight(root, x);
                    }
                    x->parent->color = BLACK;
                    x->parent->parent->color = RED;
                    root = rotateLeft(root, x->parent->parent);
                }
            } else {
                if (x == x->parent->left) {
                    x = x->parent;
                    root = rotateRight(root, x);
                }
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                root = rotateLeft(root, x->parent->parent);
            }
        }
    }
    root->color = BLACK;
    return root;
}

Node *insertNode(Node *root, int64_t val) {
    Node *current, *parent, *x;

    current = root;
    parent = 0;

    while (current != nullptr) {
        if (compEQ(val, current->val)) {
            return root;
        }
        parent = current;
        current = compLT(val, current->val) ? current->left : current->right;
    }

    x = new Node;
    x->val = val;
    x->parent = parent;
    x->left = nullptr;
    x->right = nullptr;
    x->color = RED;

    if (parent) {
        if (compLT(val, parent->val)) {
            parent->left = x;
        } else {
            parent->right = x;
        }
    } else {
        root = x;
    }

    root = insertFixup(root, x);
    return root;
}

Node *deleteFixup(Node *root, Node *x) {
    if (x == nullptr) {
        return root;
    }
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node *w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                root = rotateLeft (root, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    root = rotateRight (root, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                root = rotateLeft (root, x->parent);
                x = root;
            }
        } else {
            Node *w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                root = rotateRight (root, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    root = rotateLeft (root, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                root = rotateRight (root, x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
    return root;
}

Node *deleteNode(Node *root, Node *z) {
    if (!z || z == nullptr) {
        return root;
    }

    Node *x, *y;
    if (z->left == nullptr || z->right == nullptr) {
        y = z;
    } else {
        y = z->right;
        while (y->left != nullptr) {
            y = y->left;
        }
    }

    if (y->left != nullptr || y->right != nullptr) {
        if (y->left != nullptr) {
            x = y->left;
        } else {
            x = y->right;
        }

        x->parent = y->parent;
    } else {
        x = nullptr;
    }

    if (y->parent) {
        if (y == y->parent->left) {
            y->parent->left = x;
        } else {
            y->parent->right = x;
        }
    } else {
        root = x;
    }
    if (y != z) {
        z->val = y->val;
    }

    if (y->color == BLACK) {
        root = deleteFixup (root, x);
    }

    delete y;

    return root;
}

Node *findNode(Node *root, int64_t val) {
    Node *current = root;

    while (current != nullptr) {
        if (compEQ(val, current->val)) {
            return (current);
        } else {
            current = compLT (val, current->val) ? current->left : current->right;
        }
    }
    return 0;
}

int size_rb(Node *x) {
    if (x == nullptr) {
        return 0;
    }
    if (x->left == nullptr && x->right == nullptr) {
        return 1;
    }
    int resl = 0;
    if (x->left != nullptr) {
        resl = size_rb(x->left);
    }
    int resr = 0;
    if (x->right != nullptr) {
        resr = size_rb(x->right);
    }
    return 1 + resl + resr;
}

int height_rb(Node *x) {
    if (x == nullptr) {
        return 0;
    }
    if (x->left == nullptr && x->right == nullptr) {
        return 1;
    }
    int resl = 0;
    if (x->left != nullptr) {
        resl = height_rb(x->left);
    }
    int resr = 0;
    if (x->right != nullptr) {
        resr = height_rb(x->right);
    }
    return 1 + max(resl, resr);
}
