// 独立判据：枚举顶点子集，检查删去任一点后仍连通，取极大子集为点双。
#include <bits/stdc++.h>
using namespace std;
#ifdef ACM_VARIANT
#include "../src-acm/graph/圆方树.cpp"
#else
#include "../src/graph/圆方树.cpp"
#endif

set<vector<int>> reference(const vector<vector<int>>& g) {
    int n = (int)g.size() - 1;
    vector<int> adj(n), blocks;
    for (int u = 1; u <= n; u++)
        for (int v : g[u]) adj[u - 1] |= 1 << (v - 1);
    for (int mask = 1; mask < (1 << n); mask++) {
        if (__builtin_popcount((unsigned)mask) < 2) continue;
        bool ok = true;
        for (int ban = -1; ban < n && ok; ban++) {
            if (ban >= 0 && !(mask >> ban & 1)) continue;
            int rest = ban < 0 ? mask : mask & ~(1 << ban);
            int seen = rest & -rest, todo = seen;
            while (todo) {
                int u = __builtin_ctz((unsigned)todo);
                todo &= todo - 1;
                int add = adj[u] & rest & ~seen;
                seen |= add; todo |= add;
            }
            ok = seen == rest;
        }
        if (ok) blocks.push_back(mask);
    }
    set<vector<int>> ans;
    for (int mask : blocks) {
        bool maximal = true;
        for (int other : blocks)
            if (mask != other && (mask & other) == mask) maximal = false;
        if (!maximal) continue;
        vector<int> nodes;
        for (int u = 0; u < n; u++)
            if (mask >> u & 1) nodes.push_back(u + 1);
        ans.insert(nodes);
    }
    return ans;
}

void forest(const BCT& bt) {
    assert((int)bt.tr.size() == bt.cnt + 1);
    vector<int> fa(bt.cnt + 1);
    iota(fa.begin(), fa.end(), 0);
    auto find = [&](int u) {
        while (u != fa[u]) u = fa[u] = fa[fa[u]];
        return u;
    };
    vector<pair<int, int>> forward, reverse;
    for (int b = bt.n + 1; b <= bt.cnt; b++) {
        assert(bt.tr[b].size() >= 2);
        for (int u : bt.tr[b]) {
            assert(1 <= u && u <= bt.n);
            int x = find(u), y = find(b);
            assert(x != y);
            fa[x] = y;
            forward.push_back({u, b});
        }
    }
    for (int u = 1; u <= bt.n; u++)
        for (int b : bt.tr[u]) reverse.push_back({u, b});
    sort(forward.begin(), forward.end());
    sort(reverse.begin(), reverse.end());
    assert(forward == reverse);
}

void check(BCT& bt) {
    bt.build();
    forest(bt);
    set<vector<int>> got;
    for (int b = bt.n + 1; b <= bt.cnt; b++) {
        auto nodes = bt.tr[b];
        sort(nodes.begin(), nodes.end());
        assert(got.insert(nodes).second);
    }
    assert(got == reference(bt.ve));
    auto before = bt.tr;
    bt.build();
    assert(bt.tr == before);
    BCT copy(bt.ve);
    assert(copy.tr == bt.tr);
}

int main() {
    for (int n = 0; n <= 5; n++) {
        vector<pair<int, int>> edges;
        for (int u = 1; u <= n; u++)
            for (int v = u + 1; v <= n; v++) edges.push_back({u, v});
        for (int mask = 0; mask < (1 << edges.size()); mask++) {
            BCT bt(n);
            for (int i = 0; i < (int)edges.size(); i++)
                if (mask >> i & 1) bt.addedge(edges[i].first, edges[i].second);
            check(bt);
        }
    }
    mt19937 rng(20261119);
    for (int trial = 0; trial < 500; trial++) {
        int n = 2 + rng() % 6;
        BCT bt(n);
        for (int i = rng() % 30; i > 0; i--) {
            int u = 1 + rng() % n, v = 1 + rng() % n;
            if (u != v) bt.addedge(u, v);
        }
        check(bt);
        bt.addedge(1, n);
        check(bt);
    }
    int n = 100000;
    BCT chain(n);
    for (int u = 1; u < n; u++) chain.addedge(u, u + 1);
    chain.build();
    assert(chain.cnt == 2 * n - 1);
    forest(chain);
    for (int b = n + 1; b <= chain.cnt; b++) {
        assert(chain.tr[b].size() == 2);
        assert(abs(chain.tr[b][0] - chain.tr[b][1]) == 1);
    }
    cout << "PASS: BCT exhaustive n<=5 / 500 multigraphs / rebuild / 100000-vertex chain\n";
}
