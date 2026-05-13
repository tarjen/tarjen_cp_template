#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
Poly: a[i] 表示 x^i 系数，模数 998244353，原根 3。
Mul(a,b,lim): 多项式乘法，只保留前 lim 项；lim=-1 返回完整卷积。
Inv(a,n): 返回 a^{-1} mod x^n，要求 a[0]!=0。
Ln(a,n): 返回 ln(a) mod x^n，要求 a[0]==1。
Exp(a,n): 返回 exp(a) mod x^n，要求 a[0]==0。
Derivative/Integral: 求导/积分，积分常数为 0。
partition_number(n): 返回 p[0..n]，p[i] 是整数拆分数。
限制: NTT 长度 <= 2^23；积分用到 i^{-1}，要求 n < MOD。
*/

namespace Poly {
const int MOD = 998244353, G = 3, MAXL = 1 << 23;
using P = vector<int>;

int qpow(ll a, ll b = MOD - 2) {
    ll r = 1;
    while (b) {
        if (b & 1) r = r * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return r;
}

inline int add(int a, int b) {
    a += b;
    return a >= MOD ? a - MOD : a;
}
inline int sub(int a, int b) {
    a -= b;
    return a < 0 ? a + MOD : a;
}
inline int mul(ll a, ll b) { return a * b % MOD; }

int norm(int n) {
    int l = 1;
    while (l < n) l <<= 1;
    return l;
}

vector<int> w{0, 1}, invs{0, 1};

void ensure_w(int n) {
    if ((int)w.size() >= n) return;
    assert(n <= MAXL);
    w.assign(n, 0);
    int wn = qpow(G, (MOD - 1) / n);
    w[n >> 1] = 1;
    for (int i = (n >> 1) + 1; i < n; i++) w[i] = mul(w[i - 1], wn);
    for (int i = (n >> 1) - 1; i; i--) w[i] = w[i << 1];
}

void ensure_inv(int n) {
    if ((int)invs.size() > n) return;
    int old = invs.size();
    invs.resize(n + 1);
    for (int i = old; i <= n; i++) {
        invs[i] = mul(MOD - MOD / i, invs[MOD % i]);
    }
}

void DFT(P& a) {
    int n = a.size();
    if (n <= 1) return;
    ensure_w(n);
    for (int k = n >> 1; k; k >>= 1) {
        for (int i = 0; i < n; i += k << 1) {
            for (int j = 0; j < k; j++) {
                int x = a[i + j], y = a[i + j + k];
                a[i + j] = add(x, y);
                a[i + j + k] = mul(sub(x, y), w[k + j]);
            }
        }
    }
}

void IDFT(P& a) {
    int n = a.size();
    if (n <= 1) return;
    ensure_w(n);
    for (int k = 1; k < n; k <<= 1) {
        for (int i = 0; i < n; i += k << 1) {
            for (int j = 0; j < k; j++) {
                int x = a[i + j], y = mul(a[i + j + k], w[k + j]);
                a[i + j] = add(x, y);
                a[i + j + k] = sub(x, y);
            }
        }
    }
    int iv = qpow(n);
    for (int& x : a) x = mul(x, iv);
    reverse(a.begin() + 1, a.end());
}

P Cut(const P& a, int n) {
    P b(min(n, (int)a.size()));
    for (int i = 0; i < (int)b.size(); i++) b[i] = a[i];
    b.resize(n);
    return b;
}

P Mul(P a, P b, int lim = -1) {
    if (a.empty() || b.empty() || lim == 0) return {};
    if (lim > 0) {
        if ((int)a.size() > lim) a.resize(lim);
        if ((int)b.size() > lim) b.resize(lim);
    }
    int need = a.size() + b.size() - 1;
    if (lim > 0) need = min(need, lim);
    if (min(a.size(), b.size()) <= 32) {
        P c(need);
        for (int i = 0; i < (int)a.size(); i++)
            if (a[i]) {
                for (int j = 0; j < (int)b.size() && i + j < need; j++) {
                    c[i + j] = (c[i + j] + (ll)a[i] * b[j]) % MOD;
                }
            }
        return c;
    }
    int L = norm(a.size() + b.size() - 1);
    a.resize(L), b.resize(L);
    DFT(a), DFT(b);
    for (int i = 0; i < L; i++) a[i] = mul(a[i], b[i]);
    IDFT(a);
    a.resize(need);
    return a;
}

P Derivative(const P& a) {
    if (a.size() <= 1) return {0};
    P b(a.size() - 1);
    for (int i = 1; i < (int)a.size(); i++) b[i - 1] = mul(a[i], i);
    return b;
}

P Integral(const P& a) {
    int n = a.size();
    ensure_inv(n + 1);
    P b(n + 1);
    for (int i = 0; i < n; i++) b[i + 1] = mul(a[i], invs[i + 1]);
    return b;
}

P Inv(const P& a, int n) {
    assert(n >= 0);
    if (!n) return {};
    assert(!a.empty() && a[0]);
    P b{qpow(a[0])};
    for (int m = 2; (m >> 1) < n; m <<= 1) {
        P f = Cut(a, m), g = b;
        g.resize(m);
        DFT(f), DFT(g);
        for (int i = 0; i < m; i++) f[i] = mul(f[i], g[i]);
        IDFT(f);
        int h = m >> 1;
        for (int i = 0; i < h; i++) f[i] = 0;
        for (int i = h; i < m; i++)
            if (f[i]) f[i] = MOD - f[i];
        DFT(f);
        for (int i = 0; i < m; i++) f[i] = mul(f[i], g[i]);
        IDFT(f);
        for (int i = 0; i < h; i++) f[i] = b[i];
        b.swap(f);
    }
    b.resize(n);
    return b;
}

P Ln(const P& a, int n) {
    assert(n >= 0);
    if (!n) return {};
    assert(!a.empty() && a[0] == 1);
    P r = Mul(Derivative(Cut(a, n)), Inv(a, n), n - 1);
    r = Integral(r);
    r.resize(n);
    return r;
}

P Exp(const P& a, int n) {
    assert(n >= 0);
    if (!n) return {};
    assert(a.empty() || a[0] == 0);
    P b{1};
    for (int m = 2; (m >> 1) < n; m <<= 1) {
        int len = min(m, n);
        P f = Cut(a, len), lb = Ln(b, len);
        for (int i = 0; i < len; i++) f[i] = sub(f[i], lb[i]);
        f[0] = add(f[0], 1);
        b = Mul(b, f, len);
    }
    b.resize(n);
    return b;
}

P partition_number(int n) {
    P sig(n + 1), a(n + 1);
    for (int d = 1; d <= n; d++) {
        for (int j = d; j <= n; j += d) {
            sig[j] += d;
            if (sig[j] >= MOD) sig[j] -= MOD;
        }
    }
    ensure_inv(n);
    for (int i = 1; i <= n; i++) a[i] = mul(sig[i], invs[i]);
    return Exp(a, n + 1);
}

// 加这里
P operator*(P a, P b) { return Mul(std::move(a), std::move(b)); }

P& operator*=(P& a, const P& b) {
    a = Mul(a, b);
    return a;
}
}  // namespace Poly

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    auto p = Poly::partition_number(n);
    cout << p[n] << '\n';

    return 0;
}