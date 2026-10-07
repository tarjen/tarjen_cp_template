// 用法：
// bounded_flow tr(2, 0, 1);  // 节点 0base，源 0、汇 1。
// tr.add(0, 1, 3, 2);  // 容量 3，单位费用 2；允许负费用与负环。
// auto ans = tr.mincost();  // optional<pair<ll,ll>>，本例 {3,6}。
// if (ans) { auto [flow, cost] = *ans; }  // 无可行非负源汇流时为 nullopt。
// 有上下界时用 add_bounds(u,v,lo,hi,cost)，要求 0<=lo<=hi。
// 每次求解重建残量网络，结果依次是最大流、最小总费用。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct flow {
    struct E {
        int to;
        ll cap, cost;
    };
    int n, S, T;
    vector<E> edges;
    vector<vector<int>> g;
    vector<int> fr, in;
    vector<ll> dis;
    flow(int n, int s = -1, int t = -1)
        : n(n), S(s), T(t), g(n), fr(n), in(n), dis(n) {}
    int add(int u, int v, ll w, ll c) {
        int id = edges.size();
        g[u].push_back(id);
        edges.push_back({v, w, c});
        g[v].push_back(id + 1);
        edges.push_back({u, 0, -c});
        return id;
    }
    // 要求残量网络中没有可达负费用环；流量和费用须在long long范围内。
    // 在当前残量网络上增广，重复调用不恢复原容量。
    pair<ll, ll> mincost(int s, int t) {
        assert(s != t);
        const ll inf = numeric_limits<ll>::max() / 4;
        ll flow = 0, cost = 0;
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
            ll f = inf;
            for (int u = t; u != s; u = edges[fr[u] ^ 1].to)
                f = min(f, edges[fr[u]].cap);
            flow += f;
            cost += dis[t] * f;
            for (int u = t; u != s; u = edges[fr[u] ^ 1].to)
                edges[fr[u]].cap -= f, edges[fr[u] ^ 1].cap += f;
        }
    }
    pair<ll, ll> mincost() { return mincost(S, T); }
};

struct bounded_flow {
    struct Edge {
        int u, v;
        ll lo, hi, cost;
    };
    int n, S, T;
    vector<Edge> edges;
    bounded_flow(int n, int s = -1, int t = -1) : n(n), S(s), T(t) {}
    // 负费用边先取满流，再用非负费用反向边撤销，保留原模板的变换。
    void add(int u, int v, ll cap, ll cost) {
        add_bounds(u, v, 0, cap, cost);
    }
    void add_bounds(int u, int v, ll lo, ll hi, ll cost) {
        assert(0 <= lo && lo <= hi);
        if (cost < 0) {
            edges.push_back({u, v, hi, hi, cost});
            edges.push_back({v, u, 0, hi - lo, -cost});
        } else
            edges.push_back({u, v, lo, hi, cost});
    }
    // 返回nullopt表示上下界无可行非负s-t流；允许任意负费用环。
    optional<pair<ll, ll>> mincost(int s, int t) const {
        assert(s != t);
        int ss = n, tt = n + 1;
        flow g(n + 2);
        vector<ll> balance(n);
        ll cost = 0, required = 0, total_cap = 0;
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
        ll initial = g.edges[back ^ 1].cap;
        cost += first.second;
        for (int id : auxiliary) g.edges[id].cap = g.edges[id ^ 1].cap = 0;
        auto second = g.mincost(s, t);
        return pair<ll, ll>{initial + second.first,
                                          cost + second.second};
    }
    optional<pair<ll, ll>> mincost() const {
        return mincost(S, T);
    }
};
