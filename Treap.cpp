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

struct Treap{
    int k, y;
    int cnt;
    Treap* l;
    Treap* r;

    Treap() {}
    Treap(int _k) {
        k = _k;
        y = rnd();
        cnt = 0;
        l = NULL;
        r = NULL;
    }
};

int get_cnt(Treap* t) {
    if (t == NULL) {
        return 0;
    } else {
        return t->cnt;
    }
}

void update(Treap* t) {
    if (t)
        t->cnt = 1 + get_cnt(t->l) + get_cnt(t->r);
}

void split(Treap* v, Treap* &l, Treap* &r, int k) {
    if (v == NULL) {
        l = r = NULL;
        return;
    }
    if (k > v->k) {
        l = v;
        split(v->r, l->r, r, k);
    } else {
        r = v;
        split(v->l, l, r->l, k);
    }
    update(l);
    update(r);
}

void merge(Treap* &v, Treap* l, Treap* r) {
    if (l == NULL) {
        v = r;
        update(v);
        return;
    } else if (r == NULL) {
        v = l;
        update(v);
        return;
    }
    if (l->y > r->y) {
        v = l;
        merge(v->r, l->r, r);
    } else {
        v = r;
        merge(v->l, l, r->l);
    }
    update(l);
    update(r);
}

void insert(Treap* &v, Treap* t) {
    Treap* t1;
    Treap* t2;
    split(v, t1, t2, t->k);
    merge(t1, t1, t);
    merge(v, t1, t2);
}

int find_kth(Treap* v, int k) {
    int l = get_cnt(v->l);
    if (l == k) {
        return v->k;
    }
    if (l >= k) {
        return find_kth(v->l, k);
    } else {
        return find_kth(v->r, k - l - 1);
    }
}

void erase(Treap* &v, int k) {
    Treap* t1;
    Treap* t2;
    Treap* t3;
    split(v, t1, t3, k + 1);
    split(t1, t1, t2, k);
    merge(v, t1, t3);
}

int main() {
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    Treap* root = NULL;
    while (n--) {
        int c, k;
        cin >> c >> k;
        if (c == 1) {
            insert(root, new Treap(k));
        } else if (c == 0) {
            int ans = find_kth(root, get_cnt(root) - k);
            cout << ans << "\n";
        } else if (c == -1) {
            erase(root, k);
        }
    }
}
