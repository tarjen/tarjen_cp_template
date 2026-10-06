// 1base；Persistent_SegmentTree tr(n); append(version,l,r,w); query(version,i);
// 版本0全为0。
#include <bits/stdc++.h>
using namespace std;
struct Persistent_SegmentTree {
    struct node {
        int l, r, ls, rs;
        long long tag;
        node() { l = 0, r = 0, ls = 0, rs = 0, tag = 0; }
    };
    int n;
    vector<int> root;
    explicit Persistent_SegmentTree(int n) : n(n) {
        assert(n >= 1);
        init();
        root.push_back(build(1, n));
    }
    vector<node> a;
    void init() {
        root.clear();
        a.clear();
        a.push_back(node());
    }
    int nnode(int id = 0) {
        if (id) {
            node copy = a[id];
            a.push_back(copy);
        } else
            a.push_back(node());
        return a.size() - 1;
    }
    int build(int l, int r) {
        int now = nnode();
        a[now].l = l, a[now].r = r;
        if (l == r) return now;
        int mid = (l + r) / 2;
        a[now].ls = build(l, mid);
        a[now].rs = build(mid + 1, r);
        return now;
    }
    int addtag(int x, long long w) {
        int now = nnode(x);
        a[now].tag += w;
        return now;
    }
    // you can't pushdown a leave in your code
    int pushdown(int x) {
        int now = nnode(x);
        if (a[now].tag) {
            a[now].ls = addtag(a[now].ls, a[now].tag);
            a[now].rs = addtag(a[now].rs, a[now].tag);
            a[now].tag = 0;
        }
        return now;
    }
    int update(int x, int l, int r, long long w) {
        // cout<<"update x="<<x<<" l="<<l<<" r="<<r<<" w="<<w<<endl;
        if (a[x].l > r || a[x].r < l) return x;
        if (l <= a[x].l && a[x].r <= r) return addtag(x, w);
        int now = pushdown(x);
        a[now].ls = update(a[now].ls, l, r, w);
        a[now].rs = update(a[now].rs, l, r, w);
        return now;
    }
    int merge(int x, int y, int p) {  // x[1-p] y[p+1-~]
        // cout<<"merge x="<<x<<" y="<<y<<" p="<<p<<endl;
        if (a[x].r <= p) return x;
        if (a[y].l > p) return y;
        int xx = pushdown(x), yy = pushdown(y);
        int now = nnode(xx);
        a[now].ls = merge(a[xx].ls, a[yy].ls, p);
        a[now].rs = merge(a[xx].rs, a[yy].rs, p);
        return now;
    }
    long long val(int x, int i) {
        if (a[x].r < i || a[x].l > i) return 0;
        if (a[x].l == a[x].r) return a[x].tag;
        return a[x].tag + val(a[x].ls, i) + val(a[x].rs, i);
    }
    int append(int version, int l, int r, long long w) {
        int p = update(root[version], l, r, w);
        root.push_back(p);
        return (int)root.size() - 1;
    }
    int splice(int x, int y, int p) {
        int rt = merge(root[x], root[y], p);
        root.push_back(rt);
        return (int)root.size() - 1;
    }
    long long query(int version, int i) { return val(root[version], i); }
};
