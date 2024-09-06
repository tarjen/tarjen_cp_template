#include <bits/stdc++.h>
 
#define fp(i, a, b) for (int i = (a), i##_ = (b) + 1; i < i##_; ++i)
#define fd(i, a, b) for (int i = (a), i##_ = (b) - 1; i > i##_; --i)
#define file(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
using namespace std;
const int maxn = 2e5 + 5, P = 998244353;
using arr = int[maxn];
using ll = int64_t;
/*---------------------------------------------------------------------------*/
class Cipolla {
    int P, I2{};
    using pll = pair<ll, ll>;
#define X first
#define Y second
    ll mul(ll a, ll b) const { return a * b % P; }
    pll mul(pll a, pll b) const { return {(a.X * b.X + I2 * a.Y % P * b.Y) % P, (a.X * b.Y + a.Y * b.X) % P}; }
    template<class T> T POW(T a, int b, T x) { for (; b; b >>= 1, a = mul(a, a)) if (b & 1) x = mul(x, a); return x; }
public:
    Cipolla(int p = 0) : P(p) {}
    pair<int, int> sqrt(int n) {
        int a = rand(), x;
        if (!(n %= P))return {0, 0};
        if (POW(n, (P - 1) >> 1, (int)1) == P - 1) return {-1, -1};
        while (POW(I2 = ((ll) a * a - n + P) % P, (P - 1) >> 1, (int)1) == 1) a = rand();
        x = (int) POW(pll{a, 1}, (P + 1) >> 1, {1, 0}).X;
        if (2 * x > P) x = P - x;
        return {x, P - x};
    }
#undef X
#undef Y
};
/*---------------------------------------------------------------------------*/
#define ADD(a, b) (((a) += (b)) >= P ? (a) -=P : 0) // (a += b) %= P
#define SUB(a, b) (((a) -= (b)) < 0 ? (a) += P: 0)  // ((a -= b) += P) %= P
#define MUL(a, b) ((ll) (a) * (b) % P)
//vector<int> getInv(int L) {
//    vector<int> inv(L); inv[1] = 1;
//    fp(i, 1, L - 1) inv[i] = MUL((P - P / i), inv[P % i]);
//    return inv;
//}
//auto inv = getInv(maxn); // NOLINT
int POW(ll a, int b = P - 2, ll x = 1) { for (; b; b >>= 1, a = a * a % P) if (b & 1) x = x * a % P; return x; }
//int INV(int a) { return a < maxn ? inv[a] : POW(a); }
namespace NTT {
    const int g = 3;
    vector<int> Omega(int L) {
        int wn = POW(g, P / L);
        vector<int> w(L); w[L >> 1] = 1;
        fp(i, L / 2 + 1, L - 1) w[i] = MUL(w[i - 1], wn);
        fd(i, L / 2 - 1, 1) w[i] = w[i << 1];
        return w;
    }
    auto W = Omega(1 << 21); // NOLINT
    void DIF(int *a, int n) {
        for (int k = n >> 1; k; k >>= 1)
            for (int i = 0, y; i < n; i += k << 1)
                fp(j, 0, k - 1)
                    y = a[i + j + k], a[i + j + k] = MUL(a[i + j] - y + P, W[k + j]), ADD(a[i + j], y);
    }
    void IDIT(int *a, int n) {
        for (int k = 1; k < n; k <<= 1)
            for (int i = 0, x, y; i < n; i += k << 1)
                fp(j, 0, k - 1)
                    x = a[i + j], y = MUL(a[i + j + k], W[k + j]),
                    a[i + j + k] = x - y < 0 ? x - y + P : x - y, ADD(a[i + j], y);
        int Inv = P - (P - 1) / n;
        fp(i, 0, n - 1) a[i] = MUL(a[i], Inv);
        reverse(a + 1, a + n);
    }
}
namespace Polynomial {
    using Poly = std::vector<int>;
 
    // mul/div int
    Poly &operator*=(Poly &a, int b) { for (auto &x : a) x = MUL(x, b); return a; }
    Poly operator*(Poly a, int b) { return a *= b; }
    Poly operator*(int a, Poly b) { return b * a; }
    Poly &operator/=(Poly &a, int b) { return a *= POW(b); }
    Poly operator/(Poly a, int b) { return a /= b; }
 
    // Poly add/sub
    Poly &operator+=(Poly &a, Poly b) {
        a.resize(max(a.size(), b.size()));
        fp(i, 0, b.size() - 1) ADD(a[i], b[i]);
        return a;
    }
    Poly operator+(Poly a, Poly b) { return a += b; }
    Poly &operator-=(Poly &a, Poly b) {
        a.resize(max(a.size(), b.size()));
        fp(i, 0, b.size() - 1) SUB(a[i], b[i]);
        return a;
    }
    Poly operator-(Poly a, Poly b) { return a -= b; }
 
    // Poly mul
    void DFT(Poly &a) { NTT::DIF(a.data(), a.size()); }
    void IDFT(Poly &a) { NTT::IDIT(a.data(), a.size()); }
    int norm(int n) { return 1 << (32 - __builtin_clz(n - 1)); }
    void norm(Poly &a) { if (!a.empty()) a.resize(norm(a.size()), 0); }
    Poly &dot(Poly &a, Poly &b) {
        fp(i, 0, a.size() - 1) a[i] = MUL(a[i], b[i]);
        return a;
    }
    Poly operator*(Poly a, Poly b) {
        int n = a.size() + b.size() - 1, L = norm(n);
        if (a.size() <= 8 || b.size() <= 8) {
            Poly c(n);
            fp(i, 0, a.size() - 1) fp(j, 0, b.size() - 1)
                c[i + j] = (c[i + j] + (ll) a[i] * b[j]) % P;
            return c;
        }
        a.resize(L), b.resize(L);
        DFT(a), DFT(b), dot(a, b), IDFT(a);
        return a.resize(n), a;
    }
     
    // Poly inv
    Poly Inv2k(Poly a) { // a.size() = 2^k
        int n = a.size(), m = n >> 1;
        if (n == 1) return {POW(a[0])};
        Poly b = Inv2k(Poly(a.begin(), a.begin() + m)), c = b;
        b.resize(n), DFT(a), DFT(b), dot(a, b), IDFT(a);
        fp(i, 0, n - 1) a[i] = i < m ? 0 : P - a[i];
        DFT(a), dot(a, b), IDFT(a);
        return move(c.begin(), c.end(), a.begin()), a;
    }
    Poly Inv(Poly a) {
        int n = a.size();
        norm(a), a = Inv2k(a);
        return a.resize(n), a;
    }
 
    // Poly div/mod
    Poly operator/(Poly a,Poly b){
        int k = a.size() - b.size() + 1;
        if (k < 0) return {0};
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        b.resize(k), a = a * Inv(b);
        a.resize(k), reverse(a.begin(), a.end());
        return a;
    }
    pair<Poly, Poly> operator%(Poly a, const Poly& b) {
        Poly c = a / b;
        a -= b * c, a.resize(b.size() - 1);
        return {c, a};
    }
     
    // Poly sqrt
    Poly Sqrt(Poly a) {
        int n = a.size(), k = norm(n);
        Poly b = {(new Cipolla(P))->sqrt(a[0]).first}, c;
        a.resize(k * 2, 0);
        for (int L = 2; L <= k; L <<= 1) {
            b.resize(2 * L, 0), c = Poly(a.begin(), a.begin() + L) * Inv(b);
            fp(i, 0, 2 * L - 1) b[i] = MUL(b[i] + c[i], (P + 1) / 2);
        }
        return b.resize(n), b;
    }
     
    // Poly calculus
    void Derivative(Poly &a) {
        fp(i, 1, a.size() - 1) a[i - 1] = MUL(i, a[i]);
        a.pop_back();
    }
}