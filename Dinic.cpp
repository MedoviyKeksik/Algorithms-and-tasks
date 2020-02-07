#include <bits/stdc++.h>

// from vertex 1 to vertex n

using namespace std;

const int MAXN = 500;
const int INF = INT_MAX;

struct edge {
    int a, b, cap, flow;
};

vector<edge> e;
vector<int> g[MAXN];
int n, d[MAXN], q[MAXN], ptr[MAXN];


void add_edge(int a, int b, int cap) {
    edge e1 = {a, b, cap, 0};
    edge e2 = {b, a, 0, 0};
    g[a].push_back((int) e.size());
    e.push_back(e1);
    g[b].push_back((int) e.size());
    e.push_back(e2);
}

bool bfs() {
    int qh = 0, qt = 0;
    q[qt++] = 0;
    memset(d, -1, n * sizeof d[0]);
    d[0] = 0;
    while (qh < qt && d[n - 1] == -1) {
        int v = q[qh++];
        for (int id : g[v]) {
            int to = e[id].b;
            if (d[to] == -1 && e[id].flow < e[id].cap) {
                q[qt++] = to;
                d[to] = d[v] + 1;
            }
        }
    }
    return d[n - 1] != -1;
}

int dfs(int v, int flow) {
    if (flow == 0) return 0;
    if (v == n - 1) return flow;
    while (ptr[v] < (int) g[v].size()) {
        int id = g[v][ptr[v]], to = e[id].b;
        if (d[to] != d[v] + 1) {
            ptr[v]++;
            continue;
        }
        int pushed = dfs(to, min(flow, e[id].cap - e[id].flow));
        if (pushed) {
            e[id].flow += pushed;
            e[id ^ 1].flow -= pushed;
            return pushed;
        }
        ptr[v]++;
    }
    return 0;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif // LOCAL
    int k;
    cin >> n >> k;
    int a, b, c;
    for (int i = 0; i < k; i++) {
        cin >> a >> b >> c;
        a--; b--;
        add_edge(a, b, c);
//        add_edge(b, a, c);
    }
    long long flow = 0;
    int pushed;
    while (bfs()) {
        memset(ptr, 0, n * sizeof ptr[0]);
        while (pushed = dfs(0, INF)) {
            flow += pushed;
        }
    }
    cout << flow;
    return 0;
}

