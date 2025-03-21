#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, n) for (int i = a; i < n; i++)
#define per(i, a, n) for (int i = n - 1; i >= a; i--)
#define all(x) (x).begin(), (x).end()
#define siz(x) ((int)(x).size())
typedef vector<int> VI;
typedef long long ll;
typedef pair<int, int> PII;
const ll mod = 1000000007;
ll powmod(ll a, ll b) {
    ll res = 1;
    a %= mod;
    assert(b >= 0);
    for (; b; b >>= 1) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
    }
    return res;
}
ll n;
namespace linear_seq {
const int N = 10010;
ll res[N], base[N], _c[N], _md[N];

vector<int> Md;
void mul(ll *a, ll *b, int k) {
    rep(i, 0, k + k) _c[i] = 0;
    rep(i, 0, k) if (a[i]) rep(j, 0, k) _c[i + j] =
        (_c[i + j] + a[i] * b[j]) % mod;
    for (int i = k + k - 1; i >= k; i--)
        if (_c[i])
            rep(j, 0, siz(Md)) _c[i - k + Md[j]] =
                (_c[i - k + Md[j]] - _c[i] * _md[Md[j]]) % mod;
    rep(i, 0, k) a[i] = _c[i];
}
int solve(ll n, VI a, VI b) {
    ll ans = 0, pnt = 0;
    int k = siz(a);
    assert(siz(a) == siz(b));
    rep(i, 0, k) _md[k - 1 - i] = -a[i];
    _md[k] = 1;
    Md.clear();
    rep(i, 0, k) if (_md[i] != 0) Md.push_back(i);
    rep(i, 0, k) res[i] = base[i] = 0;
    res[0] = 1;
    while ((1ll << pnt) <= n) pnt++;
    for (int p = pnt; p >= 0; p--) {
        mul(res, res, k);
        if ((n >> p) & 1) {
            for (int i = k - 1; i >= 0; i--) res[i + 1] = res[i];
            res[0] = 0;
            rep(j, 0, siz(Md)) res[Md[j]] =
                (res[Md[j]] - res[k] * _md[Md[j]]) % mod;
        }
    }
    rep(i, 0, k) ans = (ans + res[i] * b[i]) % mod;
    if (ans < 0) ans += mod;
    return ans;
}
VI BM(VI s) {
    VI C(1, 1), B(1, 1);
    int L = 0, m = 1, b = 1;
    rep(n, 0, siz(s)) {
        ll d = 0;
        rep(i, 0, L + 1) d = (d + (ll)C[i] * s[n - i]) % mod;
        if (d == 0)
            ++m;
        else if (2 * L <= n) {
            VI T = C;
            ll c = mod - d * powmod(b, mod - 2) % mod;
            while (siz(C) < siz(B) + m) C.push_back(0);
            rep(i, 0, siz(B)) C[i + m] = (C[i + m] + c * B[i]) % mod;
            L = n + 1 - L;
            B = T;
            b = d;
            m = 1;
        } else {
            ll c = mod - d * powmod(b, mod - 2) % mod;
            while (siz(C) < siz(B) + m) C.push_back(0);
            rep(i, 0, siz(B)) C[i + m] = (C[i + m] + c * B[i]) % mod;
            ++m;
        }
    }
    return C;
}
int gao(VI a, ll n) {
    VI c = BM(a);
    c.erase(c.begin());
    rep(i, 0, siz(c)) c[i] = (mod - c[i]) % mod;
    return solve(n, c, VI(a.begin(), a.begin() + siz(c)));
}
};  // namespace linear_seq

int main() {
    vector<int> v;
    v.push_back(2);
    v.push_back(24);
    v.push_back(96);
    v.push_back(416);
    v.push_back(1536);
    v.push_back(5504);
    v.push_back(18944);
    v.push_back(64000);
    v.push_back(212992);
    v.push_back(702464);
    scanf("%lld", &n);
    printf("%lld\n", 1LL * linear_seq::gao(v, n - 1) % mod);
}
