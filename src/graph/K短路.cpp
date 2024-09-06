//复杂度 nlogn +mlogm+klogk
#include <bits/stdc++.h>
#include <queue>
 
template <class T, class U>
inline bool smin(T &x, const U &y) {
  return y < x ? x = y, 1 : 0;
}
template <class T, class U>
inline bool smax(T &x, const U &y) {
  return x < y ? x = y, 1 : 0;
}
 
using LL = long long;
using PII = std::pair<int, int>;
 
constexpr int N(2.5e5 + 5);
 
using T = LL;
struct Edge {
  int x, y; T z;
};
struct Heap {
  struct Node {
    int ls, rs, h, v;
    T w;
  } t[N * 40];
  int cnt;
  int newNode(int v, T w) {
    t[++cnt] = {0, 0, 1, v, w};
    return cnt;
  }
  int merge(int x, int y) {
    if (!x) return y;
    if (!y) return x;
    if (t[x].w > t[y].w) std::swap(x, y);
    t[++cnt] = t[x], x = cnt;
    t[x].rs = merge(t[x].rs, y);
    if (t[t[x].ls].h < t[t[x].rs].h) std::swap(t[x].ls, t[x].rs);
    t[x].h = t[t[x].rs].h + 1;
    return x;
  }
} h;
 
 
std::vector<T> kShortestPath(int n, int k, int s, int t, const std::vector<Edge> &e) {
  int m = e.size();
  std::vector<int> deg(n + 1), g(m);
  for (auto &[x, y, z] : e) deg[y]++;
  for (int i = 1; i <= n; i++) deg[i] += deg[i - 1];
  for (int i = 0; i < m; i++) g[--deg[e[i].y]] = i;
 
  std::vector<T> d(n, -1);
  std::vector<int> fa(n, -1), p;
 
  using Q = std::pair<T, int>;
  std::priority_queue<Q, std::vector<Q>, std::greater<Q>> q;
  
  {
    p.reserve(n);
    d[t] = 0, q.push({0, t});
    
    std::vector<bool> vis(n);
    while (!q.empty()) {
      int x = q.top().second;
      q.pop();
      if (vis[x]) continue;
      vis[x] = true;
      p.push_back(x);
      for (int i = deg[x]; i < deg[x + 1]; i++) {
        auto &[y, _, z] = e[g[i]];
        if (d[y] == -1 || d[y] > d[x] + z) {
          d[y] = d[x] + z, fa[y] = g[i];
          q.push({d[y], y});
        }
      }
    }  
  }
 
  if (d[s] == -1) std::vector<T>(k, -1);
  std::vector<int> heap(n);
  h.cnt = 0;
  for (int i = 0; i < m; i++) {
    auto &[x, y, z] = e[i];
    if (d[x] != -1 && d[y] != -1 && fa[x] != i) {
      heap[x] = h.merge(heap[x], h.newNode(y, d[y] + z - d[x]));
    }
  }
 
  for (int x : p) {
    if (x != t) heap[x] = h.merge(heap[x], heap[e[fa[x]].y]);
  }
 
  if (heap[s]) q.push({d[s] + h.t[heap[s]].w, heap[s]});
  std::vector<T> res = {d[s]};
 
  for (int i = 1; i < k && !q.empty(); i++) {
    auto [w, o] = q.top();
    q.pop();
 
    res.push_back(w);
    
    int j = h.t[o].v;
    if (heap[j]) q.push({w + h.t[heap[j]].w, heap[j]});
    for (auto s : {h.t[o].ls, h.t[o].rs}) {
      if (s) q.push({w + h.t[s].w - h.t[o].w, s}); 
    }
  }
  res.resize(k, -1);
  return res;
}
 
int a[N];
void solve() {
  int n, k;
  std::cin >> n >> k;
 
  std::vector<Edge> e;
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i];
  }
  e.push_back({0, 1, a[1]});
  for (int i = 2; i <= n; i++) {
    if (i - 3 > 0) e.push_back({i - 3, i, a[i]});
    e.push_back({i - 2, i, a[i]});
    e.push_back({i - 1, i, a[i]});
  }
  if (n - 1 >= 1) e.push_back({n - 1, n + 1, 0});
  e.push_back({n, n + 1, 0});
 
  auto res = kShortestPath(n + 2, k, 0, n + 1, e);
 
  for (auto x : res) std::cout << x << "\n";
}
 
int main() {
  // freopen("t.in", "r", stdin);
  
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  
  int t = 1;
  
  // std::cin >> t;
  
  while (t--) {
    solve();
  }
  return 0;
}