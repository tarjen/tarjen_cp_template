// 思路：动态维护直线凸包，单点查询 min(k*x+b)。
// 来源：KACTL LineContainer，Simon Lindholm，CC0。
// https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/LineContainer.h
// 用法：
// LineContainer hull;
// hull.add(2, 3);  // 插入 y=2x+3，内部取负转为维护上凸壳。
// hull.add(-1, 4);
// ll ans = hull.query(2);  // min(7,2)=2，查询前须非空。
// hull.clear();  // 清空后可重新插入。
// 插入、查询顺序均任意；仅支持插入，不能删除指定直线。
// 插入均摊 O(log n)，查询 O(log n)，空间 O(n)；整数版。
// 取负、差值、除法、k*x+b 均须不溢出 ll；x 和有限交点须严格处于 (-inf,inf)。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
struct LineContainer {
    struct Line {
        mutable ll k, b, p;  // 上凸壳中本直线最优的最右整数横坐标 p。
        bool operator<(const Line& o) const { return k < o.k; }
        bool operator<(ll x) const { return p < x; }
    };
    multiset<Line, less<>> hull;
    using iterator = multiset<Line, less<>>::iterator;
    static constexpr ll inf = LLONG_MAX;
    ll div(ll a, ll b) {  // 向下取整，不能直接用截断到 0 的整数除法。
        return a / b - ((a ^ b) < 0 && a % b);
    }
    bool isect(iterator x, iterator y) {
        if (y == hull.end()) return x->p = inf, false;
        if (x->k == y->k) x->p = x->b > y->b ? inf : -inf;
        else x->p = div(y->b - x->b, x->k - y->k);
        return x->p >= y->p;
    }
    void add(ll k, ll b) {
        auto z = hull.insert({-k, -b, 0}), y = z++, x = y;
        while (isect(y, z)) z = hull.erase(z);
        if (x != hull.begin() && isect(--x, y)) isect(x, y = hull.erase(y));
        while ((y = x) != hull.begin() && (--x)->p >= y->p)
            isect(x, hull.erase(y));
    }
    ll query(ll x) const {
        assert(!hull.empty());
        auto l = *hull.lower_bound(x);
        return -(l.k * x + l.b);
    }
    bool empty() const { return hull.empty(); }
    void clear() { hull.clear(); }
};
