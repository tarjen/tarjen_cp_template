// 用法：
// vector<int> parent = {0, 0, 1, 2};  // 节点 1base，根 1 的父亲为 0。
// KthAncestor tr(parent);  // 传入连通树父亲数组，自动预处理。
// int p = tr.ask(3, 2);  // 向上 2 条边，结果 1；ask(3,0)=3。
// 超出根返回 0；数组第 0 格为哨兵。
#include <bits/stdc++.h>
using namespace std;

struct KthAncestor {
    int n, root = 0, lg;
    vector<vector<int>> ve, f;
    vector<int> dep, h, w, top, id, U, D;
    explicit KthAncestor(const vector<int>& parent)
        : n((int)parent.size() - 1),
          lg(n ? __lg(n) + 1 : 1),
          ve(n + 1),
          f(lg, vector<int>(n + 1)),
          dep(n + 1),
          h(n + 1),
          w(n + 1),
          top(n + 1),
          id(n + 1),
          U(n + 1),
          D(n + 1) {
        f[0] = parent;
        for (int u = 1; u <= n; u++)
            if (parent[u])
                ve[parent[u]].push_back(u);
            else
                root = u;
        if (!n) return;
        vector<int> order{root};
        dep[root] = h[root] = 1;
        for (int i = 0; i < (int)order.size(); i++) {
            int u = order[i];
            for (int k = 1; k < lg; k++) f[k][u] = f[k - 1][f[k - 1][u]];
            for (int v : ve[u]) dep[v] = h[v] = dep[u] + 1, order.push_back(v);
        }
        for (int i = n - 1; i > 0; i--) {
            int u = order[i], p = parent[u];
            h[p] = max(h[p], h[u]);
            if (h[u] > h[w[p]]) w[p] = u;
        }
        vector<pair<int, int>> stack{{root, root}};
        top[root] = root;
        int timer = 0;
        while (!stack.empty()) {
            auto [u, p] = stack.back();
            stack.pop_back();
            id[u] = ++timer;
            D[timer] = u;
            U[timer] = p;
            for (int v : ve[u])
                if (v != w[u]) top[v] = v, stack.push_back({v, v});
            if (w[u]) top[w[u]] = top[u], stack.push_back({w[u], f[0][p]});
        }
    }
    int ask(int x, int k) const {
        assert(k >= 0);
        if (k >= dep[x]) return 0;
        if (!k) return x;
        int log = __lg(k);
        x = f[log][x];
        k -= 1 << log;
        k -= dep[x] - dep[top[x]];
        x = top[x];
        return k >= 0 ? U[id[x] + k] : D[id[x] - k];
    }
};
