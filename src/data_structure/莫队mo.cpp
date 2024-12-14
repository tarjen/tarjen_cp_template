#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int n, m, a[N], block, ans[N], now, cnt[N];
struct node {
    int l, r, i;
    friend bool operator<(const node a, const node b) {
        if ((a.l / block) == (b.l / block))
            return ((a.l / block % 2) ? a.r > b.r : a.r < b.r);
        else
            return a.l < b.l;
    }
} q[N];
void add(int x) {}
void del(int x) {}
int main() {
    block = max(1, n / sqrt(m));
    sort(q + 1, q + 1 + m);
    int l = 1, r = 0;
    for (int i = 1; i <= m; i++) {
        while (l < q[i].l) del(l++);
        while (l > q[i].l) add(--l);
        while (r < q[i].r) add(++r);
        while (r > q[i].r) del(r--);
        ans[q[i].i] = now;
    }
    for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
    return 0;
}
