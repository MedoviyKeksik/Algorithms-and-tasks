#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <map>
#include <climits>
#include <set>

using namespace std;

int rnd() {
    int x = rand() << 16;
    x |= rand() & 0xFFFF;
    return x;
}

struct Treap {
    int cnt, pri;
    Treap *left, *right;
    Treap() {
        cnt = 1; pri = rnd();
        left = nullptr; right = nullptr;
    }
};

int get_cnt(Treap* t) {
    if (t == nullptr) return 0;
    return t->cnt;
}

void update(Treap* t) {
    if (t) t->cnt = 1 + get_cnt(t->left) + get_cnt(t->right);
}

void split(Treap* t, int k, Treap &l, Treap &r) {
    if (t == nullptr) {
        l = nullptr; r = nullptr;
        return;
    }
    int l = t->left->cnt;
    if (l >= k) {
        r = t;
        split(t->left, k, l, r->left)
    } else {
        l = t;
        split(t->right, k, l->right, r);
    }
    update(l);
    update(r);
}

Treap* merge(Treap *tl, Treap *tr) {
    if (tl == nullptr) return tr;
    if (tr == nullptr) return tl;
    if (tl->pri > tr->pri) {
        tl->right = merge(tl->right, tr);
        update(tl); update(tr);
        return tl;
    } else {
        tr->left = merge(tl, tr.left);
        update(tr); update(tl);
        return tr;
    }
}

void insert(Treap *t, Treap *data) {
    Treap *t1, *t2;
    split(t, data->cnt, t1, t2);
    t1 = merge(t1, data);
    t = merge(t1, t2);
}

void erase(Treap *t, int k) {
    Treap *t1, *t2, *t3;
    split(t, k + 1, t1, t3);
    split(t1, k, t1, t2);
    t = merge(t1, t3);
}



int main() {

    return 0;
}
