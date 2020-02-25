#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101;

vector<int> g[MAXN];
vector<int> from;
vector<bool> used;

bool try_kuhn(int v) {
    if (used[v]) return false;
    used[v] = true;
    for (int to : g[v]) {
        if (from[to] == -1 || try_kuhn(from[to])) {
            from[to] = v;
            return true;
        }
    }
    return false;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif // LOCAL
    int n, m, k;
    cin >> n >> m >> k;
    int a, b;
    for (int i = 0; i < k; i++) {
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
    }
    used.resize(n);
    from.assign(m, -1);
    for (int i = 0; i < n; i++) {
        fill(used.begin(), used.end(), 0);
        try_kuhn(i);
    }
    int ans = 0;
    for (int i = 0; i < m; i++) {
        if (from[i] != -1) ans++;
    }
    cout << ans << '\n';
    for (int i = 0; i < m; i++) {
        if (from[i] != -1) {
            cout << from[i] + 1 << ' ' << i + 1 << '\n';
        }
    }
    return 0;
}
