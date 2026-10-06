// 0base闭区间；tr(n)管理[0,n]，tr(v)使用普通vector；数值类型T默认ll。
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template <class T = ll>
struct SegmentTree {
    struct Node {
        int l, r;
        T res = 0, tag = 0, tag2 = 0, res2 = 0;
    };
    static constexpr T inf = numeric_limits<T>::max();
    int n;  // 元素个数
    vector<Node> a;
    void tag_init(int i) { a[i].tag = a[i].tag2 = 0; }
    void tag_union(int fa, int i) {
        if (a[fa].tag2 < 0) a[i].tag2 = min(a[i].tag2, a[i].tag + a[fa].tag2);
        a[i].tag += a[fa].tag;
    }
    void tag_cal(int i) {
        if (a[i].tag2 < 0) a[i].res2 = min(a[i].res2, a[i].res + a[i].tag2);
        a[i].res += a[i].tag;
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
        a[i].res = min(a[i * 2].res, a[i * 2 + 1].res);
        a[i].res2 = min(a[i * 2].res2, a[i * 2 + 1].res2);
    }
    void build(int i, int l, int r, const vector<T>& v = {}) {
        a[i] = {l, r};
        if (l == r) {
            a[i].res = v.empty() ? T(0) : v[l];
            a[i].res2 = a[i].res;
            return;
        }
        int mid = (l + r) / 2;
        build(i * 2, l, mid, v);
        build(i * 2 + 1, mid + 1, r, v);
        pushup(i);
    }
    void update(int i, int l, int r, T w) {
        if (a[i].r < l || a[i].l > r || l > r) return;
        pushdown(i);
        if (a[i].l >= l && a[i].r <= r) {
            a[i].tag += w;
            a[i].tag2 = min(a[i].tag2, a[i].tag);
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
            return a[i].res2;
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
