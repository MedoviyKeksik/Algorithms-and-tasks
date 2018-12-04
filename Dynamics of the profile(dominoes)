#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10;
int n;
int d[1030][1030], a[MAXN + 3][1030];

bool bit(int x, int i) {
	return (x >> i) & 1;
}

void make(int p, int profile, int len) {
	if (len == n) {
		d[p][profile] = 1;
		return;
	}
	if (bit(p, len) == 0) {
		make(p, profile + (1 << len), len + 1);
		if (len < n - 1) {
			if (bit(p, len + 1) == 0) {
				make(p, profile, len + 2);
			}
		}
	} else {
        make(p, profile, len + 1);
    }
}

void determine_d() {
	for (int i = 0; i < (1 << n); i++) {
		make(i, 0, 0);
	}
}

int main() {
    int m;
	cin >> n >> m;
	determine_d();
	/*
	for (int i = 0; i < (1 << n); i++) {
		for (int j = 0; j < (1 << n); j++) {
			cout << d[i][j] << " ";
		}
		cout << endl;
	}
	*/
	a[1][0] = 1;
	for (int i = 1; i < (1 << n); i++) {
        a[1][i] = 0;
	}
	for (int i = 2; i <= m + 1; i++) {
        for (int p1 = 0; p1 < (1 << n); p1++) {
            for (int p2 = 0; p2 < (1 << n); p2++) {
                a[i][p1] += a[i - 1][p2] * d[p2][p1];
            }
        }
	}
	/*
	for (int i = 1; i <= m + 1; i++) {
        for (int p = 0; p < (1 << n); p++) {
            cout << a[i][p] << " ";
        }
        cout << endl;
	}
	*/
	cout << a[m + 1][0];
	return 0;
}
