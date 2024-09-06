#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353;
typedef double ld;
typedef complex<ld> cplx;
typedef vector<ll> poly;

ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
ll inv(ll n) { return qpow(n, mod - 2); }

const auto pi = acosl(-1);
const int len = 15, mask = (1 << len) - 1;

struct unitroot {
    static vector<cplx> w;
    static vector<cplx> get_root(int n) {
        n = 1 << 32 - __builtin_clz(n);
        if (n > w.size()) {
        w.resize(n);
        for (int i = 0; i < n; i++)
            w[i] = cplx(cos(2 * i * pi / n), sin(2 * i * pi / n));
        }
        int m = w.size() / n;
        vector<cplx> res(n);
        for (int i = 0, j = 0; i < n; i++, j += m) res[i] = w[j];
        return res;
    }
};
vector<cplx> unitroot::w;

void fft(vector<cplx> &p, const vector<cplx> &w) {
    int n = w.size();
    for (int i = 1, j = 0; i < n - 1; ++i) {
        int s = n;
        do {
        s >>= 1;
        j ^= s;
        } while (~j & s);
        if (i < j) swap(p[i], p[j]);
    }
    for (int d = 0; (1 << d) < n; ++d) {
        int m = 1 << d, m2 = m * 2, rm = n >> (d + 1);
        for (int i = 0; i < n; i += m2)
        for (int j = 0; j < m; ++j) {
            auto &p1 = p[i + j + m], &p2 = p[i + j];
            auto t = w[rm * j] * p1;
            p1 = p2 - t;
            p2 = p2 + t;
        }
    }
}
poly operator+(const poly &a, const poly &b) {
    poly c(max(a.size(), b.size()));
    for (int i = 0; i < a.size(); i++) c[i] += a[i];
    for (int i = 0; i < b.size(); i++) c[i] += b[i];
    for (auto &v : c) v %= mod;
    return c;
}
poly operator-(poly b) {
    for (auto &v : b) v = v ? mod - v : 0;
    return b;
}
poly operator-(const poly &a, const poly &b) { return a + -b; }
poly operator*(const poly &a, const poly &b) {
    vector<cplx> w = unitroot::get_root(a.size() + b.size() - 1);
    int n = w.size();
    vector<cplx> A(n), B(n), C(n), D(n);
    for (int i = 0; i < a.size(); ++i) A[i] = cplx(a[i] >> len, a[i] & mask);
    for (int i = 0; i < b.size(); ++i) B[i] = cplx(b[i] >> len, b[i] & mask);
    fft(A, w), fft(B, w);
    for (int i = 0; i < n; ++i) {
        int j = (n - i) % n;
        cplx da = (A[i] - conj(A[j])) * cplx(0, -0.5),
            db = (A[i] + conj(A[j])) * cplx(0.5, 0),
            dc = (B[i] - conj(B[j])) * cplx(0, -0.5),
            dd = (B[i] + conj(B[j])) * cplx(0.5, 0);
        C[j] = da * dd + da * dc * cplx(0, 1);
        D[j] = db * dd + db * dc * cplx(0, 1);
    }
    fft(C, w), fft(D, w);
    poly res(a.size() + b.size() - 1);
    for (int i = 0; i < res.size(); ++i) {
        ll da = (ll)(C[i].imag() / n + 0.5) % mod,
        db = (ll)(C[i].real() / n + 0.5) % mod,
        dc = (ll)(D[i].imag() / n + 0.5) % mod,
        dd = (ll)(D[i].real() / n + 0.5) % mod;
        res[i] = ((dd << (len * 2)) + ((db + dc) << len) + da) % mod;
    }
    return res;
}
poly inv(poly a) {
    int n = a.size();
    if (a.size() == 1) return {inv(a[0])};
    poly b = inv({a.begin(), a.end() - n / 2});
    auto c = a * b;
    c.resize(n);
    a = b * (poly{2} - c);
    a.resize(n);
    return a;
}
poly operator/(poly a, poly b) {
    int n = a.size() + b.size() - 1;
    b.resize(n);
    a = a * inv(b);
    a.resize(n);
    return a;
}