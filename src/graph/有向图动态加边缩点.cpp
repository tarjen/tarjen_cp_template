#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
using Edges = vector<tuple<int, int, int>>;
const int maxn = 4e5 + 10;
int f[maxn], siz[maxn];
ll ans = 0;
int getf(int x) {
    if (x == f[x])
        return x;
    else
        return f[x] = getf(f[x]);
}
void merge(int x, int y) {
    x = getf(x), y = getf(y);
    if (x == y) return;
    if (siz[x] > 1) ans -= (ll)siz[x] * siz[x];
    if (siz[y] > 1) ans -= (ll)siz[y] * siz[y];
    f[x] = y;
    siz[y] += siz[x];
    ans += (ll)siz[y] * siz[y];
}
int n, m, q;
int ti[maxn];
ll anss[maxn];
Edges edge;
stack<int> s;
vector<int> ve[maxn];
int col[maxn], num, dfn[maxn], low[maxn], dfstime;
void tarjan(int u) {
    s.push(u);
    dfn[u] = low[u] = ++dfstime;
    for (auto v : ve[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (!col[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        col[u] = ++num;
        while (s.top() != u) {
            col[s.top()] = num;
            s.pop();
        }
        s.pop();
    }
}
void color(Edges &edges, Edges &e1, Edges &e2, int mid) {
    for (auto &[x, y, t] : edges)
        if (x != y) ve[x].push_back(y);
    for (auto &[x, y, t] : edges)
        if (!dfn[x]) tarjan(x);
    for (auto &[x, y, t] : edges)
        if (x != y) {
        }

    for (auto &[x, y, t] : edges)
        if (x != y) {
            if (col[x] == col[y] && col[x] != 0) {
                ti[t] = mid;
                e1.emplace_back(x, y, t);
            } else
                e2.emplace_back(x, y, t);
        }
    while (!s.empty()) s.pop();
    for (auto &[x, y, t] : edges)
        col[x] = col[y] = dfn[x] = dfn[y] = low[x] = low[y] = 0, ve[x].clear();
    num = dfstime = 0;
}
void solve(int l, int r, Edges edges) {
    // cout<<"solve l="<<l<<" r="<<r<<" ::";;for(auto [x,y,t]:edges)cout<<t<<"
    // ";;cout<<endl;
    if (l > r) return;
    if (l == r) {
        if (l == q) return;
    }
    int mid = (l + r) / 2;
    Edges e, e1, e2;
    for (auto &[x, y, t] : edges)
        if (t <= r) {
            x = getf(x), y = getf(y);
            if (t <= mid)
                e.emplace_back(x, y, t);
            else
                e2.emplace_back(x, y, t);
        }
    color(e, e1, e2, mid);
    solve(l, mid - 1, e1);
    for (auto [x, y, t] : e1) merge(x, y);

    solve(mid + 1, r, e2);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    memset(ti, -1, sizeof(ti));
    int n, m, q;
    cin >> n >> m >> q;
    iota(f, f + n + m + 1, 0);
    edge.resize(q);
    for (int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        y += n;
        char c;
        cin >> c;
        if (c == 'R') swap(x, y);
        edge[i] = make_tuple(x, y, i);
        // cout<<"edge["<<i<<"]="<<"("<<x<<","<<y<<")"<<endl;
    }
    solve(0, q, edge);
    iota(f, f + n + m + 1, 0);
    // for(int i=0;i<q;i++)cout<<"ti["<<i<<"]="<<ti[i]<<endl;
    for (int i = 1; i <= n + m; i++) siz[i] = 1;
    vector<int> v(q);
    iota(v.begin(), v.end(), 0);
    sort(v.begin(), v.end(), [&](int x, int y) { return ti[x] < ti[y]; });
    for (auto i : v)
        if (ti[i] >= 0) {
            merge(get<0>(edge[i]), get<1>(edge[i]));
            anss[ti[i]] = ans;
        }
    for (int i = 1; i < q; i++)
        if (anss[i] < anss[i - 1]) anss[i] = anss[i - 1];
    for (int i = 0; i < q; i++) cout << anss[i] << "\n";
}