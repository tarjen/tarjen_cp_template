const int maxn = 3e6 + 10;
int sumf[maxn];
int Sum(int n) {  // 这是 f * g 的 n 项前缀和
}
int Sumg(int n) {  // g 的 n 项前缀和
}
map<int, int> f;
int F(int n) {
    if (n <= 3000'000) return sumf[n];  // 预处理出 n 较小时的前缀和
    if (f.find(n) != f.end())
        return f[n];  // 记忆化，如果求过这个值，就不需要再递归一遍了
    int ans = Sum(n);
    for (int l = 2, r; l <= n; l = r + 1)  // 整除分块
        r = n / (n / l), ans -= (Sumg(r) - Sumg(l - 1)) * F(n / l);
    // [l,r] 的 F (n / l) 是一样的，对 g(x) 求个和即可
    return f[n] = ans / Sumg(1);  // 别忘了除上 g(1)
}
