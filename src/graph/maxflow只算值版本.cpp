// 用法：
// dinic tr(3, 0, 2);  // 节点 0base，源 0、汇 2。
// int id = tr.addedge(0, 1, 5);
// tr.addedge(1, 2, 3);
// ll flow = tr.maxflow();  // 最大流为 3。
// ll used = 5 - tr.edges[id].cap;  // 第一条边实际流量为 3。
// 会修改残量网络，再次求流返回新增流量；容量非负。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
struct dinic {
    struct E {
        int to;
        ll cap;
    };
    int n, S, T;
    vector<E> edges;
    vector<vector<int>> g;
    vector<int> dis, now;
    explicit dinic(int n, int s = -1, int t = -1)
        : n(n), S(s), T(t), g(n), dis(n), now(n) {}
    // 0base节点[0,n-1]；返回正向边编号，原容量减剩余容量即该边流量。
    int addedge(int u, int v, ll w) {
        int id = edges.size();
        g[u].push_back(id);
        edges.push_back({v, w});
        g[v].push_back(id + 1);
        edges.push_back({u, 0});
        return id;
    }
    bool bfs(int s, int t) {
        fill(dis.begin(), dis.end(), -1);
        queue<int> q;
        q.push(s);
        dis[s] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int id : g[u])
                if (edges[id].cap > 0 && dis[edges[id].to] == -1) {
                    dis[edges[id].to] = dis[u] + 1;
                    q.push(edges[id].to);
                }
        }
        return dis[t] != -1;
    }
    ll dfs(int u, int t, ll f) {
        if (u == t) return f;
        for (int& i = now[u]; i < (int)g[u].size(); i++) {
            int id = g[u][i], v = edges[id].to;
            if (edges[id].cap > 0 && dis[v] == dis[u] + 1) {
                ll d = dfs(v, t, min(f, edges[id].cap));
                if (d) {
                    edges[id].cap -= d;
                    edges[id ^ 1].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
    // 计算当前残量网络上新增的最大流；重复调用不会恢复原容量。
    ll maxflow(int s, int t) {
        assert(s != t);
        ll flow = 0, d;
        while (bfs(s, t)) {
            fill(now.begin(), now.end(), 0);
            while ((d = dfs(s, t, numeric_limits<ll>::max() / 4)))
                flow += d;
        }
        return flow;
    }
    ll maxflow() { return maxflow(S, T); }
};
