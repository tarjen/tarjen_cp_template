// 1base；SegmentTree tr(n); tr.update_height(x,h); tr.query();
// 高度非负，初始高度0。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct Node {
    int l, r, len;
    long double mx = 0;
};
struct SegmentTree {
    int n;
    vector<Node> a;
    explicit SegmentTree(int n) : n(n), a(4 * n + 4) {
        if (n) build(1, 1, n);
    }
    // w是高度/位置的斜率；update_height(x,h)直接接收高度。
    void update(int x, long double w) {
        if (n) update(1, x, w);
    }
    void update_height(int x, long double h) { update(x, h / x); }
    int qry(long double x, int i) {  // 起点大过x
        if (a[i].l == a[i].r) {
            return a[i].mx > x;
        }
        if (a[i * 2].mx > x) {
            return a[i].len - a[i * 2].len + qry(x, 2 * i);
        } else
            return qry(x, 2 * i + 1);
    }
    void pushup(int i) {
        if (a[i].l == a[i].r) return;
        a[i].len = a[i * 2].len + qry(a[i * 2].mx, i * 2 + 1);
        a[i].mx = max(a[i * 2].mx, a[i * 2 + 1].mx);
    }
    void build(int i, int l, int r) {
        a[i].l = l, a[i].r = r;
        a[i].len = 0;
        a[i].mx = 0;
        if (l >= r) return;
        int mid = (l + r) / 2;
        build(i * 2, l, mid);
        build(i * 2 + 1, mid + 1, r);
        pushup(i);
    }
    void update(int i, int x, long double w) {
        if (a[i].r < x || a[i].l > x) return;
        if (a[i].l >= x && a[i].r <= x) {
            a[i].mx = w;
            a[i].len = w > 0;
            return;
        }
        update(i * 2, x, w);
        update(i * 2 + 1, x, w);
        pushup(i);
    }
    int query() { return n ? a[1].len : 0; }
};
