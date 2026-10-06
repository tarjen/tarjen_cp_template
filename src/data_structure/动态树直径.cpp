// 用法：节点 1base，边号 0base，固定树结构，边权非负。
// vector<tuple<int, int, ll>> edges = {{1, 2, 3}, {2, 3, 4}};
// DynamicTreeDiameter tr(3, edges);  // 构造时完成建树。
// ll ans = tr.query();              // 当前直径长度为 7。
// tr.update(0, 1);                  // 第 0 条边的权值改成 1，直径变为 5。
// update 是赋值；query 返回长度。建树 O(n log n)，修改 O(log n)，查询 O(1)。
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <class T = ll>
struct DynamicTreeDiameter {
    struct info {
        T w, lm, m, mr, lmr;
        friend info operator+(info a, info b) {
            info c;
            c.w = max(a.w, b.w);
            c.m = max(a.m, b.m);
            c.lm = max({a.lm, b.lm, a.w + b.m});
            c.mr = max({a.mr, b.mr, a.m + b.w});
            c.lmr = max({a.lmr, b.lmr, a.lm + b.w, a.w + b.mr});
            return c;
        }
    };
    struct SegmentTree {
        struct Node {
            int l, r;
            T tag = 0;
            info res{};
        };
        vector<Node> a;
        void tag_init(int i) { a[i].tag = 0; }
        void tag_union(int fa, int i) { a[i].tag += a[fa].tag; }
        void tag_cal(int i) {
            a[i].res.w += a[i].tag;
            a[i].res.m -= 2 * a[i].tag;
            a[i].res.lm -= a[i].tag;
            a[i].res.mr -= a[i].tag;
        }
        void pushdown(int i) {
            tag_cal(i);
            if (a[i].l != a[i].r) {
                tag_union(i, i * 2);
                tag_union(i, i * 2 + 1);
            }
            tag_init(i);
        }
        void pushup(int i) {
            pushdown(i * 2);
            pushdown(i * 2 + 1);
            a[i].res = a[i * 2].res + a[i * 2 + 1].res;
        }
        void build(int i, int l, int r) {
            a[i].l = l;
            a[i].r = r;
            if (l == r) return;
            int mid = (l + r) / 2;
            build(i * 2, l, mid);
            build(i * 2 + 1, mid + 1, r);
        }
        void update(int i, int l, int r, T w) {
            pushdown(i);
            if (a[i].r < l || a[i].l > r) return;
            if (l <= a[i].l && a[i].r <= r) {
                a[i].tag = w;
                return;
            }
            update(i * 2, l, r, w);
            update(i * 2 + 1, l, r, w);
            pushup(i);
        }
    } tri;
    int n, tot = 0;
    vector<tuple<int, int, T>> edges;
    vector<vector<pair<int, int>>> ve;
    vector<int> L, R, child;
    void dfs(int u, int p) {
        L[u] = ++tot;
        for (auto [v, id] : ve[u]) {
            if (v == p) continue;
            child[id] = v;
            dfs(v, u);
            tot++;
        }
        R[u] = tot;
    }

    DynamicTreeDiameter(int _n, const vector<tuple<int, int, T>>& _edges) {
        assert(_n > 0 && (int)_edges.size() == _n - 1);
        n = _n;
        edges = _edges;
        ve.resize(n + 1);
        L.resize(n + 1);
        R.resize(n + 1);
        child.resize(n - 1);
        for (int i = 0; i < n - 1; i++) {
            auto [u, v, w] = edges[i];
            assert(1 <= u && u <= n && 1 <= v && v <= n && u != v && w >= 0);
            ve[u].push_back({v, i});
            ve[v].push_back({u, i});
        }
        dfs(1, 0);
        tri.a.resize(4 * tot + 4);
        tri.build(1, 1, tot);
        for (int i = 0; i < n - 1; i++)
            tri.update(1, L[child[i]], R[child[i]], get<2>(edges[i]));
    }
    void update(int id, T w) {
        assert(0 <= id && id < n - 1 && w >= 0);
        int u = child[id];
        auto& old = get<2>(edges[id]);
        tri.update(1, L[u], R[u], w - old);
        old = w;
    }
    T query() {
        tri.pushdown(1);
        return tri.a[1].res.lmr;
    }
};
