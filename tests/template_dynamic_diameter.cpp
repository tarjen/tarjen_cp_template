#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include "../src/data_structure/动态树直径.cpp"

int checks = 0;
#define CHECK(e)                                 \
    do {                                         \
        ++checks;                                \
        if (!(e)) {                              \
            cerr << "FAIL " << __LINE__ << '\n'; \
            exit(1);                             \
        }                                        \
    } while (0)

ll naive(int n, const vector<tuple<int, int, ll>>& edges) {
    vector<vector<pair<int, ll>>> g(n + 1);
    for (auto [u, v, w] : edges) {
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    ll ans = 0;
    for (int s = 1; s <= n; s++) {
        vector<tuple<int, int, ll>> stack{{s, 0, 0}};
        while (!stack.empty()) {
            auto [u, p, d] = stack.back();
            stack.pop_back();
            ans = max(ans, d);
            for (auto [v, w] : g[u])
                if (v != p) stack.push_back({v, u, d + w});
        }
    }
    return ans;
}

int main() {
    DynamicTreeDiameter<> single(1, {});
    CHECK(single.query() == 0);
    vector<tuple<int, int, ll>> zero_edges{{2, 1, 0}, {3, 2, 0}};
    DynamicTreeDiameter zero(3, zero_edges);
    CHECK(zero.query() == 0);
    zero.update(0, 4);
    CHECK(zero.query() == 4);
    zero.update(1, 7);
    CHECK(zero.query() == 11);
    zero.update(0, 0);
    CHECK(zero.query() == 7);
    DynamicTreeDiameter<> wide(3, {{1, 2, 1LL << 40}, {2, 3, 1LL << 40}});
    CHECK(wide.query() == 1LL << 41);
    wide.update(1, 0);
    CHECK(wide.query() == 1LL << 40);
    DynamicTreeDiameter integer(2, vector<tuple<int, int, int>>{{2, 1, 5}});
    integer.update(0, 3);
    CHECK(integer.query() == 3);

    mt19937 rng(20261006);
    for (int trial = 0; trial < 250; trial++) {
        int n = 2 + rng() % 24;
        vector<tuple<int, int, ll>> edges;
        for (int v = 2; v <= n; v++) {
            int u = 1 + rng() % (v - 1);
            ll w = rng() % 31;
            if (rng() & 1)
                edges.push_back({u, v, w});
            else
                edges.push_back({v, u, w});
        }
        shuffle(edges.begin(), edges.end(), rng);
        DynamicTreeDiameter tr(n, edges), other(n, edges);
        ll initial = naive(n, edges);
        CHECK(tr.query() == initial);
        for (int q = 0; q < 120; q++) {
            int id = rng() % (n - 1);
            ll w = q % 11 == 0 ? 0 : rng() % 101;
            tr.update(id, w);
            get<2>(edges[id]) = w;
            ll expected = naive(n, edges);
            CHECK(tr.query() == expected);
            CHECK(tr.query() == expected);  // 重复查询不改变状态。
            CHECK(other.query() == initial);
        }
    }
    int n = 200001;
    vector<tuple<int, int, ll>> star;
    for (int i = 2; i <= n; i++) star.push_back({i, 1, i});
    DynamicTreeDiameter large(n, star);
    CHECK(large.query() == 2LL * n - 1);
    large.update(n - 2, 0);
    CHECK(large.query() == 2LL * n - 3);
    vector<tuple<int, int, ll>> chain;
    for (int i = 2; i <= 1000; i++) chain.push_back({i, i - 1, 1});
    DynamicTreeDiameter path(1000, chain);
    CHECK(path.query() == 999);
    path.update(0, 0);
    CHECK(path.query() == 998);
    cout << "PASS: dynamic tree diameter, " << checks
         << " checks, seed 20261006\n";
}
