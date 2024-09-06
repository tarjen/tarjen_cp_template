#include <bits/stdc++.h>
using namespace std;
const int N = 200 + 5, M = 2e4 + N;
struct flow {
  int cnt = 1, hd[N], nxt[M << 1], to[M << 1], limit[M << 1], cst[M << 1];
  void add(int u, int v, int w, int c) {
    nxt[++cnt] = hd[u], hd[u] = cnt, to[cnt] = v, limit[cnt] = w, cst[cnt] = c;
    nxt[++cnt] = hd[v], hd[v] = cnt, to[cnt] = u, limit[cnt] = 0, cst[cnt] = -c;
  }
  int fl[N], fr[N], dis[N], in[N];
  pair<int, int> mincost(int s, int t) {
    int flow = 0, cost = 0;
    while (1) {
      queue<int> q;
      memset(dis, 0x3f, sizeof(dis));
      q.push(s), fl[s] = 1e9, dis[s] = 0;
      while (!q.empty()) {
        int t = q.front();
        q.pop(), in[t] = 0;
        for (int i = hd[t]; i; i = nxt[i]) {
          int it = to[i], d = dis[t] + cst[i];
          if (limit[i] && d < dis[it]) {
            dis[it] = d, fl[it] = min(fl[t], limit[i]), fr[it] = i;
            if (!in[it]) in[it] = 1, q.push(it);
          }
        }
      }
      if (dis[t] > 1e9) return make_pair(flow, cost);
      flow += fl[t], cost += dis[t] * fl[t];
      for (int u = t; u != s; u = to[fr[u] ^ 1])
        limit[fr[u]] -= fl[t], limit[fr[u] ^ 1] += fl[t];
    }
  }
};
struct bounded_flow {
  int e, u[M], v[M], lo[M], hi[M], cst[M];
  void add(int _u, int _v, int w, int c) {
    if (c < 0) {
      u[++e] = _u, v[e] = _v, lo[e] = w, hi[e] = w, cst[e] = c;
      u[++e] = _v, v[e] = _u, lo[e] = 0, hi[e] = w, cst[e] = -c;
    } else
      u[++e] = _u, v[e] = _v, lo[e] = 0, hi[e] = w, cst[e] = c;
  }
  flow g;
  pair<int, int> mincost(int n, int s, int t, int ss, int tt) {
    static int w[N];
    memset(w, 0, sizeof(w));
    int flow = 0, cost = 0, tot = 0;
    for (int i = 1; i <= e; i++) {
      w[u[i]] -= lo[i], w[v[i]] += lo[i];
      cost += lo[i] * cst[i];
      g.add(u[i], v[i], hi[i] - lo[i], cst[i]);
    }
    for (int i = 1; i <= n; i++)
      if (w[i] > 0)
        g.add(ss, i, w[i], 0), tot += w[i];
      else if (w[i] < 0)
        g.add(i, tt, -w[i], 0);
    g.add(t, s, 1e9, 0);
    pair<int, int> res = g.mincost(ss, tt);
    cost += res.second;
    flow += g.limit[g.hd[s]];
    g.hd[s] = g.nxt[g.hd[s]], g.hd[t] = g.nxt[g.hd[t]];
    res = g.mincost(s, t);
    return make_pair(flow + res.first, cost + res.second);
  }
} f;
int n, m, s, t;
int main() {
  cin >> n >> m >> s >> t;
  for (int i = 1; i <= m; i++) {
    int u, v, w, c;
    cin >> u >> v >> w >> c, f.add(u, v, w, c);
  }
  pair<int, int> res = f.mincost(n, s, t, 0, n + 1);
  cout << res.first << " " << res.second << endl;
  return 0;
}
