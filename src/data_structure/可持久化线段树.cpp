#include <bits/stdc++.h>
using namespace std;
const int maxn = 1.5e6;  // 数据范围
int n, m;
struct Persistent_SegmentTree {
    struct node {
        int l, r, ls, rs, tag;
        node() { l = 0, r = 0, ls = 0, rs = 0, tag = 0; }
    };
    int tot = 0;
    vector<node> a;
    void init() {
        a.clear();
        a.push_back(node());
    }
    int nnode(int id = 0) {
        if (id)
            a.push_back(a[id]);
        else
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
    int addtag(int x, int w) {
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
    int update(int x, int l, int r, int w) {
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
    int val(int x, int i) {
        if (a[x].r < i || a[x].l > i) return 0;
        if (a[x].l == a[x].r) return a[x].tag;
        return a[x].tag + val(a[x].ls, i) + val(a[x].rs, i);
    }
};
Persistent_SegmentTree tri;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int lastans = 0;
    int n;
    cin >> n;
    int q;
    cin >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    vector<int> nd(n + 2);
    nd[n + 1] = tri.build(1, n);
    vector<int> pr(n + 1);
    for (int i = n; i >= 1; i--) {
        if (pr[a[i]] == 0) {
            nd[i] = tri.update(nd[i + 1], i, n, 1);
        } else {
            nd[i] = tri.merge(nd[i + 1], nd[pr[a[i]] + 1], pr[a[i]] - 1);
            nd[i] = tri.update(nd[i], i, pr[a[i]] - 1, 1);
        }
        pr[a[i]] = i;
        // cout<<"nd[i]="<<nd[i]<<endl;
    }
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=n;j++)cout<<tri.val(nd[i],j)<<" \n"[j==n];
    // }
    while (q--) {
        int l, r;
        cin >> l >> r;
        l ^= lastans, r ^= lastans;
        // cout<<"l="<<l<<" r="<<r<<endl;
        lastans = tri.val(nd[l], r);
        cout << lastans << "\n";
    }
    return 0;
}
