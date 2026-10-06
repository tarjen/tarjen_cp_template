// 1base；Treearray tr(n); tr.update(i,k); tr.query(l,r); 初值为0。
#include <bits/stdc++.h>
using namespace std;

struct Treearray {
    int n;
    vector<long long> c;
    explicit Treearray(int n) : n(n), c(n + 1) {}
    void set_n(int size) {
        n = size;
        c.assign(n + 1, 0);
    }
    static int lowbit(int x) { return x & -x; }
    void update(int i, long long k) {
        assert(i >= 1);
        for (; i <= n; i += lowbit(i)) c[i] += k;
    }
    long long getsum(int i) const {
        long long res = 0;
        for (; i > 0; i -= lowbit(i)) res += c[i];
        return res;
    }
    long long query(int l, int r) const { return getsum(r) - getsum(l - 1); }
};
