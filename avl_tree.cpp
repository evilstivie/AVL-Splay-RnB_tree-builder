#include "backend.h"
using namespace std;

int64_t get_height_avl(node_avl *v) {
    return v == nullptr ? 0 : v->h;
}

int64_t get_size_avl(node_avl *v) {
    return v == nullptr ? 0 : v->size;
}

int64_t bal_fac_avl(node_avl *v) {
    return v == nullptr ? 0 : get_height_avl(v->left) - get_height_avl(v->right);
}

void relax_avl(node_avl *v) {
    if (v != nullptr) {
        v->h = max(get_height_avl(v->left), get_height_avl(v->right)) + 1;
        v->size = get_size_avl(v->left) + get_size_avl(v->right) + 1;
    }
}

node_avl *rotate_right_avl(node_avl *v) {
    node_avl *q = v->left;
    v->left = q->right;
    q->right = v;

    relax_avl(v); // SEQ
    relax_avl(q);

    return q;
}

node_avl *rotate_left_avl(node_avl *v) {
    node_avl *q = v->right;
    v->right = q->left;
    q->left = v;

    relax_avl(v); // SEQ
    relax_avl(q);

    return q;
}

node_avl *large_rotate_right_avl(node_avl *v) {
    node_avl *q = v->left;
    node_avl *r = q->right;

    v->left = r->right;
    q->right = r->left;
    r->left = q;
    r->right = v;

    relax_avl(v); // SEQ
    relax_avl(q);
    relax_avl(r);

    return r;
}


node_avl *large_rotate_left_avl(node_avl *v) {
    node_avl *q = v->right;
    node_avl *r = q->left;

    v->right = r->left;
    q->left = r->right;
    r->left = v;
    r->right = q;

    relax_avl(v); // SEQ
    relax_avl(q);
    relax_avl(r);

    return r;
}


node_avl *balance_avl(node_avl *v) {
    relax_avl(v);

    if (bal_fac_avl(v) == -2) {
        if (bal_fac_avl(v -> right) > 0) {
            return large_rotate_left_avl(v);
        } else {
            return rotate_left_avl(v);
        }
    } else if (bal_fac_avl(v) == 2) {
        if (bal_fac_avl(v -> left) < 0) {
            return large_rotate_right_avl(v);
        } else {
            return rotate_right_avl(v);
        }
    }
    return v;
}

node_avl *insert_avl(node_avl *v, int64_t key) {
    if (v == nullptr) {
        return new node_avl(key);
    }
    if (v->val == key) {
        return v;
    }
    if (key < v->val){
        v->left = insert_avl(v->left, key);
    } else {
        v->right = insert_avl(v->right, key);
    }
    return balance_avl(v);
}

pair<int64_t, node_avl*> find_min_avl(node_avl *v) {
    if (v->left == nullptr) {
        return {v->val, v->right};
    }

    auto st = find_min_avl(v->left);
    v->left = st.second;
    return {st.first, v};
}

pair<int64_t, node_avl*> find_max_avl(node_avl *v) {
    if (v->right == nullptr) {
        return {v->val, v->left};
    }

    auto st = find_max_avl(v->right);
    v->right = st.second;
    return {st.first, v};
}

node_avl *erase_avl(node_avl *v, int64_t key) {
    if (v == nullptr) {
        return nullptr;
    }

    if (key < v->val) {
        v->left = erase_avl(v->left, key);
    } else if (key > v->val) {
        v->right = erase_avl(v->right, key);
    } else {
        pair<int64_t, node_avl*> st;
        if (v->right != nullptr) {
            st = find_min_avl(v->right);
            v->right = st.second;
        } else if (v->left != nullptr) {
            st = find_max_avl(v->left);
            v->left = st.second;
        } else {
            return nullptr;
        }

        v->val = st.first;
    }
    return balance_avl(v);
}

backend::backend()
{

}
