// 可选性能实验：同图比较 HK 和仓库 Dinic，分别计构图及求解时间。
#include <bits/stdc++.h>
using namespace std;
namespace hk_impl {
#include "../src-acm/graph/HK.cpp"
}
namespace flow_impl {
#include "../src/graph/maxflow只算值版本.cpp"
}
using Clock = chrono::steady_clock;
struct Graph {
    string name;
    int n, m;
    vector<pair<int, int>> edges;
};
struct Sample {
    int count;
    double build, solve;
};
double ms(Clock::time_point a, Clock::time_point b) {
    return chrono::duration<double, milli>(b - a).count();
}
Sample run_hk(const Graph& g) {
    auto start = Clock::now();
    hk_impl::HK tr(g.n, g.m);
    for (auto [u, v] : g.edges) tr.addedge(u, v);
    auto built = Clock::now();
    auto pairs = tr.maxmatch();
    auto end = Clock::now();
    return {(int)pairs.size(), ms(start, built), ms(built, end)};
}
Sample run_flow(const Graph& g) {
    auto start = Clock::now();
    int sink = g.n + g.m + 1;
    flow_impl::dinic tr(sink + 1, 0, sink);
    for (int u = 1; u <= g.n; u++) tr.addedge(0, u, 1);
    for (int v = 1; v <= g.m; v++) tr.addedge(g.n + v, sink, 1);
    for (auto [u, v] : g.edges) tr.addedge(u, g.n + v, 1);
    auto built = Clock::now();
    int count = tr.maxflow();
    auto end = Clock::now();
    return {count, ms(start, built), ms(built, end)};
}
double median(vector<double> v) {
    sort(v.begin(), v.end());
    return v[v.size() / 2];
}
int main() {
    mt19937 rng(20261116);
    vector<Graph> graphs;
    auto random_graph = [&](string name, int n, int m, int degree, int active) {
        Graph g{name, n, m, {}};
        g.edges.reserve(n * degree);
        for (int u = 1; u <= n; u++)
            for (int j = 0; j < degree; j++) g.edges.push_back({u, int(rng() % active) + 1});
        graphs.push_back(move(g));
    };
    random_graph("sparse", 20000, 20000, 8, 20000);
    random_graph("dense", 1200, 1200, 500, 1200);
    random_graph("unbalanced", 40000, 2000, 6, 2000);
    random_graph("bottleneck", 10000, 10000, 12, 2000);
    Graph chain{"alternating_path", 1500, 1500, {}};
    for (int u = 1; u < chain.n; u++) {
        chain.edges.push_back({u, u + 1});
        chain.edges.push_back({u, u});
    }
    chain.edges.push_back({chain.n, chain.n});
    graphs.push_back(move(chain));
    cout << "graph,n,m,edges,matching,hk_solve_ms,dinic_solve_ms,hk_total_ms,dinic_total_ms,total_speedup\n";
    cout << fixed << setprecision(3);
    for (const auto& g : graphs) {
        vector<double> hs, fs, ht, ft;
        int count = -1;
        for (int trial = 0; trial < 8; trial++) {
            Sample h, f;
            if (trial & 1) f = run_flow(g), h = run_hk(g);
            else h = run_hk(g), f = run_flow(g);
            if (h.count != f.count) return 1;
            count = h.count;
            if (!trial) continue;  // 热身后取 7 次中位数，生成图的时间不计入。
            hs.push_back(h.solve); fs.push_back(f.solve);
            ht.push_back(h.build + h.solve); ft.push_back(f.build + f.solve);
        }
        cout << g.name << ',' << g.n << ',' << g.m << ',' << g.edges.size() << ',' << count
             << ',' << median(hs) << ',' << median(fs) << ',' << median(ht) << ',' << median(ft)
             << ',' << median(ft) / median(ht) << '\n';
    }
}
