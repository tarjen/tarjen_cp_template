const ull mask = std::chrono::steady_clock::now().time_since_epoch().count();
ull h(ull x) { return x * x * x * 1237123 + 19260817; }
ull f(ull x) {
  ull cur = h(x & ((1 << 31) - 1)) + h(x >> 31);
  return cur;
}
ull shift(ull x) {
  x ^= mask;
  x ^= x << 13; x ^= x >> 7; x ^= x << 17;
  x ^= mask; return x;
}
const int N = 1e6 + 10;
int n; ull hash[N];
std::vector<int> edge[N];
std::set<ull> trees;
void getHash(int x, int p) {
  hash[x] = 1;
  for (int i : edge[x]) {
    if (i == p) {
      continue;
    }
    getHash(i, x);
    hash[x] += shift(hash[i]);
  }
  trees.insert(hash[x]);
}