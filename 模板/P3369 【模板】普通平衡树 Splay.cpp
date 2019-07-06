#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int INF = 0x7f7f7f7f;
enum Relation {
    L, R
};

class SplayNode {
public:
    int value, count, size;
    SplayNode *parent;
    SplayNode *children[2];

    SplayNode() : value(0), count(1), size(1), parent(nullptr) {
        children[0] = nullptr;
        children[1] = nullptr;
    }

    SplayNode(SplayNode *p, int v) : value(v), count(1), size(1), parent(p) {
        children[0] = nullptr;
        children[1] = nullptr;
    };
};

SplayNode *getGrandparent(SplayNode *node) {
    SplayNode *parent = node->parent;
    if (parent) {
        return parent->parent;
    } else {
        return nullptr;
    }
}

Relation getRelation(SplayNode *node) {
    if (node && node->parent) {
        return node->parent->children[L] == node ? L : R;
    } else {
        return L;
    }
}

Relation reverseRelation(Relation r) {
    return r == L ? R : L;
}

void setSon(SplayNode *parent, SplayNode *son, Relation relation) {
    if (parent) {
        parent->children[relation] = son;
    }
    if (son) {
        son->parent = parent;
    }
}

void maintain(SplayNode *node) {
    if (node) {
        int leftSize = node->children[L] ? node->children[L]->size : 0;
        int rightSize = node->children[R] ? node->children[R]->size : 0;

        node->size = leftSize + rightSize + node->count;
    }
}

void rotate(SplayNode *node) {
    if (!node) {
        return;
    }

    SplayNode *parent = node->parent;
    SplayNode *grandParent = getGrandparent(node);
    SplayNode *children = node->children[reverseRelation(getRelation(node))];

    Relation r = getRelation(node);
    setSon(parent, children, r);
    setSon(grandParent, node, getRelation(parent));
    setSon(node, parent, reverseRelation(r));

    maintain(parent);
    maintain(node);
}

SplayNode *root;

void splay(SplayNode *curr, SplayNode *target = nullptr) {
    if (!curr) {
        return;
    }

    while (curr && curr->parent != target) {
        SplayNode *parent = curr->parent;
        SplayNode *grandParent = getGrandparent(curr);
        if (grandParent != target) {
            if (getRelation(curr) == getRelation(parent)) {
                rotate(parent);
            } else {
                rotate(curr);
            }
        }
        rotate(curr);
    }

    if (!target) {
        root = curr;
    }
}

SplayNode *find(SplayNode *node, int val) {
    if (!node) {
        return nullptr;
    }
    SplayNode *curr = root;
    while (curr && curr->children[val < curr->value ? L : R] && curr->value != val) {
        curr = curr->children[val < curr->value ? L : R];
    }
    splay(curr);
    return curr;
}

void insert(SplayNode *node, int val) {
    SplayNode *previous = nullptr;
    while (node && node->value != val) {
        previous = node;
        node = node->children[val < node->value ? L : R];
    }

    if (node) {
        node->count++;
        maintain(node);
    } else {
        Relation relation = val < previous->value ? L : R;
        previous->children[relation] = new SplayNode(previous, val);
        node = previous->children[relation];
    }
    splay(node);
}

SplayNode *successor(SplayNode *node, int K) {
    SplayNode *previous = nullptr;
    while (node) {
        if (node->value > K) {
            previous = node;
            node = node->children[L];
        } else {
            node = node->children[R];
        }
    }
    return previous;
}

SplayNode *predecessor(SplayNode *node, int K) {
    SplayNode *previous = nullptr;
    while (node) {
        if (node->value < K) {
            previous = node;
            node = node->children[R];
        } else {
            node = node->children[L];
        }
    }
    return previous;
}

int getRank(SplayNode *node) {
    if (!node) {
        return 0;
    } else {
        return node->children[L] ? node->children[L]->size : 0;
    }
}

int getRank(int val) {
    SplayNode *node = find(root, val);
    if (node) {
        return getRank(node);
    } else {
        return 0;
    }
}

void deleteNode(SplayNode *node) {
    if (!node) {
        return;
    }
    SplayNode *pre = predecessor(root, node->value);
    SplayNode *suc = successor(root, node->value);

    splay(pre);
    splay(suc, pre);

    if (node->count > 1) {
        node->size--;
        node->count--;
    } else {
        delete suc->children[L];
        suc->children[L] = nullptr;
    }

    suc->size--;
    pre->size--;
}

void deleteNode(int val) {
    SplayNode *node = find(root, val);
    if (node) {
        deleteNode(node);
    }
}

SplayNode *select(SplayNode *node, int k) {
    SplayNode *curr = node;

    while (!(k >= getRank(curr) && k < getRank(curr) + curr->count)) {
        if (k < getRank(curr)) {
            curr = curr->children[L];
        } else {
            k -= getRank(curr) + curr->count;
            curr = curr->children[R];
        }
    }

    splay(curr);
    return curr;
}

int main() {
    root = new SplayNode(nullptr, INF);
    root->children[L] = new SplayNode(root, -INF);
    int Q = 0;
    cin >> Q;

    for (int _ = 1; _ <= Q; _++) {
        int opt = 0, K = 0;
        cin >> opt >> K;
        switch (opt) {
            case 1:
                insert(root, K);
                break;
            case 2:
                deleteNode(K);
                break;
            case 3:
                cout << getRank(K) << endl;
                break;
            case 4:
                cout << select(root, K)->value << endl;
                break;
            case 5:
                cout << predecessor(root, K)->value << endl;
                break;
            case 6:
                cout << successor(root, K)->value << endl;
                break;
        }
    }
    return 0;
}

