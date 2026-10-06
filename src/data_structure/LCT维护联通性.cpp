// 用法：
// LCT tr(3);  // 节点 1base，初始没有边；维护森林连通性。
// tr.addedge(1, 2);
// tr.addedge(2, 3);
// bool connected = tr.query(1, 3);  // true。
// tr.deledge(2, 3);  // 删除已有边后 query(1,3) 为 false。
#include <bits/stdc++.h>
using namespace std;

struct LCT {
    vector<array<int, 2>> ch;
    vector<int> fa, tag;
    explicit LCT(int n) : ch(n + 1), fa(n + 1), tag(n + 1) {}

    void clear(int x) { ch[x][0] = ch[x][1] = fa[x] = tag[x] = 0; }

    int getch(int x) { return ch[fa[x]][1] == x; }

    int isroot(int x) { return ch[fa[x]][0] != x && ch[fa[x]][1] != x; }

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
    }

    void splay(int x) {
        update(x);
        for (int f = fa[x]; f = fa[x], !isroot(x); rotate(x))
            if (!isroot(f)) rotate(getch(x) == getch(f) ? f : x);
    }

    void access(int x) {
        for (int f = 0; x; f = x, x = fa[x]) splay(x), ch[x][1] = f;
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
        if (ch[y][0] == x && !ch[x][1]) ch[y][0] = fa[x] = 0;
    }
};
