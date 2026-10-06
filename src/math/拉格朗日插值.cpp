// LR lr(n,mod=998244353);
// inpo(f,x)为连续点插值，cal(xs,ys,x)为离散点插值；输入0base。
#include <bits/stdc++.h>
using namespace std;

struct LR {
    int n, mod;
    vector<int> fac, facinv, inv;
    LR(int n, int mod = 998244353)
        : n(n), mod(mod), fac(n + 1, 1), facinv(n + 1, 1), inv(n + 1, 0) {
        assert(0 <= n && n < mod);  // mod为质数。
        for (int i = 1; i <= n; i++) fac[i] = 1LL * fac[i - 1] * i % mod;
        facinv[n] = Inv(fac[n]);
        for (int i = n; i >= 1; i--) facinv[i - 1] = 1LL * facinv[i] * i % mod;
        for (int i = 1; i <= n; i++)
            inv[i] = 1LL * fac[i - 1] * facinv[i] % mod;
    }
    int norm(long long x) const {
        x %= mod;
        return x < 0 ? x + mod : x;
    }
    int Inv(int x) const {
        int r = 1;
        for (int k = mod - 2; k; k >>= 1, x = 1LL * x * x % mod)
            if (k & 1) r = 1LL * r * x % mod;
        return r;
    }
    // x/y为0base，x在模意义下互异，O(m^2)。
    template <class T>
    int cal(const vector<T>& x, const vector<T>& y, long long k) const {
        assert(x.size() == y.size());
        int m = x.size(), s = 0;
        k = norm(k);
        for (int i = 0; i < m; i++)
            if (norm(x[i]) == k) return norm(y[i]);
        for (int i = 0; i < m; i++) {
            long long p = norm(y[i]), q = 1;
            for (int j = 0; j < m; j++)
                if (i != j)
                    p = p * norm(k - x[j]) % mod,
                    q = q * norm((long long)x[i] - x[j]) % mod;
            assert(q != 0);
            s = (s + p * Inv(q)) % mod;
        }
        return s;
    }
    // f[0..m]是连续整数点值，m<=构造时n，O(m)。
    template <class T>
    int inpo(const vector<T>& f, long long x) const {
        assert(!f.empty());
        int m = (int)f.size() - 1;
        assert(m <= n);
        x = norm(x);
        if (x <= m) return norm(f[x]);
        vector<int> pre(m + 2, 1), suf(m + 2, 1);
        for (int i = 0; i <= m; i++)
            pre[i + 1] = 1LL * pre[i] * norm(x - i) % mod;
        for (int i = m; i >= 0; i--)
            suf[i] = 1LL * suf[i + 1] * norm(x - i) % mod;
        long long s = 0;
        for (int i = 0; i <= m; i++) {
            long long p = 1LL * facinv[i] * facinv[m - i] % mod * pre[i] % mod *
                          suf[i + 1] % mod * norm(f[i]) % mod;
            s = norm(s + ((m - i) & 1 ? -p : p));
        }
        return s;
    }
};
