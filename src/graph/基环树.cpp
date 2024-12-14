#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
/*
1 init
2 addedge
3 Get
*/
struct Graph {
    vector<int> ve[maxn];
    int base[maxn], id[maxn];
    bool Incircle[maxn];
    vector<int> Circle;
    int len = 0;
    int dep[maxn], f[21][maxn];
    int n;
    void init(int _n) {
        n = _n;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < 21; j++) f[j][i] = 0;
            ve[i].clear();
            Incircle[i] = false;
            id[i] = -1;
            base[i] = i;
            Circle.clear();
            len = 0;
            dep[i] = 0;
        }
    }
    void addedge(int x, int y) {
        ve[x].push_back(y);
        ve[y].push_back(x);
    }
    void dfs(int x, int fa) {
        base[x] = base[fa];
        dep[x] = dep[fa] + 1;
        for (int i = 0; i <= 19; i++) f[i + 1][x] = f[i][f[i][x]];
        for (auto it : ve[x]) {
            if (it == fa) continue;
            f[0][it] = x;
            dfs(it, x);
        }
    }
    void Get() {
        vector<int> sta;
        vector<bool> vis(n + 1, false);
        function<bool(int, int)> dfs2 = [&](int x, int h) {
            vis[x] = true;
            sta.push_back(x);
            for (auto it : ve[x])
                if (it != h) {
                    if (vis[it]) {
                        Circle.push_back(it);
                        while (!sta.empty() && sta.back() != it) {
                            Circle.push_back(sta.back());
                            sta.pop_back();
                        }
                        return true;
                    } else {
                        if (dfs2(it, x)) return true;
                    }
                }
            sta.pop_back();
            return false;
        };
        dfs2(1, 0);
        len = (int)Circle.size();
        for (auto it : Circle) Incircle[it] = true;
        for (auto it : Circle) {
            for (auto it2 : ve[it])
                if (!Incircle[it2]) {
                    f[0][it2] = it;
                    dfs(it2, it);
                }
        }
        for (int i = 0; i < len; i++) id[Circle[i]] = i;
    }
    int lca(int x, int y) {
        if (dep[x] < dep[y]) swap(x, y);
        for (int i = 20; i >= 0; i--) {
            if (dep[f[i][x]] >= dep[y]) x = f[i][x];
            if (x == y) return x;
        }
        for (int i = 20; i >= 0; i--)
            if (f[i][x] != f[i][y]) x = f[i][x], y = f[i][y];
        return f[0][x];
    }
    int dis(int x, int y) {
        if (base[x] == base[y]) {
            int l = lca(x, y);
            return dep[x] + dep[y] - 2 * dep[l];
        } else {
            int g = (id[base[x]] - id[base[y]] + len) % len;
            return dep[x] + dep[y] + min(g, len - g);
        }
    }
};
Graph g;