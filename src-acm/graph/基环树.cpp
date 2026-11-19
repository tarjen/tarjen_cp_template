/*
用户要求：直接传入 vector<vector<int>> 邻接表，构造时完成预处理。
保留原有 DFS 找环、环上挂树和倍增求距离的方法。
*/
// 用法：节点 1base，连通无向简单图，恰有一个环。
// vector<vector<int>> ve = {{}, {2,3}, {1,3}, {1,2}};
// Graph tr(ve);  // 传入双向邻接表，第 0 格不用；自动预处理。
// int distance = tr.dis(1, 3);  // 无权最短距离为 1。
// 对象保存邻接表副本；外部 ve 可在构造后修改或销毁。
#include <bits/stdc++.h>
using namespace std;
struct Graph {
    int n, lg, len = 0;
    vector<vector<int>> ve;
    vector<int> base, id;
    vector<char> Incircle;
    vector<int> Circle;
    vector<int> dep;
    vector<vector<int>> f;
    Graph(const vector<vector<int>>& g)
        : n((int)g.size() - 1),
          lg(n ? __lg(n) + 1 : 1),
          ve(g),
          base(n + 1),
          id(n + 1, -1),
          Incircle(n + 1),
          dep(n + 1),
          f(lg, vector<int>(n + 1)) {
        Get();
    }
    void dfs(int x, int fa) {
        base[x] = base[fa];
        dep[x] = dep[fa] + 1;
        for (int i = 0; i + 1 < lg; i++) f[i + 1][x] = f[i][f[i][x]];
        for (auto it : ve[x]) {
            if (it == fa) continue;
            f[0][it] = x;
            dfs(it, x);
        }
    }
    void Get() {
        Circle.clear();
        len = 0;
        fill(Incircle.begin(), Incircle.end(), 0); fill(id.begin(), id.end(), -1);
        fill(dep.begin(), dep.end(), 0);
        iota(base.begin(), base.end(), 0);
        for (auto& row : f) fill(row.begin(), row.end(), 0);
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
        for (int i = lg - 1; i >= 0; i--) {
            if (dep[f[i][x]] >= dep[y]) x = f[i][x];
            if (x == y) return x;
        }
        for (int i = lg - 1; i >= 0; i--)
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
