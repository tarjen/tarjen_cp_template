int find(int x) {
  for (int i = h[x]; ~i; i = ne[i]) {
    int j = e[i];
    if (!st[j]) {
      st[j] = 1;
      if (!match[j] || find(match[j])) {
        match[j] = x;
        return 1;
      }
    }
  }
  return 0;
}
int main() {
  for (int i = 1; i <= n; ++i) {
    memset(st, 0, sizeof st);
    if (find(i)) maxMatch++;
  }
}
