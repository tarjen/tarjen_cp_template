// 1base有向图；SCC scc(graph)，或SCC scc(n); addedge(); build();
// col为分量编号。
#include <bits/stdc++.h>
using namespace std;

struct SCC {
    int n, num = 0, dfstime = 0;
    vector<vector<int>> ve;
    vector<int> col, dfn, low;
    explicit SCC(int n) : n(n), ve(n + 1), col(n + 1), dfn(n + 1), low(n + 1) {}
    explicit SCC(const vector<vector<int>>& graph)
        : SCC((int)graph.size() - 1) {
        ve = graph;
        build();
    }
    void addedge(int u, int v) { ve[u].push_back(v); }
    void build() {
        num = dfstime = 0;
        fill(col.begin(), col.end(), 0);
        fill(dfn.begin(), dfn.end(), 0);
        fill(low.begin(), low.end(), 0);
        vector<int> active;
        struct Frame {
            int u, next;
        };
        vector<Frame> stack;
        for (int root = 1; root <= n; root++)
            if (!dfn[root]) {
                stack.push_back({root, 0});
                active.push_back(root);
                dfn[root] = low[root] = ++dfstime;
                while (!stack.empty()) {
                    auto& frame = stack.back();
                    int u = frame.u;
                    if (frame.next < (int)ve[u].size()) {
                        int v = ve[u][frame.next++];
                        if (!dfn[v]) {
                            dfn[v] = low[v] = ++dfstime;
                            active.push_back(v);
                            stack.push_back({v, 0});
                        } else if (!col[v])
                            low[u] = min(low[u], dfn[v]);
                    } else {
                        if (low[u] == dfn[u]) {
                            ++num;
                            while (true) {
                                int v = active.back();
                                active.pop_back();
                                col[v] = num;
                                if (v == u) break;
                            }
                        }
                        stack.pop_back();
                        if (!stack.empty())
                            low[stack.back().u] =
                                min(low[stack.back().u], low[u]);
                    }
                }
            }
    }
};
