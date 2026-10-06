// SSP mf(n,s,t); mf.add(u,v,cap,cost); mf.min_cost(); 0base节点[0,n-1]。
#include <bits/stdc++.h>
using namespace std;

struct SSP {
    struct E {
        int to;
        long long cap, cost;
    };
    int n, S, T;
    vector<E> edges;
    vector<vector<int>> g;
    vector<int> fr, in;
    vector<long long> dis;
    SSP(int n, int s = -1, int t = -1)
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
    pair<long long, long long> min_cost(int s, int t) {
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
    pair<long long, long long> min_cost() { return min_cost(S, T); }
};
