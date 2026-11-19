// 对照枚举所有用边顺序，核对字典序、合法起点、重边、自环、非连通和清空重用。
#include <bits/stdc++.h>
using namespace std;
namespace euler {
#define main euler_example_main
#ifdef ACM_VARIANT
#include "../src-acm/graph/欧拉回路.cpp"
#else
#include "../src/graph/欧拉回路.cpp"
#endif
#undef main
}
using Edges = vector<pair<int, int>>;

optional<vector<int>> solve(int n, const Edges& edges, int start) {
    using namespace euler;
    init();
    for (auto [u, v] : edges) add(u, v);
    vector<int> odd;
    int first = 1;
    for (int u = n; u >= 1; u--) {
        if (deg[u]) first = u;
        if (deg[u] & 1) odd.push_back(u);
    }
    reverse(odd.begin(), odd.end());
    if (!odd.empty() && odd.size() != 2) return nullopt;
    if (!start) start = odd.empty() ? first : odd[0];
    if (odd.size() == 2 && start != odd[0] && start != odd[1]) return nullopt;
    sort_edges(n);
    dfs(start);
    reverse(st.begin(), st.end());
    if (st.size() != edges.size() + 1) return nullopt;
    return st;
}

optional<vector<int>> brute(const Edges& edges, int start) {
    vector<int> path{start}, best;
    function<void(int, int)> dfs = [&](int u, int used) {
        if (used == (1 << edges.size()) - 1) {
            if (best.empty() || path < best) best = path;
            return;
        }
        for (int i = 0; i < (int)edges.size(); i++) {
            if (used >> i & 1) continue;
            auto [a, b] = edges[i];
            if (a != u && b != u) continue;
            int v = a == u ? b : a;
            path.push_back(v);
            dfs(v, used | (1 << i));
            path.pop_back();
        }
    };
    dfs(start, 0);
    if (best.empty()) return nullopt;
    return best;
}

void check(int n, const Edges& edges) {
    optional<vector<int>> best;
    for (int start = 1; start <= n; start++) {
        auto expected = brute(edges, start);
        assert(solve(n, edges, start) == expected);
        if (expected && (!best || *expected < *best)) best = expected;
    }
    assert(solve(n, edges, 0) == best);
}

int main() {
    Edges types;
    for (int u = 1; u <= 3; u++)
        for (int v = u; v <= 3; v++) types.push_back({u, v});
    Edges current;
    function<void(int, int)> enumerate = [&](int first, int remaining) {
        check(3, current);
        if (!remaining) return;
        for (int i = first; i < (int)types.size(); i++) {
            current.push_back(types[i]);
            enumerate(i, remaining - 1);
            current.pop_back();
        }
    };
    enumerate(0, 5);
    mt19937 rng(20261117);
    for (int trial = 0; trial < 400; trial++) {
        int n = 1 + rng() % 5, m = rng() % 8;
        Edges edges;
        while (m--) edges.push_back({1 + int(rng() % n), 1 + int(rng() % n)});
        check(n, edges);
    }
    assert(*solve(4, {{1,2},{1,3},{3,4},{4,1}}, 0) == vector<int>({1,3,4,1,2}));
    Edges parallel(2000, {1, 2});
    auto path = solve(2, parallel, 1);
    assert(path && path->size() == 2001);
    for (int i = 0; i <= 2000; i++) assert((*path)[i] == 1 + i % 2);
    cout << "PASS: Euler lexicographic order / multigraph enumeration / 400 random graphs / reuse\n";
}
