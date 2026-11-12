// 手抄版：沿用原算法与类封装；//? 标记为按需抄写。
// 用法：
// 数组构造：RangeTreearray tr(vector<ll>{0,1,2,3})，第 0 格不用。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
struct RangeTreearray {
    int n;
    vector<ll> tree1, tree2;
    RangeTreearray(int n) : n(n), tree1(n + 1), tree2(n + 1) {}
    // 输入a为1base，a[0]不参与计算；差分沿父节点累加，O(n)建树。
    RangeTreearray(const vector<ll>& a)
        : RangeTreearray((int)a.size() - 1) {
        for (int i = 1; i <= n; i++) {
            ll d = a[i] - (i == 1 ? 0 : a[i - 1]);
            tree1[i] += d, tree2[i] += (i - 1) * d;
            int j = i + (i & -i);
            if (j <= n) tree1[j] += tree1[i], tree2[j] += tree2[i];
        }
    }
    void add(int x, ll k) {
        //? assert(x >= 1);
        for (int i = x; i <= n; i += i & -i)
            tree1[i] += k, tree2[i] += (x - 1) * k;
    }
    void update(int l, int r, ll k) {
        if (l <= r) add(l, k), add(r + 1, -k);
    }
    ll getsum(int x) const {
        ll ans = 0;
        for (int i = x; i > 0; i -= i & -i) ans += tree1[i] * x - tree2[i];
        return ans;
    }
    ll query(int l, int r) const { return getsum(r) - getsum(l - 1); }
};
