// 1base；SCC scc(graph); Kosaraju两遍遍历；col为分量编号。
#include <bits/stdc++.h>
using namespace std;

struct SCC {
    int n, cnt = 0;
    vector<vector<int>> ve, ve2;
    vector<int> sta, col;
    vector<char> vis;
    explicit SCC(int n) : n(n), ve(n + 1), ve2(n + 1), col(n + 1), vis(n + 1) {}
    explicit SCC(const vector<vector<int>>& graph)
        : SCC((int)graph.size() - 1) {
        ve = graph;
        build();
    }
    void addedge(int u, int v) { ve[u].push_back(v); }
    void build() {
        cnt = 0;
        sta.clear();
        fill(vis.begin(), vis.end(), 0);
        fill(col.begin(), col.end(), 0);
        ve2.assign(n + 1, {});
        for (int u = 1; u <= n; u++)
            for (int v : ve[u]) ve2[v].push_back(u);
        vector<pair<int, int>> stack;
        for (int root = 1; root <= n; root++)
            if (!vis[root]) {
                stack.push_back({root, 0});
                vis[root] = 1;
                while (!stack.empty()) {
                    int u = stack.back().first;
                    int& i = stack.back().second;
                    if (i == (int)ve[u].size())
                        sta.push_back(u), stack.pop_back();
                    else {
                        int v = ve[u][i++];
                        if (!vis[v]) vis[v] = 1, stack.push_back({v, 0});
                    }
                }
            }
        for (int i = (int)sta.size() - 1; i >= 0; i--)
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
