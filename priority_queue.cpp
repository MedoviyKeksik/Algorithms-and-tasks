#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 11;
int k[MAXN], sz_k;

/*
int sift_up(int i) {
    while (i != 0 && a[i] > a[(i - 1) / 2]) {
        swap(a[i], a[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
    return i;
}

int sift_down(int i) {
    while (2 * i + 1 < n) {
        int left = 2 * i + 1, right = 2 * i + 2, j = left;
        if (right < n && a[right] > a[left]) j = right;
        if (a[i] > a[j])
            break;
        swap(a[i], a[j]);
        i = j;
    }
    return i;
}
*/

void in_k(int x) {
    sz_k++;
    int i    = sz_k;
    while (i > 1 && k[i / 2] > x) {
        k[i] = k[i / 2];
        i /= 2;
    }
    k[i] = x;
}

void out_k(int &x) {
    x = k[1];
    sz_k--;
    int i = 1;
    while (i * 2 <= sz_k && k[sz_k + 1] > k[i * 2] || i * 2 + 1 <= sz_k && k[sz_k + 1] > k[i * 2 + 1]) {
        if (i * 2 + 1 <= sz_k && k[i * 2 + 1] < k[i * 2]) {
            k[i] = k[i * 2 + 1];
            i = i * 2 + 1;
        } else {
            k[i] = k[i * 2];
            i = i * 2;
        }
    }
    k[i] = k[sz_k + 1];
}

int main() {
    srand(time(NULL));
    int n, tmp;
    cin >> n;
    for (int i = 0; i < n; i++) {
        tmp = rand() % 10000;
        cout << tmp << ' ';
        in_k(tmp);
    }
    cout << "\n";
    while (sz_k) {
        out_k(tmp);
        cout << tmp << " ";
    }
    return 0;
}
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 11;
int k[MAXN], sz_k;

void in_k(int x) {
    sz_k++;
    int i    = sz_k;
    while (i > 1 && k[i / 2] > x) {
        k[i] = k[i / 2];
        i /= 2;
    }
    k[i] = x;
}

void out_k(int &x) {
    x = k[1];
    sz_k--;
    int i = 1;
    while (i * 2 <= sz_k && k[sz_k + 1] > k[i * 2] || i * 2 + 1 <= sz_k && k[sz_k + 1] > k[i * 2 + 1]) {
        if (i * 2 + 1 <= sz_k && k[i * 2 + 1] < k[i * 2]) {
            k[i] = k[i * 2 + 1];
            i = i * 2 + 1;
        } else {
            k[i] = k[i * 2];
            i = i * 2;
        }
    }
    k[i] = k[sz_k + 1];
}

int main() {
    srand(time(NULL));
    int n, tmp;
    cin >> n;
    for (int i = 0; i < n; i++) {
        tmp = rand() % 10000;
        cout << tmp << ' ';
        in_k(tmp);
    }
    cout << "\n";
    while (sz_k) {
        out_k(tmp);
        cout << tmp << " ";
    }
    return 0;
}
