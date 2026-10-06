// 用法：
// 本板是轴对齐线段统计的题目片段，输入每条线段的 x y z w。
// solve<LEN>() 统计由两条竖线和两条横线组成的矩形。
// 依赖 N/ll、模板 solve 的前置声明；目前不是可独立复用的 Bitset 类。
int n;
vector<tuple<int, int, int>> a, b;
int sz;
void solve() {
    cin >> n;
    for (int i = 1, x, y, z, w; i <= n; i++) {
        cin >> x >> y >> z >> w;
        if (y > w) swap(y, w);
        if (x > z) swap(x, z);
        if (x == z)
            a.emplace_back(x, y, w);
        else
            b.emplace_back(y, x, z);
    }
    if (a.size() > b.size()) swap(a, b);
    solve<1>();
}
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