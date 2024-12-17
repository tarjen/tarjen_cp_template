#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 10;
struct info {
    ll w, lm, m, mr, lmr;
};
info operator+(info a, info b) {
    info c;
    c.w = max(a.w, b.w);
    c.m = max(a.m, b.m);
    c.lm = max({a.lm, b.lm, a.w + b.m});
    c.mr = max({a.mr, b.mr, a.m + b.w});
    c.lmr = max({a.lmr, b.lmr, a.lm + b.w, a.w + b.mr});
    return c;
}
struct Node {
    int l, r;
    ll tag = 0;
    info res;
};
struct SegmentTree {
    Node a[maxn * 4];
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
        if (a[i].l == a[i].r) return;
        pushdown(i * 2);
        pushdown(i * 2 + 1);
        a[i].res = a[i * 2].res + a[i * 2 + 1].res;
    }
    void build(int i, int l, int r) {
        a[i].l = l, a[i].r = r;
        tag_init(i);
        a[i].res = {0, 0, 0, 0, 0};
        if (l >= r) return;
        int mid = (l + r) / 2;
        build(i * 2, l, mid);
        build(i * 2 + 1, mid + 1, r);
    }
    void update(int i, int l, int r, ll w) {
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
    info query(int i, int l, int r) {
        pushdown(i);
        if (a[i].r < l || a[i].l > r || l > r) return info{0, 0, 0, 0, 0};
        if (a[i].l >= l && a[i].r <= r) {
            return a[i].res;
        }
        return query(i * 2, l, r) + query(i * 2 + 1, l, r);
    }
};
SegmentTree tri;
vector<pair<int, ll>> ve[maxn];
int L[maxn], R[maxn], tot = 0;
int dfn[maxn * 2];
ll dep[maxn];
void dfs(int x, int h) {
    dfn[++tot] = x;
    L[x] = tot;
    for (auto [it, w] : ve[x])
        if (it != h) {
            dep[it] = dep[x] + w;
            dfs(it, x);
            dfn[++tot] = x;
        }
    R[x] = tot;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    ll ww;
    cin >> n >> q >> ww;
    vector<tuple<int, int, ll>> edges(n - 1);
    for (int i = 1; i < n; i++) {
        int x, y;
        ll w;
        cin >> x >> y >> w;
        ve[x].emplace_back(y, w);
        ve[y].emplace_back(x, w);
        edges[i - 1] = make_tuple(x, y, w);
    }
    dfs(1, 0);
    // for (int i = 1; i <= tot; i++) cout << dfn[i] << " \n"[i == tot];
    // for (int i = 1; i <= n; i++) cout << L[i] << " \n"[i == n];
    // for (int i = 1; i <= n; i++) cout << R[i] << " \n"[i == n];
    tri.build(1, 1, 2 * n);
    for (int i = 1; i <= n; i++) {
        for (auto [it, w] : ve[i])
            if (dep[it] > dep[i]) {
                // cout << "i=" << i << " it=" << it << " w=" << w << endl;
                tri.update(1, L[it], R[it], w);
            }
    }
    ll lastans = 0;
    while (q--) {
        ll d, e;
        cin >> d >> e;
        d = (lastans + d) % (n - 1);
        e = (lastans + e) % ww;
        auto &[x, y, w] = edges[d];
        if (dep[x] > dep[y]) swap(x, y);
        ll delta = e - w;
        // cout << "x=" << x << " y=" << y << " w=" << w << " e=" << e << endl;
        w += delta;
        tri.update(1, L[y], R[y], delta);
        info ans = tri.query(1, 1, 2 * n);
        lastans = ans.lmr;
        cout << ans.lmr << "\n";
    }
}