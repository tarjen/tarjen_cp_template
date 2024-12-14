template <int LEN>
void solve() {
    sz = a.size();
    if (LEN <= b.size()) {
        solve<min(N, LEN + 10)>();
        return;
    }
    using Bitset = bitset<LEN>;
    Bitset is[sz + 5];
    for (int i = 0; i < sz; i++)
        for (int j = 0; j < b.size(); j++) {
            auto& [x, l, r] = a[i];
            auto& [y, L, R] = b[j];
            if (l <= y && y <= r && L <= x && x <= R) is[i][j] = 1;
        }
    ll rs = 0;
    for (int i = 0, x; i < sz; i++)
        for (int j = i + 1; j < sz; j++) {
            x = (is[i] & is[j]).count();
            rs += x * (x - 1) / 2;
        }
    cout << rs << '\n';
}