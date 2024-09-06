struct graph {
  vector<vector<pair<int, ll>>> e;
  graph(int n) : e(n + 1) {}
  void adde(int u, int v, ll w) { e[u].push_back({v, w}); }
  vector<ll> h;
  // initialize h(u), return false if there exists a negative cycle
  bool init() {
    int n = e.size();
    h.assign(n, 0);
    queue<int> que;
    for (int u = 1; u < n; u++) que.push(u);
    vector<int> vis(n, 0), cnt(n, n + 1);
    while (que.size()) {
      auto u = que.front();
      que.pop();
      vis[u] = false;
      if (!cnt[u]--) return false;  // exists a negative cycle
      for (auto &[v, w] : e[u])
        if (h[v] > h[u] + w) {
          h[v] = h[u] + w;
          if (!vis[v]) que.push(v), vis[v] = 1;
        }
    }
    return true;
  }
  // single source shortest path from given sink based on h(u)
  vector<ll> query(int s) {
    int n = e.size();
    vector<ll> dis(n, inf);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>,
				   greater<pair<ll, int>>>
        que;
    que.push({dis[s] = 0, s});
    while (que.size()) {
      auto [du, u] = que.top();
      que.pop();
      if (dis[u] < du) continue;
      for (auto [v, w] : e[u]) {
        auto dv = du + w + h[u] - h[v];
        if (dis[v] > dv) que.push({dis[v] = dv, v});
      }
    }
    for (int i = 0; i < n; i++) dis[i] += h[i] - h[s];
    return dis;
  }
};