// 用法：
// XS tr(3);  // 节点 1base，根默认 1，原图必须是连通带权树。
// tr.add(1, 2, 3);
// tr.add(1, 3, 4);
// tr.build();
// auto nodes = tr.build_virtual({2, 3});  // 返回虚树节点，包含所需 LCA 和根。
// ll distance = tr.getlen(2, 3);  // 原树距离为 7。
// ve2 是虚树邻接表，边的 len 为原树路径长度；b[u] 标记关键点。
// 每次 build_virtual 自动清理上一棵虚树。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
struct XS {
    struct Edge {
        int to;
        ll len;
    };
    int n, root, lg;
    vector<vector<Edge>> ve, ve2;
    vector<vector<int>> f;
    vector<int> dep, id, vis, v1;
    vector<ll> dist, sum;
    vector<char> b;
    XS(int n, int root = 1)
        : n(n),
          root(root),
          lg(n ? __lg(n) + 1 : 1),
          ve(n + 1),
          ve2(n + 1),
          f(lg, vector<int>(n + 1)),
          dep(n + 1),
          id(n + 1),
          dist(n + 1),
          sum(n + 1),
          b(n + 1) {}
    void add(int u, int v, ll w) {
        ve[u].push_back({v, w});
        ve[v].push_back({u, w});
    }
    void build() {
        fill(dep.begin(), dep.end(), 0);
        fill(dist.begin(), dist.end(), 0);
        for (auto& row : f) fill(row.begin(), row.end(), 0);
        if (!n) return;
        vector<int> stack{root};
        dep[root] = 1;
        int timer = 0;
        while (!stack.empty()) {
            int u = stack.back();
            stack.pop_back();
            id[u] = ++timer;
            for (int k = 1; k < lg; k++) f[k][u] = f[k - 1][f[k - 1][u]];
            for (auto e : ve[u])
                if (e.to != f[0][u]) {
                    f[0][e.to] = u;
                    dep[e.to] = dep[u] + 1;
                    dist[e.to] = dist[u] + e.len;
                    stack.push_back(e.to);
                }
        }
    }
    int lca(int u, int v) const {
        if (dep[u] < dep[v]) swap(u, v);
        int d = dep[u] - dep[v];
        for (int k = 0; k < lg; k++)
            if (d >> k & 1) u = f[k][u];
        if (u == v) return u;
        for (int k = lg - 1; k >= 0; k--)
            if (f[k][u] != f[k][v]) u = f[k][u], v = f[k][v];
        return f[0][u];
    }
    ll getlen(int u, int v) const {
        int p = lca(u, v);
        return dist[u] + dist[v] - 2 * dist[p];
    }
    void init() {
        for (int u : vis) ve2[u].clear(), b[u] = false, sum[u] = 0;
        vis.clear();
        v1.clear();
    }
    const vector<int>& build_virtual(vector<int> keys) {
        init();
        if (!n) return vis;
        for (int u : keys) b[u] = true;
        keys.push_back(root);
        auto cmp = [&](int u, int v) { return id[u] < id[v]; };
        sort(keys.begin(), keys.end(), cmp);
        keys.erase(unique(keys.begin(), keys.end()), keys.end());
        int count = keys.size();
        for (int i = 1; i < count; i++)
            keys.push_back(lca(keys[i - 1], keys[i]));
        sort(keys.begin(), keys.end(), cmp);
        keys.erase(unique(keys.begin(), keys.end()), keys.end());
        vis = keys;
        vector<int> stack;
        for (int u : keys) {
            while (!stack.empty() && lca(stack.back(), u) != stack.back())
                stack.pop_back();
            if (!stack.empty()) {
                int p = stack.back();
                ll w = dist[u] - dist[p];
                ve2[p].push_back({u, w});
                ve2[u].push_back({p, w});
            }
            stack.push_back(u);
        }
        return vis;
    }
    void addintoxs(int u) { v1.push_back(u); }
    void makexs() {
        auto keys = v1;
        build_virtual(move(keys));
    }
};
