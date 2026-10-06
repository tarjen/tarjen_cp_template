// bounded_flow f(n,s,t); add(u,v,cap,cost);
// mincost()；结果optional{最大流,最小费用}；0base节点[0,n-1]。
#include <bits/stdc++.h>
using namespace std;
struct flow {
    struct E {
        int to;
        long long cap, cost;
    };
    int n, S, T;
    vector<E> edges;
    vector<vector<int>> g;
    vector<int> fr, in;
    vector<long long> dis;
    flow(int n, int s = -1, int t = -1)
        : n(n), S(s), T(t), g(n), fr(n), in(n), dis(n) {}
    int add(int u, int v, long long w, long long c) {
        int id = edges.size();
        g[u].push_back(id);
        edges.push_back({v, w, c});
        g[v].push_back(id + 1);
        edges.push_back({u, 0, -c});
        return id;
    }
    // 要求残量网络中没有可达负费用环；流量和费用须在long long范围内。
    // 在当前残量网络上增广，重复调用不恢复原容量。
    pair<long long, long long> mincost(int s, int t) {
        assert(s != t);
        const long long inf = numeric_limits<long long>::max() / 4;
        long long flow = 0, cost = 0;
        while (true) {
            fill(dis.begin(), dis.end(), inf);
            fill(in.begin(), in.end(), 0);
            queue<int> q;
            q.push(s);
            in[s] = 1;
            dis[s] = 0;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                in[u] = 0;
                for (int id : g[u]) {
                    auto e = edges[id];
                    if (e.cap > 0 && dis[u] + e.cost < dis[e.to]) {
                        dis[e.to] = dis[u] + e.cost;
                        fr[e.to] = id;
                        if (!in[e.to]) in[e.to] = 1, q.push(e.to);
                    }
                }
            }
            if (dis[t] == inf) return {flow, cost};
            long long f = inf;
            for (int u = t; u != s; u = edges[fr[u] ^ 1].to)
                f = min(f, edges[fr[u]].cap);
            flow += f;
            cost += dis[t] * f;
            for (int u = t; u != s; u = edges[fr[u] ^ 1].to)
                edges[fr[u]].cap -= f, edges[fr[u] ^ 1].cap += f;
        }
    }
    pair<long long, long long> mincost() { return mincost(S, T); }
};

struct bounded_flow {
    struct Edge {
        int u, v;
        long long lo, hi, cost;
    };
    int n, S, T;
    vector<Edge> edges;
    bounded_flow(int n, int s = -1, int t = -1) : n(n), S(s), T(t) {}
    // 负费用边先取满流，再用非负费用反向边撤销，保留原模板的变换。
    void add(int u, int v, long long cap, long long cost) {
        add_bounds(u, v, 0, cap, cost);
    }
    void add_bounds(int u, int v, long long lo, long long hi, long long cost) {
        assert(0 <= lo && lo <= hi);
        if (cost < 0) {
            edges.push_back({u, v, hi, hi, cost});
            edges.push_back({v, u, 0, hi - lo, -cost});
        } else
            edges.push_back({u, v, lo, hi, cost});
    }
    // 返回nullopt表示上下界无可行非负s-t流；允许任意负费用环。
    optional<pair<long long, long long>> mincost(int s, int t) const {
        assert(s != t);
        int ss = n, tt = n + 1;
        flow g(n + 2);
        vector<long long> balance(n);
        long long cost = 0, required = 0, total_cap = 0;
        for (auto e : edges) {
            balance[e.u] -= e.lo;
            balance[e.v] += e.lo;
            cost += e.lo * e.cost;
            g.add(e.u, e.v, e.hi - e.lo, e.cost);
            total_cap += e.hi;
        }
        int back = g.add(t, s, total_cap, 0);
        vector<int> auxiliary{back};
        for (int u = 0; u < n; u++) {
            if (balance[u] > 0)
                auxiliary.push_back(g.add(ss, u, balance[u], 0)),
                    required += balance[u];
            else if (balance[u] < 0)
                auxiliary.push_back(g.add(u, tt, -balance[u], 0));
        }
        auto first = g.mincost(ss, tt);
        if (first.first != required) return nullopt;
        long long initial = g.edges[back ^ 1].cap;
        cost += first.second;
        for (int id : auxiliary) g.edges[id].cap = g.edges[id ^ 1].cap = 0;
        auto second = g.mincost(s, t);
        return pair<long long, long long>{initial + second.first,
                                          cost + second.second};
    }
    optional<pair<long long, long long>> mincost() const {
        return mincost(S, T);
    }
};
