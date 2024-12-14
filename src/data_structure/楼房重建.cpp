#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;
struct Node {
    int l, r, len;
    int mx;
};
struct SegmentTree {
    Node a[maxn * 4];
    int qry(int x, int i) {  // 起点大过x
        if (a[i].l == a[i].r) {
            return a[i].mx > x;
        }
        if (a[i * 2].mx > x) {
            return a[i].len - a[i * 2].len + qry(x, 2 * i);
        } else
            return qry(x, 2 * i + 1);
    }
    void pushup(int i) {
        if (a[i].l == a[i].r) return;
        a[i].len = a[i * 2].len + qry(a[i * 2].mx, i * 2 + 1);
        a[i].mx = max(a[i * 2].mx, a[i * 2 + 1].mx);
    }
    void build(int i, int l, int r) {
        a[i].l = l, a[i].r = r;
        a[i].len = 0;
        a[i].mx = {0, 1};
        if (l >= r) return;
        int mid = (l + r) / 2;
        build(i * 2, l, mid);
        build(i * 2 + 1, mid + 1, r);
        pushup(i);
    }
    void update(int i, int x, int w) {
        if (a[i].r < x || a[i].l > x) return;
        if (a[i].l >= x && a[i].r <= x) {
            a[i].mx = w;
            a[i].len = 1;
            return;
        }
        update(i * 2, x, w);
        update(i * 2 + 1, x, w);
        pushup(i);
    }
    int query() { return a[1].len; }
};
SegmentTree tri;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    tri.build(1, 1, n);
    while (m--) {
        int x, y;
        cin >> x >> y;
        tri.update(1, x, int(y, x));
        cout << tri.query() << "\n";
    }
}