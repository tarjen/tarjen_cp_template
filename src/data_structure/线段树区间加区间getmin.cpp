// 用法：
// SegmentTree<> tr(4);  // 初值 0，管理闭区间 [0,4]。
// tr.update(1, 3, 2);  // 闭区间加 2。
// ll ans = tr.query(0, 4);  // 区间最小值为 0。
// 数组构造：SegmentTree tr(vector<ll>{1,2,3})，范围 [0,2]。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
template <class T = ll>
struct SegmentTree {
    struct Node {
        int l, r;
        T res = 0, tag = 0;
    };
    static constexpr T inf = numeric_limits<T>::max();
    int n;  // 元素个数
    vector<Node> a;
    void tag_init(int i) { a[i].tag = 0; }
    void tag_union(int fa, int i) { a[i].tag += a[fa].tag; }
    void tag_cal(int i) { a[i].res += a[i].tag; }
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
        a[i].res = min(a[i * 2].res, a[i * 2 + 1].res);
    }
    void build(int i, int l, int r, const vector<T>& v = {}) {
        a[i] = {l, r};
        if (l == r) {
            a[i].res = v.empty() ? T(0) : v[l];
            return;
        }
        int mid = (l + r) / 2;
        build(i * 2, l, mid, v);
        build(i * 2 + 1, mid + 1, r, v);
        pushup(i);
    }
    void update(int i, int l, int r, T w) {
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
    T query(int i, int l, int r) {
        pushdown(i);
        if (a[i].r < l || a[i].l > r || l > r) return inf;
        if (a[i].l >= l && a[i].r <= r) {
            return a[i].res;
        }
        return min(query(i * 2, l, r), query(i * 2 + 1, l, r));
    }

    SegmentTree(int _n) : n(_n) {
        assert(0 <= _n && _n < INT_MAX);
        ++n;
        a.resize(4LL * n + 4);
        build(1, 0, _n);
    }
    SegmentTree(const vector<T>& v) : n(v.size()), a(4LL * n + 4) {
        if (n) build(1, 0, n - 1, v);
    }
    void update(int l, int r, T w) {
        assert(n > 0 && 0 <= l && l <= n && -1 <= r && r < n);
        update(1, l, r, w);
    }
    T query(int l, int r) {
        assert(n > 0 && 0 <= l && l <= n && -1 <= r && r < n);
        return query(1, l, r);
    }
};
