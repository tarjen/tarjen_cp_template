/*
用户指定：将本次讨论的 O(n^2) 多项式 k 次幂递推收进板子。
令 b=a^k，由 a*b'=k*a'*b 比较系数，按次数递推 b。
*/
// 用法：auto b = PolyPow::pow(vector<int>{1, 2, 3}, 3, 5);
// 返回 a(x)^k 的前 n 项（下标 0..n-1），上例为 {1,6,21,44,63}。
// 要求 a[0]=1，系数属于 [0,mod)，k>=0，0<=n<mod；缺少的系数补 0。
// 模数为质数 998244353；时间 O(n^2)，空间 O(n)，不依赖 NTT。
#include <bits/stdc++.h>
using namespace std;

struct PolyPow {
    using ll = long long;
    static constexpr int mod = 998244353;

    static vector<int> pow(vector<int> a, ll k, int n) {
        assert(k >= 0 && n >= 0 && n < mod);
        if (!n) return {};
        assert(!a.empty() && a[0] == 1);
        a.resize(n);
        vector<int> b(n), inv(n);
        b[0] = 1;
        ll km = (k % mod + 1) % mod;
        for (int i = 1; i < n; i++) {
            inv[i] = i == 1 ? 1 : (ll)(mod - mod / i) * inv[mod % i] % mod;
            for (int j = 1; j <= i; j++) {
                ll c = (km * j - i) % mod;
                if (c < 0) c += mod;
                b[i] = (b[i] + c * a[j] % mod * b[i - j]) % mod;
            }
            b[i] = (ll)b[i] * inv[i] % mod;
        }
        return b;
    }
};
