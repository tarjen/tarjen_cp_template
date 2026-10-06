// HLD hld(graph,values,root,mod);
// chain_add/chain_sum、subtree_add/subtree_sum。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// 连通树，图与初值均为1base；所有路径、子树操作都取模。
struct HLD {
    int n, mod, root;

    void add(int& x, int y) { x = ((long long)x + y) % mod; }
    struct Node {
        int l, r, res, tag;
    };
    struct SegmentTree {
        int mod;
        vector<Node> a;
        SegmentTree(int n, int mod) : mod(mod), a(4 * n + 4) {
            if (n) build(1, 1, n);
        }
        void add(int& x, int y) { x = ((long long)x + y) % mod; }
        void tag_init(int i) { a[i].tag = 0; }
        void tag_union(int fa, int i) { add(a[i].tag, a[fa].tag); }
        void tag_cal(int i) {
            add(a[i].res, (ll)a[i].tag * (a[i].r - a[i].l + 1) % mod);
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
            if (a[i].l == a[i].r) return;
            pushdown(i * 2);
            pushdown(i * 2 + 1);
            a[i].res = ((ll)a[i * 2].res + a[i * 2 + 1].res) % mod;
        }
        void build(int i, int l, int r) {
            a[i].l = l, a[i].r = r;
            tag_init(i);
            a[i].res = 0;
            if (l >= r) return;
            int mid = (l + r) / 2;
            build(i * 2, l, mid);
            build(i * 2 + 1, mid + 1, r);
        }
        void update(int i, int l, int r, int w) {
            pushdown(i);
            if (a[i].r < l || a[i].l > r || l > r) return;
            if (a[i].l >= l && a[i].r <= r) {
                a[i].tag = w;
                return;
            }
            update(i * 2, l, r, w);
            update(i * 2 + 1, l, r, w);
            pushup(i);
        }
        int query(int i, int l, int r) {
            pushdown(i);
            if (a[i].r < l || a[i].l > r || l > r) return 0;
            if (a[i].l >= l && a[i].r <= r) {
                return a[i].res;
            }
            return ((ll)query(i * 2, l, r) + query(i * 2 + 1, l, r)) % mod;
        }
    };
    SegmentTree tri;
    vector<vector<int>> ve;
    vector<int> L, R, siz, top, dep, fa, dfn, heavy;
    int tot = 0;
    HLD(const vector<vector<int>>& graph, const vector<int>& values, int root,
        int mod)
        : n((int)graph.size() - 1),
          mod(mod),
          root(root),
          tri(n, mod),
          ve(graph),
          L(n + 1),
          R(n + 1),
          siz(n + 1, 1),
          top(n + 1),
          dep(n + 1),
          fa(n + 1),
          dfn(n + 1),
          heavy(n + 1) {
        assert(mod > 0 && values.size() == graph.size());
        if (!n) return;
        vector<int> order{root};
        dep[root] = 1;
        for (int i = 0; i < (int)order.size(); i++) {
            int u = order[i];
            for (int v : ve[u])
                if (v != fa[u])
                    fa[v] = u, dep[v] = dep[u] + 1, order.push_back(v);
        }
        for (int i = n - 1; i > 0; i--) {
            int u = order[i], p = fa[u];
            siz[p] += siz[u];
            if (!heavy[p] || siz[u] > siz[heavy[p]]) heavy[p] = u;
        }
        vector<pair<int, int>> stack{{root, root}};
        while (!stack.empty()) {
            auto [u, t] = stack.back();
            stack.pop_back();
            top[u] = t;
            L[u] = ++tot;
            dfn[tot] = u;
            for (int v : ve[u])
                if (v != fa[u] && v != heavy[u]) stack.push_back({v, v});
            if (heavy[u]) stack.push_back({heavy[u], t});
        }
        for (int u = 1; u <= n; u++) {
            R[u] = L[u] + siz[u] - 1;
            tri.update(1, L[u], L[u], normalize(values[u]));
        }
    }
    int normalize(long long w) const {
        w %= mod;
        return w < 0 ? w + mod : w;
    }
    void subtree_add(int u, long long w) {
        tri.update(1, L[u], R[u], normalize(w));
    }
    int subtree_sum(int u) { return tri.query(1, L[u], R[u]); }
    void chain_add(int x, int y, long long value) {
        int w = normalize(value);  // chain add w
        while (top[x] != top[y]) {
            if (dep[top[x]] < dep[top[y]]) swap(x, y);
            tri.update(1, L[top[x]], L[x], w);
            x = fa[top[x]];
        }
        if (L[x] > L[y]) swap(x, y);
        tri.update(1, L[x], L[y], w);
    }
    int chain_sum(int x, int y) {  // query the length of chain
        int sum = 0;
        while (top[x] != top[y]) {
            if (dep[top[x]] < dep[top[y]]) swap(x, y);
            add(sum, tri.query(1, L[top[x]], L[x]));
            x = fa[top[x]];
        }
        if (L[x] > L[y]) swap(x, y);
        add(sum, tri.query(1, L[x], L[y]));
        return sum;
    }
};
