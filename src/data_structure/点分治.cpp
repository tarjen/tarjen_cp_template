// 1base连通带权树；CentroidDecomposition cd(n); addedge(); build(callback);
// 回调接收重心及各分支的{点,距离}。
#include <bits/stdc++.h>
using namespace std;

struct CentroidDecomposition {
    int n;
    vector<vector<pair<int, long long>>> ve;
    vector<int> siz, parent, centroid_parent;
    vector<char> vis;
    explicit CentroidDecomposition(int n)
        : n(n),
          ve(n + 1),
          siz(n + 1),
          parent(n + 1),
          centroid_parent(n + 1),
          vis(n + 1) {}
    void add_edge(int u, int v, long long w) { ve[u].push_back({v, w}); }
    void addedge(int u, int v, long long w) {
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    template <class Callback>
    void build(Callback process) {
        fill(vis.begin(), vis.end(), 0);
        fill(centroid_parent.begin(), centroid_parent.end(), 0);
        if (!n) return;
        vector<pair<int, int>> pending{{1, 0}};
        while (!pending.empty()) {
            auto [start, cp] = pending.back();
            pending.pop_back();
            vector<int> order{start};
            parent[start] = 0;
            for (int i = 0; i < (int)order.size(); i++) {
                int u = order[i];
                for (auto [v, w] : ve[u])
                    if (!vis[v] && v != parent[u])
                        parent[v] = u, order.push_back(v);
            }
            int total = order.size(), centroid = start, best = total;
            for (int i = total - 1; i >= 0; i--) {
                int u = order[i], maximum = 0;
                siz[u] = 1;
                for (auto [v, w] : ve[u])
                    if (!vis[v] && parent[v] == u)
                        siz[u] += siz[v], maximum = max(maximum, siz[v]);
                maximum = max(maximum, total - siz[u]);
                if (maximum < best) best = maximum, centroid = u;
            }
            vector<vector<pair<int, long long>>> branches;
            for (auto [v, w] : ve[centroid])
                if (!vis[v]) {
                    vector<pair<int, long long>> branch;
                    vector<tuple<int, int, long long>> stack{{v, centroid, w}};
                    while (!stack.empty()) {
                        auto [u, p, d] = stack.back();
                        stack.pop_back();
                        branch.push_back({u, d});
                        for (auto [to, len] : ve[u])
                            if (!vis[to] && to != p)
                                stack.push_back({to, u, d + len});
                    }
                    branches.push_back(move(branch));
                }
            centroid_parent[centroid] = cp;
            process(centroid, branches);
            vis[centroid] = true;
            for (auto [v, w] : ve[centroid])
                if (!vis[v]) pending.push_back({v, centroid});
        }
    }
    void build() {
        build([](int, const auto&) {});
    }
};
