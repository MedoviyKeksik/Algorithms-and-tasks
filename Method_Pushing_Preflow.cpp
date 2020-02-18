#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif // LOCAL
    int n, m;
    cin >> n >> m;
    vector<vector<int>> c(n, vector<int> (n));
    int a, b, cap;
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> cap;
        a--; b--;
        c[a][b] = cap;
    }
    vector<vector<int>> f(n, vector<int> (n));
    for (int i = 1; i < n; i++) {
        f[0][i] = c[0][i];
        f[i][0] = -c[0][i];
    }

    vector<int> h(n);
    h[0] = n;

    vector<int> e(n);
    for (int i = 1; i < n; i++) {
        e[i] = c[0][i];
        e[0] -= c[0][i];
    }

    while (true) {
        int i;
        for (i = 1; i < n - 1; i++) {
            if (e[i] > 0) break;
        }

        if (i == n - 1) break;

        int j;
        for (j = 0; j < n; j++) {
            if (c[i][j] - f[i][j] > 0 && h[i] == h[j] + 1)
                break;
        }
        if (j < n) {
            int d = min(e[i], c[i][j] - f[i][j]);
            f[i][j] += d;
            f[j][i] = -f[i][j];
            e[i] -= d;
            e[j] += d;
        } else {
            int d = INT_MAX;
            for (j = 0; j < n; j++)
                if (c[i][j] - f[i][j] > 0)
                    d = min(d, h[j]);
            if (d != INT_MAX) h[i] = d + 1;
        }
    }
    int flow = 0;
    for (int i = 0; i < n; i++) {
        if (c[0][i]) flow += f[0][i];
    }
    cout << max(flow, 0);
    return 0;
}
