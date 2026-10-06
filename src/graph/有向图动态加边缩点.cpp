// 用法：
// vector<pair<int,int>> additions = {{1,2}, {2,1}, {2,3}};
// IncrementalSCC tr(3, additions);  // 节点 1base，按给定顺序逐条加有向边。
// ll after_second = tr.anss[1];  // 加入前两条边后结果为 4。
// anss[i] 为加完第 i 条边后的统计；时间位置 0base。
// 统计的是大小 >1 的强连通分量大小平方和，不是分量个数。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
using Edges = vector<tuple<int, int, int>>;
struct IncrementalSCC {
    int n, q;
    vector<int> f, siz, ti, col, dfn, low;
    vector<long long> anss;
    long long ans = 0;
    int num = 0, dfstime = 0;
    Edges edge;
    stack<int> s;
    vector<vector<int>> ve;
    IncrementalSCC(int n, const vector<pair<int, int>>& additions)
        : n(n),
          q(additions.size()),
          f(n + 1),
          siz(n + 1, 1),
          ti(q, -1),
          col(n + 1),
          dfn(n + 1),
          low(n + 1),
          anss(q),
          ve(n + 1) {
        iota(f.begin(), f.end(), 0);
        for (int i = 0; i < q; i++)
            edge.emplace_back(additions[i].first, additions[i].second, i);
        solve(0, q, edge);
        iota(f.begin(), f.end(), 0);
        fill(siz.begin(), siz.end(), 1);
        ans = 0;
        vector<int> order(q);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(),
             [&](int x, int y) { return ti[x] < ti[y]; });
        for (int i : order)
            if (ti[i] >= 0) {
                merge(get<0>(edge[i]), get<1>(edge[i]));
                anss[ti[i]] = ans;
            }
        for (int i = 1; i < q; i++) anss[i] = max(anss[i], anss[i - 1]);
    }
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
    void color(Edges& edges, Edges& e1, Edges& e2, int mid) {
        for (auto& [x, y, t] : edges)
            if (x != y) ve[x].push_back(y);
        for (auto& [x, y, t] : edges)
            if (!dfn[x]) tarjan(x);

        for (auto& [x, y, t] : edges)
            if (x != y) {
                if (col[x] == col[y] && col[x] != 0) {
                    ti[t] = mid;
                    e1.emplace_back(x, y, t);
                } else
                    e2.emplace_back(x, y, t);
            }
        while (!s.empty()) s.pop();
        for (auto& [x, y, t] : edges)
            col[x] = col[y] = dfn[x] = dfn[y] = low[x] = low[y] = 0,
            ve[x].clear();
        num = dfstime = 0;
    }
    void solve(int l, int r, Edges edges) {
        // cout<<"solve l="<<l<<" r="<<r<<" ::";;for(auto
        // [x,y,t]:edges)cout<<t<<"
        // ";;cout<<endl;
        if (l > r) return;
        if (l == r) {
            if (l == q) return;
        }
        int mid = (l + r) / 2;
        Edges e, e1, e2;
        for (auto& [x, y, t] : edges)
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
};
