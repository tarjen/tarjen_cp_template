#include <bits/stdc++.h>
using namespace std;
const int maxn = 10010;

struct LCT {
    int ch[maxn][2], fa[maxn], tag[maxn];

    void clear(int x) { ch[x][0] = ch[x][1] = fa[x] = tag[x] = 0; }

    int getch(int x) { return ch[fa[x]][1] == x; }

    int isroot(int x) { return ch[fa[x]][0] != x && ch[fa[x]][1] != x; }

    void pushdown(int x) {
        if (tag[x]) {
        if (ch[x][0]) swap(ch[ch[x][0]][0], ch[ch[x][0]][1]), tag[ch[x][0]] ^= 1;
        if (ch[x][1]) swap(ch[ch[x][1]][0], ch[ch[x][1]][1]), tag[ch[x][1]] ^= 1;
        tag[x] = 0;
        }
    }

    void update(int x) {
        if (!isroot(x)) update(fa[x]);
        pushdown(x);
    }

    void rotate(int x) {
        int y = fa[x], z = fa[y], chx = getch(x), chy = getch(y);
        fa[x] = z;
        if (!isroot(y)) ch[z][chy] = x;
        ch[y][chx] = ch[x][chx ^ 1];
        fa[ch[x][chx ^ 1]] = y;
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
        while (ch[x][0]) x = ch[x][0];
        splay(x);
        return x;
    }
/*------------------------------------------------------*/
    bool query(int x,int y){//查询是否为同一颗树
        return find(x)==find(y);
    }
    void addedge(int x,int y){
        if (find(x) != find(y)) makeroot(x), fa[x] = y;
    }
    void deledge(int x,int y){
        makeroot(x);
        access(y);
        splay(y);
        if (ch[y][0] == x && !ch[x][1]) ch[y][0] = fa[x] = 0;
    }
} st;

int n, q, x, y;
char op[maxn];

int main() {
    scanf("%d%d", &n, &q);
    while (q--) {
        scanf("%s%d%d", op, &x, &y);
        if (op[0] == 'Q') {
            if (st.query(x,y))
            printf("Yes\n");
        else
            printf("No\n");
        }
        if (op[0] == 'C')st.addedge(x,y);
        if (op[0] == 'D')st.deledge(x,y);
    }
    return 0;
}