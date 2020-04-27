#include "backend.h"

splay* RR_Rotate(splay* k2) {
    splay* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    return k1;
}

splay* LL_Rotate(splay* k2) {
    splay* k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;
    return k1;
}

splay* Splay(int val, splay* root) {
    if (!root) {
        return nullptr;
    }

    splay header;
    header.left = header.right = nullptr;
    splay* LeftTreeMax = &header;
    splay* RightTreeMin = &header;
    while (1) {
        if (val < root->val) {
            if (!root->left) {
                break;
            }
            if (val < root->left->val) {
                root = RR_Rotate(root);
                // only zig-zig mode need to rotate once,
                if (!root->left)
                    break;
            }
            /* Link to R Tree */
            RightTreeMin->left = root;
            RightTreeMin = RightTreeMin->left;
            root = root->left;
            RightTreeMin->left = nullptr;
        }
        else if (val > root->val){
            if (!root->right)
                break;
            if (val > root->right->val)
            {
                root = LL_Rotate(root);
                // only zag-zag mode need to rotate once,
                if (!root->right)
                    break;
            }
            /* Link to L Tree */
            LeftTreeMax->right = root;
            LeftTreeMax = LeftTreeMax->right;
            root = root->right;
            LeftTreeMax->right = nullptr;
        }
        else
            break;
    }

    /* assemble L Tree, Middle Tree and R tree */
    LeftTreeMax->right = root->left;
    RightTreeMin->left = root->right;
    root->left = header.right;
    root->right = header.left;
    return root;
}

splay* New_Node(int val) {
    splay* p_node = new splay;

    p_node->val = val;
    p_node->left = p_node->right = nullptr;
    return p_node;
}

splay* Insert(int val, splay* root) {
    static splay* p_node = nullptr;
    if (!p_node)
        p_node = New_Node(val);
    else
        p_node->val = val;
    if (!root) {
        root = p_node;
        p_node = nullptr;
        return root;
    }

    root = Splay(val, root);

    if (val < root->val) {
        p_node->left = root->left;
        p_node->right = root;
        root->left = nullptr;
        root = p_node;
    } else if (val > root->val) {
        p_node->right = root->right;
        p_node->left = root;
        root->right = nullptr;
        root = p_node;
    } else
        return root;
    p_node = nullptr;
    return root;
}

splay* Delete(int val, splay* root) {
    splay* temp;
    if (!root) {
        return nullptr;
    }
    root = Splay(val, root);
    if (val != root->val)
        return root;
    else {
        if (!root->left) {
            temp = root;
            root = root->right;
        } else {
            temp = root;

            root = Splay(val, root->left);
            root->right = temp->right;
        }
        delete temp;
        return root;
    }
}

splay* Search(int val, splay* root) {
    return Splay(val, root);
}

int size_splay(splay *x) {
    if (x == nullptr) {
        return 0;
    }
    if (x->left == nullptr && x->right == nullptr) {
        return 1;
    }
    int resl = 0;
    if (x->left != nullptr) {
        resl = size_splay(x->left);
    }
    int resr = 0;
    if (x->right != nullptr) {
        resr = size_splay(x->right);
    }
    return 1 + resl + resr;
}

int height_splay(splay *x) {
    if (x == nullptr) {
        return 0;
    }
    if (x->left == nullptr && x->right == nullptr) {
        return 1;
    }
    int resl = 0;
    if (x->left != nullptr) {
        resl = height_splay(x->left);
    }
    int resr = 0;
    if (x->right != nullptr) {
        resr = height_splay(x->right);
    }
    return 1 + max(resl, resr);
}
