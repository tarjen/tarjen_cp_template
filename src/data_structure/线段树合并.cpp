#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e5 + 10;
typedef long long ll;
void gmax(ll& x, ll y) {
    if (y > x) x = y;
}
struct SegmentTree {
    struct Node {
        int ls, rs;
        ll tag = 0, res0 = 0, res1 = 0;  // res0 small res1 bigger
        void add(ll v) { tag += v, res0 += v, res1 += v; }
    };
    vector<Node> a;
    SegmentTree() {
        a.clear();
        a.emplace_back();
    }
    int newnode() {
        a.emplace_back();
        return (int)a.size() - 1;
    }
    void pushup(int i) {
        a[i].res0 = a[i].res1 = 0;
        if (a[i].ls) {
            gmax(a[i].res0, a[a[i].ls].res0);
            gmax(a[i].res1, a[a[i].ls].res1);
        }
        if (a[i].rs) {
            gmax(a[i].res0, a[a[i].rs].res0);
            gmax(a[i].res1, a[a[i].rs].res1);
        }
    }
    void pushdown(int i) {
        if (a[i].ls) a[a[i].ls].add(a[i].tag);
        if (a[i].rs) a[a[i].rs].add(a[i].tag);
        a[i].tag = 0;
    }
    int update(int i, int L, int R, int x, ll v) {
        if (i == 0) i = newnode();
        if (L == R) {
            a[i].res0 = v, a[i].res1 = 0;
        } else {
            pushdown(i);
            int mid = (L + R) / 2;
            if (x <= mid)
                a[i].ls = update(a[i].ls, L, mid, x, v);
            else
                a[i].rs = update(a[i].rs, mid + 1, R, x, v);
            pushup(i);
        }
        return i;
    }
    int merge(int i, int j, int L, int R, ll adi, ll adj, ll& ans) {
        if (!i || !j) {
            if (i == 0) {
                a[j].add(adj);
            }
            if (j == 0) {
                a[i].add(adi);
            }
            return i | j;
        }
        pushdown(i);
        pushdown(j);
        if (a[i].ls && a[j].rs) gmax(ans, a[a[i].ls].res0 + a[a[j].rs].res1);
        if (a[j].ls && a[i].rs) gmax(ans, a[a[j].ls].res0 + a[a[i].rs].res1);
        int mid = (L + R) / 2;
        a[i].ls = merge(a[i].ls, a[j].ls, L, mid, adi, adj, ans);
        a[i].rs = merge(a[i].rs, a[j].rs, mid + 1, R, adi, adj, ans);
        pushup(i);
        return i;
    }
} tri;
