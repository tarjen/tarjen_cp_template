vector<pair<int, int>> prufer_to_tree(const vector<int>& prufer) {
  int n = prufer.size() + 2;
  vector<int> deg(n + 1, 1);  // 1-base
  for (int u : prufer) deg[u]++;
  priority_queue<int, vector<int>, greater<int>> pq;
  for (int i = 1; i <= n; i++) if (deg[i] == 1) pq.push(i);
  vector<pair<int, int>> edges;
  for (int ux : prufer) {
    int u = pq.top(); pq.pop();
    edges.emplace_back(u, x);
    deg[u]--; deg[x]--;
    if (deg[x] == 1) { pq.push(x); }
  }
  int a = pq.top(); pq.pop();
  int b = pq.top(); pq.pop();
  edges.emplace_back(a, b);
  return edges;
}