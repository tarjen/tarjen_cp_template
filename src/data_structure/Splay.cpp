// Splay t; 实际保留FHQ
// Treap算法；前驱/后继不存在时返回nullopt；节点池自动增长。
#include <bits/stdc++.h>
using namespace std;
struct Splay {
    vector<int> val{0}, siz{0};
    vector<array<int, 2>> c{array<int, 2>{}};
    vector<unsigned> w{0};
    int cnt = 0, r = 0;
    mt19937 random;
    explicit Splay(int reserve_nodes = 0, unsigned seed = 712367821)
        : random(seed) {
        val.reserve(reserve_nodes + 1);
        siz.reserve(reserve_nodes + 1);
        c.reserve(reserve_nodes + 1);
        w.reserve(reserve_nodes + 1);
    }
    void update(int i) {
        if (i) siz[i] = siz[c[i][0]] + siz[c[i][1]] + 1;
    }
    int newnode(int x) {
        val.push_back(x);
        siz.push_back(1);
        c.push_back({});
        w.push_back(random());
        return ++cnt;
    }
    void split(int& x, int& y, int i, long long v) {
        if (!i) {
            x = y = 0;
            return;
        }
        if (val[i] <= v) {
            x = i;
            split(c[i][1], y, c[i][1], v);
        } else {
            y = i;
            split(x, c[i][0], c[i][0], v);
        }
        update(i);
        return;
    }
    int merge(int x, int y) {
        if (!x || !y) return x + y;
        if (w[x] < w[y]) {
            c[x][1] = merge(c[x][1], y);
            update(x);
            return x;
        } else {
            c[y][0] = merge(x, c[y][0]);
            update(y);
            return y;
        }
    }
    int th(int i, long long v) {
        if (siz[c[i][0]] + 1 == v) return val[i];
        if (v <= siz[c[i][0]])
            return th(c[i][0], v);
        else
            return th(c[i][1], v - siz[c[i][0]] - 1);
    }
    /*-----------------------------------------------*/
    void insert(int v) {  // 插入一个大小为v的数
        int x, y;
        split(x, y, r, v);
        r = merge(x, merge(newnode(v), y));
    }
    void del(int v) {  // 删除 v 数（若有多个相同的数，只删除一个）
        int x, y, z;
        split(x, y, r, v);
        split(x, z, x, (long long)v - 1);
        z = merge(c[z][0], c[z][1]);
        r = merge(x, merge(z, y));
    }
    int queryrk(int v) {  // 定义排名为比当前数小的数的个数 +1 查询 v 的排名。
        int x, y;
        split(x, y, r, (long long)v - 1);
        int ans = siz[x] + 1;
        r = merge(x, y);
        return ans;
    }
    int querynum(int v) {  // 查询排名为 v 的数
        assert(1 <= v && v <= siz[r]);
        return th(r, v);
    }
    optional<int> query_pre(
        int v) {  // 求 v 的前驱（前驱定义为小于 v，且最大的数）
        int x, y;
        split(x, y, r, (long long)v - 1);
        int i = x;
        while (c[i][1]) i = c[i][1];
        optional<int> ans = i ? optional<int>(val[i]) : nullopt;
        r = merge(x, y);
        return ans;
    }
    optional<int> query_suf(
        int v) {  // 求 v 的前驱（前驱定义为小于 v，且最大的数）
        int x, y;
        split(x, y, r, v);
        int i = y;
        while (c[i][0]) i = c[i][0];
        optional<int> ans = i ? optional<int>(val[i]) : nullopt;
        r = merge(x, y);
        return ans;
    }
};
