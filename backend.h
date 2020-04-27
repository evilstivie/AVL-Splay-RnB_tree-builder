#ifndef BACKEND_H
#define BACKEND_H

#include <iostream>
#include <numeric>
#include <string>
#include <tuple>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

typedef enum { BLACK, RED } nodeColor;

struct node_avl {
    int64_t val, h, size;
    node_avl *left, *right;
    node_avl (int64_t x) {
        val = x;
        h = size = 1;
        left = right = nullptr;
    }
};

typedef struct Node_ {
    struct Node_ *left;
    struct Node_ *right;
    struct Node_ *parent;
    nodeColor color;
    int64_t val;
} Node;

struct splay {
    int64_t val;
    splay *left;
    splay *right;
};


/* AVL-Tree */

int64_t get_height_avl(node_avl *v);
int64_t get_size_avl(node_avl *v);
int64_t bal_fac_avl(node_avl *v);

void relax_avl(node_avl *v);

node_avl *rotate_right_avl(node_avl *v);
node_avl *rotate_left_avl(node_avl *v);
node_avl *large_rotate_right_avl(node_avl *v);
node_avl *large_rotate_left_avl(node_avl *v);

node_avl *balance_avl(node_avl *v);
node_avl *erase_avl(node_avl *v, int64_t key);
node_avl *insert_avl(node_avl *v, int64_t key);

pair<int64_t, node_avl*> find_min_avl(node_avl *v);
pair<int64_t, node_avl*> find_max_avl(node_avl *v);


/* RedBlack-Tree */

Node *rotateLeft(Node *root, Node *x);
Node *rotateRight(Node *root, Node *x);

Node *insertFixup(Node *root, Node *x);
Node *insertNode(Node *root, int64_t data);

Node *deleteFixup(Node *root, Node *x);
Node *deleteNode(Node *root, Node *z);

Node *findNode(Node *root, int64_t data);
int size_rb(Node *x);
int height_rb(Node *x);


/* Splay-Tree */

splay* RR_Rotate(splay* k2);
splay* LL_Rotate(splay* k2);

splay* Splay(int key, splay* root);
splay* New_Node(int key);

splay* Insert(int key, splay* root);
splay* Delete(int key, splay* root);
splay* Search(int key, splay* root);

int size_splay(splay *x);
int height_splay(splay *x);

class backend
{
public:
    backend();
};

#endif // BACKEND_H
