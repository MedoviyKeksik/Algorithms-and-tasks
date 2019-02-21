#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <map>

using namespace std;

struct Treap {
    int k, cnt, p;
    Treap *left, *right;
};

pair<Treap*, Treap*> split(Treap *t, int k) {
    if (t == nullptr)
        return make_pair(nullptr, nullptr);
    int l = t->left->cnt;
    if (l >= k) {
        pair<Treap*, Treap*> tmp = split(t->left, k);
        t->left = tmp.second;
        return make_pair(tmp.first, t);
    } else {
        pair<Treap*, Treap*> tmp = split(t->right, k);
        t->right = tmp.first;
        return make_pair(t, tmp.second);
    }
}

Treap* merge(Treap* tl, Treap* tr) {
    if (tl == nullptr) return tr;
    if (tr == nullptr) return tl;
    if (tl->p > tr->p) {
        tl->right = merge(tl->right, tr);
        return tl;
    } else {
        tr->left = merge(tl, tr->left);
        return tr;
    }
}

int main() {

    return 0;
}
