// 用法：
// SCC tr(3);  // 有向图，节点 1base。
// tr.addedge(1, 2);
// tr.addedge(2, 1);
// tr.addedge(2, 3);
// tr.build();  // 加完边后求强连通分量。
// bool same = tr.col[1] == tr.col[2];  // true。
// int cnt = tr.num;  // 分量数为 2；col[u] 是 1base 分量编号。
#include <bits/stdc++.h>
using namespace std;

struct SCC {
    int n, num = 0, tim = 0;
    vector<vector<int>> ve;
    vector<int> col, dfn, low;
    explicit SCC(int n) : n(n), ve(n + 1), col(n + 1), dfn(n + 1), low(n + 1) {}
    explicit SCC(const vector<vector<int>>& g)
        : SCC((int)g.size() - 1) {
        ve = g;
        build();
    }
    void addedge(int u, int v) { ve[u].push_back(v); }
    void build() {
        num = tim = 0;
        fill(col.begin(), col.end(), 0);
        fill(dfn.begin(), dfn.end(), 0);
        fill(low.begin(), low.end(), 0);
        vector<int> stk;  // 待归属分量的点栈。
        struct F {
            int u, i;
        };
        vector<F> st;  // DFS 调用栈。
        for (int s = 1; s <= n; s++)
            if (!dfn[s]) {
                st.push_back({s, 0});
                stk.push_back(s);
                dfn[s] = low[s] = ++tim;
                while (!st.empty()) {
                    auto& f = st.back();
                    int u = f.u;
                    if (f.i < (int)ve[u].size()) {
                        int v = ve[u][f.i++];
                        if (!dfn[v]) {
                            dfn[v] = low[v] = ++tim;
                            stk.push_back(v);
                            st.push_back({v, 0});
                        } else if (!col[v])
                            low[u] = min(low[u], dfn[v]);
                    } else {
                        if (low[u] == dfn[u]) {
                            ++num;
                            while (true) {
                                int v = stk.back();
                                stk.pop_back();
                                col[v] = num;
                                if (v == u) break;
                            }
                        }
                        st.pop_back();
                        if (!st.empty())
                            low[st.back().u] =
                                min(low[st.back().u], low[u]);
                    }
                }
            }
    }
};
