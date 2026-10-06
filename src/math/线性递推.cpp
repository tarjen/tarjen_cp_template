// 0base序列；LinearRecurrence
// r(coefficients,initial)或r(sequence)由BM推递推式；r.nth(n)，默认mod=1000000007。
#include <bits/stdc++.h>
using namespace std;
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
struct LinearRecurrence {
    vector<ll> res, _c, _md;
    VI coefficients, initial;
    LinearRecurrence(VI coefficients, VI initial)
        : coefficients(move(coefficients)), initial(move(initial)) {
        assert(this->coefficients.size() == this->initial.size());
    }
    explicit LinearRecurrence(VI sequence) : initial(move(sequence)) {
        coefficients = BM(initial);
        coefficients.erase(coefficients.begin());
        for (int& x : coefficients) x = (mod - x) % mod;
        initial.resize(coefficients.size());
    }
    int nth(ll n) {
        assert(n >= 0);
        if (coefficients.empty()) return 0;
        return solve(n, coefficients, initial);
    }

    vector<int> Md;
    void mul(ll* a, ll* b, int k) {
        for (int i = 0; i < k + k; i++) _c[i] = 0;
        for (int i = 0; i < k; i++)
            if (a[i])
                for (int j = 0; j < k; j++)
                    _c[i + j] = (_c[i + j] + a[i] * b[j]) % mod;
        for (int i = k + k - 1; i >= k; i--)
            if (_c[i])
                for (int j = 0; j < (int)Md.size(); j++)
                    _c[i - k + Md[j]] =
                        (_c[i - k + Md[j]] - _c[i] * _md[Md[j]]) % mod;
        for (int i = 0; i < k; i++) a[i] = _c[i];
    }
    int solve(ll n, VI a, VI b) {
        ll ans = 0, pnt = 0;
        int k = (int)a.size();
        if (!k) return 0;
        res.assign(k + 1, 0);
        _c.assign(2 * k + 1, 0);
        _md.assign(k + 1, 0);
        assert((int)a.size() == (int)b.size());
        for (int i = 0; i < k; i++) _md[k - 1 - i] = -a[i];
        _md[k] = 1;
        Md.clear();
        for (int i = 0; i < k; i++)
            if (_md[i] != 0) Md.push_back(i);
        for (int i = 0; i < k; i++) res[i] = 0;
        res[0] = 1;
        while (pnt < 62 && ((1ULL << pnt) <= (unsigned long long)n)) pnt++;
        for (int p = pnt; p >= 0; p--) {
            mul(res.data(), res.data(), k);
            if ((n >> p) & 1) {
                for (int i = k - 1; i >= 0; i--) res[i + 1] = res[i];
                res[0] = 0;
                for (int j = 0; j < (int)Md.size(); j++)
                    res[Md[j]] = (res[Md[j]] - res[k] * _md[Md[j]]) % mod;
            }
        }
        for (int i = 0; i < k; i++) ans = (ans + res[i] * b[i]) % mod;
        if (ans < 0) ans += mod;
        return ans;
    }
    VI BM(VI s) {
        VI C(1, 1), B(1, 1);
        int L = 0, m = 1, b = 1;
        for (int n = 0; n < (int)s.size(); n++) {
            ll d = 0;
            for (int i = 0; i < L + 1; i++) d = (d + (ll)C[i] * s[n - i]) % mod;
            if (d == 0)
                ++m;
            else if (2 * L <= n) {
                VI T = C;
                ll c = mod - d * powmod(b, mod - 2) % mod;
                while ((int)C.size() < (int)B.size() + m) C.push_back(0);
                for (int i = 0; i < (int)B.size(); i++)
                    C[i + m] = (C[i + m] + c * B[i]) % mod;
                L = n + 1 - L;
                B = T;
                b = d;
                m = 1;
            } else {
                ll c = mod - d * powmod(b, mod - 2) % mod;
                while ((int)C.size() < (int)B.size() + m) C.push_back(0);
                for (int i = 0; i < (int)B.size(); i++)
                    C[i + m] = (C[i + m] + c * B[i]) % mod;
                ++m;
            }
        }
        return C;
    }
    int gao(VI a, ll n) {
        VI c = BM(a);
        c.erase(c.begin());
        for (int i = 0; i < (int)c.size(); i++) c[i] = (mod - c[i]) % mod;
        if (c.empty()) return 0;
        return solve(n, c, VI(a.begin(), a.begin() + (int)c.size()));
    }
};
