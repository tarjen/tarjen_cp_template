// 用法：
// Comb tr(100, 1000000007);  // 预处理到 100；模数为质数，100<mod。
// int choose = tr.C(5, 2);  // 组合数 10。
// int arrange = tr.A(5, 2);  // 排列数 20。
// C/A 的第一个参数不超过预处理上界；非法选择数返回 0。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
struct Comb {
    int n, mod;
    vector<int> fac, inv;
    Comb(int n, int mod = 1000000007)
        : n(n), mod(mod), fac(n + 1, 1), inv(n + 1, 1) {
        assert(0 <= n && n < mod);  // mod须为质数。
        for (int i = 1; i <= n; i++) fac[i] = 1LL * fac[i - 1] * i % mod;
        inv[n] = ksm(fac[n], mod - 2);
        for (int i = n; i >= 1; i--) inv[i - 1] = 1LL * inv[i] * i % mod;
    }
    int ksm(int x, ll k) const {
        int res = 1;
        for (; k; k >>= 1, x = 1LL * x * x % mod)
            if (k & 1) res = 1LL * res * x % mod;
        return res;
    }
    int C(int n, int m) const {
        if (n < 0 || m < 0 || m > n) return 0;
        assert(n <= this->n);
        return 1LL * fac[n] * inv[m] % mod * inv[n - m] % mod;
    }
    int A(int n, int m) const {
        if (n < 0 || m < 0 || m > n) return 0;
        assert(n <= this->n);
        return 1LL * fac[n] * inv[n - m] % mod;
    }
};
