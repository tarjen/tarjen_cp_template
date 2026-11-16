// 与独立朴素增广路对拍，核对返回边及匹配数组；长交替路检查无递归实现。
#include <bits/stdc++.h>
using namespace std;
#ifdef ACM_VARIANT
#include "../src-acm/graph/HK.cpp"
#else
#include "../src/graph/HK.cpp"
#endif

int reference(const vector<vector<int>>& g, int m) {
    vector<int> match(m + 1), vis(m + 1);
    int stamp = 0, ans = 0;
    function<bool(int)> dfs = [&](int u) {
        for (int v : g[u]) {
            if (vis[v] == stamp) continue;
            vis[v] = stamp;
            if (!match[v] || dfs(match[v])) {
                match[v] = u;
                return true;
            }
        }
        return false;
    };
    for (int u = 1; u < (int)g.size(); u++) {
        ++stamp;
        ans += dfs(u);
    }
    return ans;
}

void check(HK& tr, int expected) {
    auto pairs = tr.maxmatch();
    assert((int)pairs.size() == expected);
    vector<int> left(tr.n + 1), right(tr.m + 1);
    for (auto [u, v] : pairs) {
        assert(1 <= u && u <= tr.n && 1 <= v && v <= tr.m);
        assert(!left[u] && !right[v]);
        assert(find(tr.g[u].begin(), tr.g[u].end(), v) != tr.g[u].end());
        left[u] = v;
        right[v] = u;
    }
    assert(left == tr.left && right == tr.right);
}

int main() {
    // 穷举所有至多 3x3 的简单二分图。
    for (int n = 0; n <= 3; n++)
        for (int m = 0; m <= 3; m++)
            for (int mask = 0; mask < (1 << (n * m)); mask++) {
                HK tr(n, m);
                for (int u = 1; u <= n; u++)
                    for (int v = 1; v <= m; v++)
                        if (mask >> ((u - 1) * m + v - 1) & 1) tr.addedge(u, v);
                int expected = reference(tr.g, m);
                check(tr, expected);
                check(tr, expected);
            }
    mt19937 rng(20261116);
    for (int trial = 0; trial < 2000; trial++) {
        int n = rng() % 65, m = rng() % 65;
        HK tr(n, m);
        int e = n && m ? rng() % 700 : 0;
        for (int i = 0; i < e; i++) tr.addedge(rng() % n + 1, rng() % m + 1);
        check(tr, reference(tr.g, m));
        check(tr, reference(tr.g, m));
        // 同一对象加边后，重新求任意一组最大匹配。
        if (n && m) {
            for (int i = 0; i < 20; i++) tr.addedge(rng() % n + 1, rng() % m + 1);
            check(tr, reference(tr.g, m));
        }
    }
    // 初配后只剩最后一个左点，唯一增广路穿过全部 100000 个左点。
    int n = 100000;
    HK chain(n, n);
    for (int u = 1; u < n; u++) {
        chain.addedge(u, u + 1);
        chain.addedge(u, u);
    }
    chain.addedge(n, n);
    check(chain, n);
    check(chain, n);
    HK empty_left(0, n), empty_right(n, 0);
    check(empty_left, 0);
    check(empty_right, 0);
    cout << "PASS: HK exhaustive / 2000 random graphs / reuse / 100000-vertex alternating path\n";
}
