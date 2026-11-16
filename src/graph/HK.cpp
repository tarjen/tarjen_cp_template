/*
用户要求：HK 二分图最大匹配，addedge(x,y)，两侧独立 1base 编号，
返回任意一组最大匹配的 vector<pair<int,int>>；优先考虑常数和手抄便利。
实现：贪心初配、BFS 最短层、当前弧、失败点剪枝；DFS 用显式路径避免递归。
*/
// 用法：HK tr(n, m);  // 左侧 [1,n]，右侧 [1,m]，第 0 格不用。
// tr.addedge(1, 2);  // 只加左到右的边；允许重边。
// auto pairs = tr.maxmatch();  // 每项为 {左点,右点}，pairs.size() 为最大匹配数。
// left[u]/right[v] 为匹配点，未匹配为 0；可重复求解、加边后再求解。
// 每次 maxmatch 从空匹配重算；不要求、也不保证字典序最小。
// V=n+m，E 为边数；时间 O((V+E)*sqrt(V))，空间 O(V+E)。
#include <bits/stdc++.h>
using namespace std;

struct HK {
    int n, m;
    vector<vector<int>> g;
    vector<int> left, right, dis, cur, q;
    HK(int n, int m)
        : n(n), m(m), g(n + 1), left(n + 1), right(m + 1),
          dis(n + 1), cur(n + 1), q(n + 1) {}
    void addedge(int x, int y) {
        assert(1 <= x && x <= n && 1 <= y && y <= m);
        g[x].push_back(y);
    }
    bool bfs() {
        fill(dis.begin(), dis.end(), -1);
        int l = 0, r = 0;
        for (int u = 1; u <= n; u++)
            if (!left[u]) dis[u] = 0, q[r++] = u;
        // 0 作为未匹配右点的虚拟后继，dis[0] 为最短增广层数。
        while (l < r) {
            int u = q[l++];
            if (dis[0] != -1 && dis[u] >= dis[0]) continue;
            for (int v : g[u]) {
                int w = right[v];
                if (dis[w] != -1) continue;
                dis[w] = dis[u] + 1;
                if (w) q[r++] = w;
            }
        }
        return dis[0] != -1;
    }
    bool dfs(int root) {
        // BFS 已结束，复用 q 保存 DFS 路径上的左点。
        int top = 0;
        q[0] = root;
        while (top >= 0) {
            int u = q[top];
            bool down = false;
            while (cur[u] < (int)g[u].size()) {
                int v = g[u][cur[u]++];
                int w = right[v];
                if (dis[w] != dis[u] + 1) continue;
                if (!w) {
                    // 从空闲右点倒推翻转路径，旧 left 即上一条匹配边。
                    for (int j = top; j >= 0; j--) {
                        int x = q[j], old = left[x];
                        left[x] = v;
                        right[v] = x;
                        v = old;
                    }
                    return true;
                }
                q[++top] = w;
                down = true;
                break;
            }
            if (!down) {
                dis[u] = -1;
                --top;
            }
        }
        return false;
    }
    vector<pair<int, int>> maxmatch() {
        fill(left.begin(), left.end(), 0);
        fill(right.begin(), right.end(), 0);
        // 贪心初配减少后续分层次数，不影响最终最大匹配数。
        for (int u = 1; u <= n; u++)
            for (int v : g[u])
                if (!right[v]) {
                    left[u] = v;
                    right[v] = u;
                    break;
                }
        while (bfs()) {
            fill(cur.begin(), cur.end(), 0);
            for (int u = 1; u <= n; u++)
                if (!left[u]) dfs(u);
        }
        vector<pair<int, int>> ans;
        ans.reserve(min(n, m));
        for (int u = 1; u <= n; u++)
            if (left[u]) ans.push_back({u, left[u]});
        return ans;
    }
};
