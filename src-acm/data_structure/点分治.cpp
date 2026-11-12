// 用法：
// CentroidDecomposition cd(3);  // 1base 连通无权树。
// cd.addedge(1, 2);
// cd.addedge(2, 3);
// cd.dfs(1);                   // 完成点分治；题目统计写在 dfs 的注释处。
// 每棵树创建一个对象，无需手动清空。
#include <bits/stdc++.h>
using namespace std;

struct CentroidDecomposition {
    int n;
    vector<vector<int>> ve;
    vector<int> siz;
    vector<char> vis;

    void getsize(int u, int p) {
        siz[u] = 1;
        for (int v : ve[u]) {
            if (v == p || vis[v]) continue;
            getsize(v, u);
            siz[u] += siz[v];
        }
    }
    int getroot(int u, int p, int total) {
        for (int v : ve[u]) {
            if (v == p || vis[v]) continue;
            if (siz[v] > total / 2) return getroot(v, u, total);
        }
        return u;
    }

    CentroidDecomposition(int _n) : n(_n), ve(n + 1), siz(n + 1), vis(n + 1) {
        assert(n > 0);
    }
    void addedge(int u, int v) {
        assert(1 <= u && u <= n && 1 <= v && v <= n);
        ve[u].push_back(v);
        ve[v].push_back(u);
    }
    void dfs(int u) {
        assert(1 <= u && u <= n && !vis[u]);
        getsize(u, 0);
        int rt = getroot(u, 0, siz[u]);
        vis[rt] = true;
        // 在这里处理经过重心 rt 的路径。
        for (int v : ve[rt]) {
            if (!vis[v]) dfs(v);
        }
    }
};
