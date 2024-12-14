#include <bits/stdc++.h>
using namespace std;
struct SegmentMap {
    map<int, int> ma;
    int sum = 0;
    int n;
    SegmentMap(int _n = 0) {
        n = _n;
        ma[1] = 0;
        ma[n + 1] = -1;
    }
    void del(int l, int r, int x) {  // 减去当前 (l,r,x) 的贡献
        sum -= (r - l + 1) * x;
    }
    void add(int l, int r, int x) {  // 加上当前 (l,r,x) 的贡献
        sum += (r - l + 1) * x;
    }
    void split(int x) {
        auto t = prev(ma.upper_bound(x))->second;
        ma[x] = t;
    }
    void update(int l, int r, auto&& T) {
        split(l);
        split(r + 1);
        auto it = prev(ma.upper_bound(l));
        int pr = -1;
        while (it->first <= r) {
            int nowl = it->first, nowr = next(it)->first - 1;
            int x = it->second;
            del(nowl, nowr, x);
            add(nowl, nowr, T(x));
            if (l != nowl && pr == T(x))
                it = ma.erase(it);
            else {
                it->second = T(x);
                it = next(it);
            }
            pr = T(x);
        }
        if (it->first != n + 1 && it->second == pr) ma.erase(it);
        if (l != 1) {
            it = ma.lower_bound(l);
            if (prev(it)->second == it->second) ma.erase(it);
        }
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    SegmentMap sol(n);
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int l, r;
            cin >> l >> r;
            sol.update(l, r, [](int x) { return (int)sqrt(x); });
        } else {
            int l, r, x;
            cin >> l >> r >> x;
            sol.update(l, r, [x](int y) { return x; });
        }
        cout << sol.sum << "\n";
    }
}