// 手抄版：沿用原算法与类封装；//? 标记为按需抄写。
// 用法：
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
struct Treearray {
    int n;
    vector<ll> c;
    Treearray(int n) : n(n), c(n + 1) {}
    void set_n(int size) {
        n = size;
        c.assign(n + 1, 0);
    }
    static int lowbit(int x) { return x & -x; }
    void update(int i, ll k) {
        //? assert(i >= 1);
        for (; i <= n; i += lowbit(i)) c[i] += k;
    }
    ll getsum(int i) const {
        ll res = 0;
        for (; i > 0; i -= lowbit(i)) res += c[i];
        return res;
    }
    ll query(int l, int r) const { return getsum(r) - getsum(l - 1); }
};
