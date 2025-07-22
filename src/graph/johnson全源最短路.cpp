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