#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
struct Splay {
    int val[maxn];
    int c[maxn][2];
    int siz[maxn];
    int w[maxn];
    int cnt, r = 0;
    void update(int i) { siz[i] = siz[c[i][1]] + siz[c[i][0]] + 1; }
    int newnode(int x) {
        cnt++;
        val[cnt] = x;
        w[cnt] = rand();
        siz[cnt] = 1;
        return cnt;
    }
    void split(int &x, int &y, int i, int v) {
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
    int th(int i, int v) {
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
        split(x, z, x, v - 1);
        z = merge(c[z][0], c[z][1]);
        r = merge(x, merge(z, y));
    }
    int queryrk(int v) {  // 定义排名为比当前数小的数的个数 +1 查询 v 的排名。
        int x, y;
        split(x, y, r, v - 1);
        int ans = siz[x] + 1;
        r = merge(x, y);
        return ans;
    }
    int querynum(int v) {  // 查询排名为 v 的数
        return th(r, v);
    }
    int query_pre(int v) {  // 求 v 的前驱（前驱定义为小于 v，且最大的数）
        int x, y;
        split(x, y, r, v - 1);
        int i = x;
        while (c[i][1]) i = c[i][1];
        int ans = val[i];
        r = merge(x, y);
        return ans;
    }
    int query_suf(int v) {  // 求 v 的前驱（前驱定义为小于 v，且最大的数）
        int x, y;
        split(x, y, r, v);
        int i = y;
        while (c[i][0]) i = c[i][0];
        int ans = val[i];
        r = merge(x, y);
        return ans;
    }
} sol;
int n;
int main() {
    scanf("%d", &n);
    int r = 0;
    while (n--) {
        int opt;
        scanf("%d", &opt);
        if (opt == 1) {
            int v;
            scanf("%d", &v);
            sol.insert(v);
        }
        if (opt == 2) {
            int v;
            scanf("%d", &v);
            sol.del(v);
        }
        if (opt == 3) {
            int v;
            scanf("%d", &v);
            printf("%d\n", sol.queryrk(v));
        }
        if (opt == 4) {
            int v;
            scanf("%d", &v);
            printf("%d\n", sol.querynum(v));
        }
        if (opt == 5) {
            int v;
            scanf("%d", &v);
            printf("%d\n", sol.query_pre(v));
        }
        if (opt == 6) {
            int v;
            scanf("%d", &v);
            printf("%d\n", sol.query_suf(v));
        }
    }
}