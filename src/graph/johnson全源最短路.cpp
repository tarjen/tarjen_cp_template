// 用法：
// 先提供 using ll=long long; const ll inf=1LL<<60; 以及标准库头文件。
// graph tr(3);  // 有向带权图，节点 0base。
// tr.adde(0, 1, -2);
// tr.adde(1, 2, 5);
// if (tr.init()) {
//     vector<ll> d = tr.query(0);  // d[2]=3；init 返回 false 表示有负环。
// }
// query 对不可达项也加上势差，判不可达时用足够大的阈值，而非 d==inf。
struct graph {
    vector<vector<pair<int, ll>>> e;
    graph(int n) : e(n) {}
    void adde(int u, int v, ll w) { e[u].push_back({v, w}); }
    vector<ll> h;
    // initialize h(u), return false if there exists a negative cycle
    bool init() {
        int n = e.size();
        h.assign(n, 0);
        queue<int> que;
        for (int u = 0; u < n; u++) que.push(u);
        vector<int> vis(n, 0), cnt(n, n + 1);
        while (que.size()) {
            auto u = que.front();
            que.pop();
            vis[u] = false;
            if (!cnt[u]--) return false;  // exists a negative cycle
            for (auto& [v, w] : e[u])
                if (h[v] > h[u] + w) {
                    h[v] = h[u] + w;
                    if (!vis[v]) que.push(v), vis[v] = 1;
                }
        }
        return true;
    }
    // single source shortest path from given sink based on h(u)
    vector<ll> query(int s) {
        int n = e.size();
        vector<ll> dis(n, inf);
        priority_queue<pair<ll, int>, vector<pair<ll, int>>,
                       greater<pair<ll, int>>>
            que;
        que.push({dis[s] = 0, s});
        while (que.size()) {
            auto [du, u] = que.top();
            que.pop();
            if (dis[u] < du) continue;
            for (auto [v, w] : e[u]) {
                auto dv = du + w + h[u] - h[v];
                if (dis[v] > dv) que.push({dis[v] = dv, v});
            }
        }
        for (int i = 0; i < n; i++) dis[i] += h[i] - h[s];
        return dis;
    }
};
