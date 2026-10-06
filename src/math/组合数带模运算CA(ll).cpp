// Comb c(n,mod=998244353); inv为阶乘逆元；非法选择数返回0。
#include <bits/stdc++.h>
using namespace std;

struct Comb {
    int n, mod;
    vector<int> fac, inv;
    Comb(int n, int mod = 998244353)
        : n(n), mod(mod), fac(n + 1, 1), inv(n + 1, 1) {
        assert(0 <= n && n < mod);  // mod须为质数。
        for (int i = 1; i <= n; i++) fac[i] = 1LL * fac[i - 1] * i % mod;
        inv[n] = ksm(fac[n], mod - 2);
        for (int i = n; i >= 1; i--) inv[i - 1] = 1LL * inv[i] * i % mod;
    }
    int ksm(int x, long long k) const {
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
