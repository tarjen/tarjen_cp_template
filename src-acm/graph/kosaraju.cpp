// 用法：
// SCC tr(3);  // 有向图，节点 1base。
// tr.addedge(1, 2);
// tr.addedge(2, 1);
// tr.addedge(2, 3);
// tr.build();  // 加完边后求强连通分量。
// bool same = tr.col[1] == tr.col[2];  // true。
// int count = tr.cnt;  // 分量数为 2；col[u] 是 1base 分量编号。
// 原理：把每个强连通分量缩成点，得到 DAG；反转所有边不改变分量划分。
// 第一遍在原图 DFS，节点退出时加入 sta，得到退出时间从小到大的顺序。
// 若分量间有边 A -> B，则 A 的最大退出时间大于 B：
// 先搜到 A 时，会搜完 B 再退出 A；先搜到 B 时，B 无法到达 A，会先搜完 B。
// 第二遍倒序枚举 sta，在反图中搜索，每次从尚未染色的点开始。
// 此时其分量是剩余原图缩点 DAG 的源点，在反图中无法走到其他未染色分量；
// 分量内部仍互相可达，所以本次恰好染出一个完整的强连通分量。
// 分量编号按原图缩点 DAG 的拓扑序递增；跨分量边 u -> v 满足 col[u] < col[v]。
// 时间、空间复杂度均为 O(n + m)。
#include <bits/stdc++.h>
using namespace std;

struct SCC {
    int n, cnt = 0;
    vector<vector<int>> ve, ve2;
    vector<int> sta, col;
    vector<char> vis;
    SCC(int n) : n(n), ve(n + 1), ve2(n + 1), col(n + 1), vis(n + 1) {}
    SCC(const vector<vector<int>>& graph)
        : SCC((int)graph.size() - 1) {
        ve = graph;
        build();
    }
    void addedge(int u, int v) { ve[u].push_back(v); }
    void build() {
        cnt = 0;
        sta.clear();
        fill(vis.begin(), vis.end(), 0); fill(col.begin(), col.end(), 0);
        ve2.assign(n + 1, {});
        for (int u = 1; u <= n; u++)
            for (int v : ve[u]) ve2[v].push_back(u);
        vector<pair<int, int>> stack;  // 模拟递归栈：(节点，下一个待访问的出边下标)。
        for (int root = 1; root <= n; root++)
            if (!vis[root]) {
                stack.push_back({root, 0});
                vis[root] = 1;
                while (!stack.empty()) {
                    int u = stack.back().first;
                    int& i = stack.back().second;
                    if (i == (int)ve[u].size())  // 所有出边处理完才记录退出顺序。
                        sta.push_back(u), stack.pop_back();
                    else {
                        int v = ve[u][i++];
                        if (!vis[v]) vis[v] = 1, stack.push_back({v, 0});
                    }
                }
            }
        for (int i = (int)sta.size() - 1; i >= 0; i--)  // 按退出时间递减，在反图染色。
            if (!col[sta[i]]) {
                ++cnt;
                vector<int> todo{sta[i]};
                col[sta[i]] = cnt;
                while (!todo.empty()) {
                    int u = todo.back();
                    todo.pop_back();
                    for (int v : ve2[u])
                        if (!col[v]) col[v] = cnt, todo.push_back(v);
                }
            }
    }
};
