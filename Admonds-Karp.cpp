#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif // LOCAL
    int n, k;
    cin >> n >> k;
    int u, v, temp;
    vector<vector<int>> c(MAXN, vector<int> (MAXN));
    vector<vector<int>> f(MAXN, vector<int> (MAXN));
    for (int i = 0; i < k; i++) {
        cin >> u >> v >> temp;
        u--; v--;
        c[u][v] = temp;
        c[v][u] = temp;
    }

    while (true) {
        vector<int> q(n), from(n, -1);
        int q_sz = 0, id = 0;
        q[q_sz++] = 0;
        while (q_sz > id) {
            int now = q[id++];
            for (int to = 0; to < n; to++) {
                if (from[to] == -1 && c[now][to] - f[now][to] > 0) {
                    q[q_sz++] = to;
                    from[to] = now;
                }
            }
        }

        if (from[n - 1] == -1) {
            break;
        }

        int mn = INT_MAX;
        int now = n - 1;
        while (now != 0) {
            int prev = from[now];
            mn = min(mn, c[prev][now] - f[prev][now]);
            now = prev;
        }

        now = n - 1;
        while (now != 0) {
            int prev = from[now];
            f[prev][now] += mn;
            f[now][prev] -= mn;
            now = prev;
        }
    }

    int flow = 0;
    for (int i = 0; i < n; i++) {
        if (c[0][i]) {
            flow += f[0][i];
        }
    }
    cout << flow;
    return 0;
}

