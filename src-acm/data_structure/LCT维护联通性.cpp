/*
用户要求：LCT 维护点权，支持单点查询和链上点权求和。
实现：辅助 Splay 维护 val/sum，结构变化后 pushup；提供单点赋值与加值。
*/
// 用法：
// LCT tr(3);  // 节点 1base，初始没有边，点权均为 0。
// tr.addedge(1, 2);
// tr.addedge(2, 3);
// bool connected = tr.query(1, 3);  // true。
// tr.point_set(1, 2);  // 点 1 赋值为 2。
// tr.point_add(2, 3);  // 点 2 加上 3。
// ll value = tr.point_sum(2);  // 单点权值为 3。
// ll sum = tr.chain_sum(1, 3);  // 链上点权和为 5，包含两端点。
// tr.deledge(2, 3);  // 删除已有边后 query(1,3) 为 false。
// chain_sum 要求两点连通；点权与和用 ll，修改点权须走 point_set/point_add。
// 连边、断边、点修改、链求和均摊 O(log n)；单点查询 O(1)。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct LCT {
    vector<array<int, 2>> ch;
    vector<int> fa, tag;
    vector<ll> val, sum;
    LCT(int n)
        : ch(n + 1), fa(n + 1), tag(n + 1), val(n + 1), sum(n + 1) {}

    void clear(int x) {  // 仅用于重置孤立点。
        ch[x][0] = ch[x][1] = fa[x] = tag[x] = 0;
        val[x] = sum[x] = 0;
    }

    int getch(int x) { return ch[fa[x]][1] == x; }

    int isroot(int x) { return ch[fa[x]][0] != x && ch[fa[x]][1] != x; }

    void pushup(int x) { sum[x] = sum[ch[x][0]] + val[x] + sum[ch[x][1]]; }

    void pushdown(int x) {
        if (tag[x]) {
            if (ch[x][0])
                swap(ch[ch[x][0]][0], ch[ch[x][0]][1]), tag[ch[x][0]] ^= 1;
            if (ch[x][1])
                swap(ch[ch[x][1]][0], ch[ch[x][1]][1]), tag[ch[x][1]] ^= 1;
            tag[x] = 0;
        }
    }

    void update(int x) {
        vector<int> path{x};
        while (!isroot(x)) x = fa[x], path.push_back(x);
        for (auto it = path.rbegin(); it != path.rend(); ++it) pushdown(*it);
    }

    void rotate(int x) {
        int y = fa[x], z = fa[y], chx = getch(x), chy = getch(y);
        fa[x] = z;
        if (!isroot(y)) ch[z][chy] = x;
        ch[y][chx] = ch[x][chx ^ 1];
        if (ch[x][chx ^ 1]) fa[ch[x][chx ^ 1]] = y;
        ch[x][chx ^ 1] = y;
        fa[y] = x;
        pushup(y); pushup(x);
    }

    void splay(int x) {
        update(x);
        for (int f = fa[x]; f = fa[x], !isroot(x); rotate(x))
            if (!isroot(f)) rotate(getch(x) == getch(f) ? f : x);
    }

    void access(int x) {
        for (int f = 0; x; f = x, x = fa[x]) {
            splay(x);
            ch[x][1] = f;
            pushup(x);
        }
    }

    void makeroot(int x) {
        access(x);
        splay(x);
        swap(ch[x][0], ch[x][1]);
        tag[x] ^= 1;
    }

    int find(int x) {
        access(x);
        splay(x);
        while (true) {
            pushdown(x);
            if (!ch[x][0]) break;
            x = ch[x][0];
        }
        splay(x);
        return x;
    }
    /*------------------------------------------------------*/
    bool query(int x, int y) {  // 查询是否为同一颗树
        return find(x) == find(y);
    }
    void addedge(int x, int y) {
        if (find(x) != find(y)) makeroot(x), fa[x] = y;
    }
    void deledge(int x, int y) {
        makeroot(x);
        access(y);
        splay(y);
        if (ch[y][0] == x && !ch[x][1]) {
            ch[y][0] = fa[x] = 0;
            pushup(y);
        }
    }
    void point_set(int x, ll v) {
        access(x);
        splay(x);
        val[x] = v;
        pushup(x);
    }
    void point_add(int x, ll v) {
        access(x);
        splay(x);
        val[x] += v;
        pushup(x);
    }
    ll point_sum(int x) const { return val[x]; }
    ll chain_sum(int x, int y) {  // 两点必须连通，包含两端点。
        assert(query(x, y));
        makeroot(x);
        access(y);
        splay(y);
        return sum[y];
    }
};
