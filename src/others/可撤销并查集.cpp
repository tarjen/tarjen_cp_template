int fa[N * 2], sz[N * 2], st[N * 2], tp = 0;
int find(int x) { return fa[x] == x ? x : find(fa[x]); }
bool merge(int x, int y) {
    // if (test) cout << "merge x=" << x << " y=" << y << endl;
    int p = find(x), q = find(y);
    if (p == q) return false;
    if (sz[p] < sz[q]) swap(p, q);
    st[++tp] = q, fa[q] = p, sz[p] += sz[q];
    return true;
}
void del() {
    if (!tp) return;
    int y = st[tp--];
    sz[fa[y]] -= sz[y], fa[y] = y;
}