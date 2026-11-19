/*
用户要求：将圆方树片段改为完整封装，沿用 Tarjan 点双建树。
实现：显式 DFS 栈，low[v] >= dfn[u] 时弹出一个点双，并连到新方点。
*/
// 用法：BCT bt(4);  // 无向图，原点 1base，支持重边，不接受自环。
// bt.addedge(1, 2); bt.addedge(2, 3); bt.addedge(3, 1);
// bt.addedge(3, 4); bt.build();
// tr 为双向圆方森林；圆点 [1,n]，方点 [n+1,cnt]，第 0 格不用。
// 每个方点连接其点双的所有原点，桥也形成一个含两点的点双。
// 孤立点保留为单独圆点，不另建方点；非连通图分别建树。
// 可重复 build，也可加边后重建；BCT bt(g) 可从 1base 对称邻接表构建。
// 时间、空间 O(n+m)，无递归；build 后 cnt 为圆点与方点的总数。
#include <bits/stdc++.h>
using namespace std;

struct BCT {
    int n, cnt, tim = 0;
    vector<vector<int>> ve, tr;
    vector<int> dfn, low;
    BCT(int n) : n(n), cnt(n), ve(n + 1) {}
    BCT(const vector<vector<int>>& g) : BCT((int)g.size() - 1) {
        ve = g;
        build();
    }
    void addedge(int u, int v) {
        assert(1 <= u && u <= n && 1 <= v && v <= n && u != v);
        ve[u].push_back(v);
        ve[v].push_back(u);
    }
    void build() {
        cnt = n; tim = 0;
        tr.assign(n + 1, {});
        dfn.assign(n + 1, 0);
        low.assign(n + 1, 0);
        vector<int> stk;  // 尚未归入已弹出点双的点。
        struct F { int u, i; };
        vector<F> st;  // DFS 调用栈。
        for (int s = 1; s <= n; s++)
            if (!dfn[s]) {
                dfn[s] = low[s] = ++tim;
                stk.push_back(s);
                st.push_back({s, 0});
                while (!st.empty()) {
                    auto& f = st.back();
                    int u = f.u;
                    if (f.i < (int)ve[u].size()) {
                        int v = ve[u][f.i++];
                        if (!dfn[v]) {
                            dfn[v] = low[v] = ++tim;
                            stk.push_back(v);
                            st.push_back({v, 0});
                        } else
                            low[u] = min(low[u], dfn[v]);
                    } else {
                        st.pop_back();
                        if (st.empty()) continue;
                        int p = st.back().u;
                        low[p] = min(low[p], low[u]);
                        if (low[u] >= dfn[p]) {
                            ++cnt;
                            tr.push_back({p});
                            tr[p].push_back(cnt);
                            int v;
                            do {
                                v = stk.back(); stk.pop_back();
                                tr[cnt].push_back(v);
                                tr[v].push_back(cnt);
                            } while (v != u);
                        }
                    }
                }
                stk.pop_back();  // 此连通分量仅剩 DFS 根。
            }
    }
};
