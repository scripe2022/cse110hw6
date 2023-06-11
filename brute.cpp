// compile: make brute
// run: ./brute < data.in
#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#ifdef LOCAL
#include <debug/codeforces.h>
#define debug(x...) _debug_print(#x, x);
#else
#define debug(x...) {};
#endif
template<typename...Args> void print_(Args...args){((cout<<args<<" "),...)<<endl;}
#define rep(i,a,b) for(int i=(a);i<(int)(b);++i)
#define sz(v) ((int)(v).size())
#define print(...) print_(__VA_ARGS__);
#define INTMAX (int)(9223372036854775807)
#define INF (int)(1152921504606846976)
#define double long double
#define int long long
#define MAXN 200010

struct graph {
    struct node {
        int u, v, w;
        bool operator<(const node &other) const {
            return w < other.w;
        }
        bool operator==(const node &other) const {
            return u == other.u && v == other.v && w == other.w;
        }
    };
    vector<vector<node>> e;
    int n;
    bool directed;
    bool weighted = 0;
    graph(int V, bool D = 0) {
        n = V;
        e.resize(n);
        directed = D;
    }
    void add_edge(int u, int v, int w = 1) {
        e[u].push_back(node{u, v, w});
    }
    void spfa(int s, vector<int> &dis) {
        dis.resize(n, INF);
        vector<bool> inq(n, 0);
        vector<int> cnt(n, 0);
        queue<int> q;
        dis[s] = 0, q.push(s), inq[s] = 1;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            inq[u] = 0;
            for (auto edge: e[u]) {
                int v = edge.v, w = edge.w;
                if (dis[v] > dis[u] + w && dis[v] != -INF) {
                    dis[v] = dis[u] + w;
                    cnt[v] = cnt[u] + 1;
                    if (cnt[v] > n) dis[v] = -INF;
                    if (!inq[v]) q.push(v), inq[v] = 1;
                }
            }
        }
    }
    void dijkstra(int s, vector<int> &dis) {
        dis.resize(n, INF);
        vector<bool> vis(n, 0);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        dis[s] = 0, pq.push({0, s});
        while (!pq.empty()) {
            int u = pq.top().second; pq.pop();
            if (vis[u]) continue;
            vis[u] = 1;
            for (auto edge: e[u]) {
                int v = edge.v, w = edge.w;
                if (dis[v] > dis[u] + w) {
                    dis[v] = dis[u] + w;
                    pq.push({dis[v], v});
                }
            }
        }
    }
    void floyd(vector<vector<int>> &dis) {
        dis.resize(n, vector<int>(n, INF));
        rep(i, 0, n) dis[i][i] = 0;
        rep(u, 0, n) for (auto edge: e[u]) {
            int v = edge.v, w = edge.w;
            dis[u][v] = min(dis[u][v], w);
        }
        rep(k, 0, n) rep(i, 0, n) rep(j, 0, n) {
            if (dis[i][k] == INF || dis[k][j] == INF) continue;
            dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
        }
    }
    void graphviz_dump(string filename = "graph.dot") {
        ofstream gf;
        gf.open(filename);
        gf << (directed ? "digraph" : "graph") << " {\n";
        gf << "    "; rep(i, 0, n) gf << i << " ;"[i==n-1]; gf << endl;
        string notation = directed ? " -> " : " -- ";
        for (auto es: e) for (auto edge: es) if (edge.w != 1) weighted = 1;
        for (auto es: e) {
            for (auto edge: es) {
                if (!directed && edge.u > edge.v) continue;
                gf << "    " << edge.u << notation << edge.v << (weighted ? " [label=\"" + to_string(edge.w) + "\"];\n" : ";\n");
            }
        }
        gf << "}\n";
    }
};
 
int ans = INF;
void dfs(int x, vector<int> &a, int t, int n) {
    if (x > n) return;
    if (x == n) {
        ans = min(ans, t);
        return;
    }
    dfs(x+1, a, t+2, n);
    dfs(x+a[x], a, t+1, n);
}

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int n; cin >> n;
    vector<int> a(n);
    rep(i, 0, n) cin >> a[i];
    graph g(n+1);
    rep(i, 0, n) {
        g.add_edge(i, i+1, 2);
        if (a[i] + i <= n) g.add_edge(i, a[i]+i, 1);
    }
    vector<int> dis;
    g.dijkstra(0, dis);
    // dfs(0, a, 0, n);
    // debug(dis[n]);
    cout << dis[n] << endl;
    // debug(ans);

    return 0;
}