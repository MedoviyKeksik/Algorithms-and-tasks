#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100;

int cap[MAXN][MAXN], flow[MAXN][MAXN], cost[MAXN][MAXN];
vector<int> from;
vector<int> dist;
int n, m;

bool bfs(int s, int t) {
    queue<int> q;
    q.push(s);
    from.assign(n, -1);
    while (from[t] == -1 && !q.empty()) {
        int now = q.front();
        q.pop();
        for (int to = 0; to < n; to++) {
            if (from[to] == -1 && cap[now][to] - flow[now][to] > 0) {
                from[to] = now;
                q.push(to);
            }
        }
    }
    return from[t] != -1;
}

int check_cycles() {
    for (int now = 0; now < n; now++) {
        for (int to = 0; to < n; to++) {
            if (cap[now][to] - flow[now][to] > 0 && dist[to] > dist[now] + cost[now][to]) {
                return now;
            }
        }
    }
    return -1;
}

int bf(int s) {
    dist.assign(n, 1000000000);
    queue<int> q;
    from.assign(n, -1);
    q.push(s);
    q.push(-1);
    int series = 0;
    while (!q.empty()) {
        while (q.front() == -1) {
            q.pop();
            if (++series > n) return check_cycles();
            else q.push(-1);
        }
        int now = q.front();
        q.pop();
        for (int to = 0; to < n; to++) {
            if (cap[now][to] - flow[now][to] > 0 && dist[to] > dist[now] + cost[now][to]) {
                dist[to] = dist[now] + cost[now][to];
                from[to] = now;
                q.push(to);
            }
        }
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif // LOCAL
    cin >> n >> m;
    int u, v, c, p;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> c >> p;
        u--; v--;
        cap[u][v] = c;
        cost[u][v] = p;
        cost[v][u] = -p;
    }
    while (bfs(0, n - 1)) {
        int mn = INT_MAX;
        int now = n - 1;
        while (now != 0) {
            int pred = from[now];
            mn = min(mn, cap[pred][now] - flow[pred][now]);
            now = pred;
        }
        now = n - 1;
        while (now != 0) {
            int pred = from[now];
            flow[pred][now] += mn;
            flow[now][pred] -= mn;
            now = pred;
        }
    }
    int neg_cycle = bf(n - 1);
    while (neg_cycle != -1) {
        int now = neg_cycle, pred = from[now];
        int mn = INT_MAX;
        do {
            mn = min(mn, cap[pred][now] - flow[pred][now]);
            now = pred; pred = from[now];
        } while (now != neg_cycle);
        now = neg_cycle, pred = from[now];
        do {
            flow[pred][now] += mn;
            flow[now][pred] -= mn;
            now = pred; pred = from[now];
        } while (now != neg_cycle);
        neg_cycle = bf(n - 1);
    }
    long long min_cost = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (cap[i][j] > 0)
                min_cost += flow[i][j] * cost[i][j];
        }
    }
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            cerr << flow[i][j] << ' ';
//        }
//        cerr << '\n';
//    }
//    cerr << '\n';
//
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            cerr << cost[i][j] << ' ';
//        }
//        cerr << '\n';
//    }
    cout << min_cost;
    return 0;
}

