// 用法：
// LCA tr(3);  // 节点 1base，必须是一棵连通树。
// tr.addedge(1, 2);
// tr.addedge(1, 3);
// tr.build(1);  // 加完所有边后预处理，根为 1。
// int p = tr.lca(2, 3);  // 最近公共祖先为 1。
#include <bits/stdc++.h>
using namespace std;

struct LCA {
    int n, lg, root;
    vector<vector<int>> ve, f;
    vector<int> dep;
    explicit LCA(int n)
        : n(n),
          lg(n ? __lg(n) + 1 : 1),
          root(1),
          ve(n + 1),
          f(lg, vector<int>(n + 1)),
          dep(n + 1) {}
    LCA(const vector<vector<int>>& graph, int root = 1)
        : LCA((int)graph.size() - 1) {
        ve = graph;
        build(root);
    }
    void addedge(int u, int v) {
        ve[u].push_back(v);
        ve[v].push_back(u);
    }
    void build(int r = 1) {
        root = r;
        fill(dep.begin(), dep.end(), 0);
        for (auto& row : f) fill(row.begin(), row.end(), 0);
        if (!n) return;
        vector<int> order{root};
        dep[root] = 1;
        for (int i = 0; i < (int)order.size(); i++) {
            int u = order[i];
            for (int j = 1; j < lg; j++) f[j][u] = f[j - 1][f[j - 1][u]];
            for (int v : ve[u])
                if (v != f[0][u])
                    f[0][v] = u, dep[v] = dep[u] + 1, order.push_back(v);
        }
    }
    int lca(int x, int y) const {
        if (dep[x] < dep[y]) swap(x, y);
        int d = dep[x] - dep[y];
        for (int i = 0; i < lg; i++)
            if (d >> i & 1) x = f[i][x];
        if (x == y) return x;
        for (int i = lg - 1; i >= 0; i--)
            if (f[i][x] != f[i][y]) x = f[i][x], y = f[i][y];
        return f[0][x];
    }
};
