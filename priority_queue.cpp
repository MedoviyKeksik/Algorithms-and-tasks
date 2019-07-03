#include <bits/stdc++.h>

using namespace std;

struct binary_heap {
    static const int MAXN = 1e5 + 17;
    int a[MAXN], sz = 0;

    void push(int x) {
        sz++;
        int i = sz - 1;
        while (i > 0 && x < a[(i - 1) / 2]) {
            a[i] = a[(i - 1) / 2];
            i = (i - 1) / 2;
        }
        a[i] = x;
    }

    int pop() {
        int x = a[0];
        sz--;
        int i = 0;
        while ((i * 2 + 1 < sz && a[sz] > a[i * 2 + 1]) || (i * 2 + 2 < sz && a[sz] > a[i * 2 + 2])) {
            if (i * 2 + 2 < sz && a[i * 2 + 2] < a[i * 2 + 1]) {
                a[i] = a[i * 2 + 2];
                i = i * 2 + 2;
            } else {
                a[i] = a[i * 2 + 1];
                i = i * 2 + 1;
            }
        }
        a[i] = a[sz];
        return x;
    }
};

int main() {
    binary_heap k;
    int n, tmp;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> tmp;
        k.push(tmp);
    }
    for (int i = 0; i < n; i++) {
        tmp = k.pop();
        cout << tmp << " ";
    }
    return 0;
}
