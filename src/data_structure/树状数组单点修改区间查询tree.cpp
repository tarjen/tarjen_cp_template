// 用法：
// Treearray tr(5);  // 位置 [1,5]，初值 0。
// tr.update(2, 3);  // 位置 2 加 3，不是赋值。
// ll sum = tr.query(1, 4);  // 闭区间和为 3。
// ll prefix = tr.getsum(2);  // [1,2] 的和为 3。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
struct Treearray {
    int n;
    vector<ll> c;
    explicit Treearray(int n) : n(n), c(n + 1) {}
    void set_n(int size) {
        n = size;
        c.assign(n + 1, 0);
    }
    static int lowbit(int x) { return x & -x; }
    void update(int i, ll k) {
        assert(i >= 1);
        for (; i <= n; i += lowbit(i)) c[i] += k;
    }
    ll getsum(int i) const {
        ll res = 0;
        for (; i > 0; i -= lowbit(i)) res += c[i];
        return res;
    }
    ll query(int l, int r) const { return getsum(r) - getsum(l - 1); }
};
