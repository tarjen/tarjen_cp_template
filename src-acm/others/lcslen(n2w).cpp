// 用户要求：复用 bitset手写.cpp，不再重复定义 Bitset。
// 函数内片段：先提供 Bitset、int n 和小写串 s（1base，s[0] 不用）。
// getans(mid) 返回 s[1..mid] 与 s[mid+1..n] 的 LCS 长度，0<=mid<=n。
vector<Bitset> ch(26, Bitset(n + 1));
Bitset f(n + 1), g(n + 1);
auto getans = [&](int mid) {
    f.init();
    for (auto& b : ch) b.init();
    for (int i = mid + 1; i <= n; i++) ch[s[i] - 'a'].setBit(i);
    for (int i = 1; i <= mid; i++) {
        g = f | ch[s[i] - 'a'];
        f = f << 1;
        f.setBit(1);
        f = g - f;
        f = f ^ g;
        f = f & g;
    }
    return f.count();
};
