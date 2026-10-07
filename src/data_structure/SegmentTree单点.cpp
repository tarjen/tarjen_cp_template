// 用法：
// SegmentTree<> tr(4);  // 初值 0，管理闭区间 [0,4]。
// tr.update(2, 7);  // 将位置 2 赋为 7，不是加 7。
// ll sum = tr.query(1, 3);  // 区间和为 7。
// int p = tr.min_right(0, 7);  // 从 0 开始累加首次达到 7 的位置为 2。
// max_left(r,need) 从右往左找；二分要求元素非负，不存在时返回 -1。
// 也可 SegmentTree tr(vector<ll>{1,2,3})，此时范围是 [0,2]。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
template <class T = ll>
struct SegmentTree {
    struct Node {
        int l, r;
        T res = 0;
    };
    int n;  // 元素个数
    vector<Node> a;
    void pushup(int i) {
        if (a[i].l == a[i].r) return;
        a[i].res = a[i * 2].res + a[i * 2 + 1].res;
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
    void update(int i, int x, T w) {
        if (a[i].r < x || a[i].l > x) return;
        if (a[i].l >= x && a[i].r <= x) {
            a[i].res = w;
            return;
        }
        update(i * 2, x, w);
        update(i * 2 + 1, x, w);
        pushup(i);
    }
    T query(int i, int l, int r) {
        if (a[i].r < l || a[i].l > r || l > r) return 0;
        if (a[i].l >= l && a[i].r <= r) {
            return a[i].res;
        }
        return query(i * 2, l, r) + query(i * 2 + 1, l, r);
    }
    int min_right(int qL, T& nowsum, T querysum,
                  int i) {  // 从左往右第一个>=sum的位置
        if (a[i].r < qL) return -1;
        if (qL <= a[i].l) {
            T ss = nowsum + a[i].res;
            if (ss < querysum) {
                nowsum = ss;
                return -1;
            }
            if (a[i].l == a[i].r) return a[i].l;
        }
        int pos = min_right(qL, nowsum, querysum, i * 2);
        if (pos != -1) return pos;
        return min_right(qL, nowsum, querysum, 2 * i + 1);
    }
    int max_left(int qR, T& nowsum, T querysum,
                 int i) {  // 从右往左第一个>=sum的位置
        if (a[i].l > qR) return -1;
        if (qR >= a[i].r) {
            T ss = nowsum + a[i].res;
            if (ss < querysum) {
                nowsum = ss;
                return -1;
            }
            if (a[i].l == a[i].r) return a[i].r;
        }
        int pos = max_left(qR, nowsum, querysum, i * 2 + 1);
        if (pos != -1) return pos;
        return max_left(qR, nowsum, querysum, i * 2);
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
    void update(int x, T w) {
        assert(n > 0 && 0 <= x && x < n);
        update(1, x, w);
    }
    T query(int l, int r) {
        assert(n > 0 && 0 <= l && l <= n && -1 <= r && r < n);
        return query(1, l, r);
    }
    // 二分要求元素非负、need>0，不存在返回-1。
    int min_right(int l, T need) {
        assert(n > 0 && 0 <= l && l <= n && need > 0);
        T sum = 0;
        return min_right(l, sum, need, 1);
    }
    int max_left(int r, T need) {
        assert(n > 0 && -1 <= r && r < n && need > 0);
        T sum = 0;
        return max_left(r, sum, need, 1);
    }
};
