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
    int cnt, pri, k;
    Treap *left, *right;
    Treap(int _k) {
        k = _k;
        cnt = 1; pri = rnd();
        left = NULL; right = NULL;
    }
};

int get_cnt(Treap* t) {
    if (t == NULL) return 0;
    return t->cnt;
}

void update(Treap* t) {
    if (t) t->cnt = 1 + get_cnt(t->left) + get_cnt(t->right);
}

void split(Treap* t, int k, Treap* &l, Treap* &r) {
    if (t == NULL) {
        l = NULL; r = NULL;
        return;
    }
    if (t->k >= k) {
        r = t;
        split(t->left, k, l, r->left);
    } else {
        l = t;
        split(t->right, k, l->right, r);
    }
    update(l);
    update(r);
}

Treap* merge(Treap *tl, Treap *tr) {
    if (tl == NULL) {
        update(tr);
        return tr;
    }
    if (tr == NULL) {
        update(tl);
        return tl;
    }
    if (tl->pri > tr->pri) {
        tl->right = merge(tl->right, tr);
        update(tl); update(tr);
        return tl;
    } else {
        tr->left = merge(tl, tr->left);
        update(tr); update(tl);
        return tr;
    }
}

void insert(Treap* &t, Treap *data) {
    Treap *t1, *t2;
    split(t, data->k, t1, t2);
    t1 = merge(t1, data);
    t = merge(t1, t2);
}

void erase(Treap* &t, int k) {
    Treap *t1, *t2, *t3;
    split(t, k + 1, t1, t3);
    split(t1, k, t1, t2);
    t = merge(t1, t3);
}

int fnd_kth(Treap *t, int k) {
    int l = get_cnt(t->left);
    if (l == k) return t->k;
    if (l > k) {
        return fnd_kth(t->left, k);
    } else {
        return fnd_kth(t->right, k - l - 1);
    }
}

int main() {
    int n, tp;
    scanf("%d", &n);
    Treap *root = NULL;
    while (n--) {
        scanf("%d", &tp);
        switch (tp) {
            case 1: {
                int a;
                scanf("%d", &a);
                insert(root, new Treap(a));
                break;
            }
            case 0: {
                int k;
                scanf("%d", &k);
                printf("%d\n", fnd_kth(root, get_cnt(root) - k));
                break;
            }
            case -1: {
                int a;
                scanf("%d", &a);
                erase(root, a);
                break;
            }
        }
    }
    return 0;
}
