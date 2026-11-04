// 验证本次讨论的多项式求幂递推，与朴素卷积二进制求幂对拍。
#include <bits/stdc++.h>
using namespace std;
#ifdef ACM_VARIANT
#include "../src-acm/math/多项式幂(n2).cpp"
#else
#include "../src/math/多项式幂(n2).cpp"
#endif

using ll = long long;
const int MOD = PolyPow::mod;

vector<int> mul(const vector<int>& a, const vector<int>& b, int n) {
    vector<int> c(n);
    for (int i = 0; i < min(n, (int)a.size()); i++)
        for (int j = 0; j < (int)b.size() && i + j < n; j++)
            c[i + j] = (c[i + j] + (ll)a[i] * b[j]) % MOD;
    return c;
}

vector<int> brute(vector<int> a, ll k, int n) {
    if (!n) return {};
    vector<int> b(n);
    b[0] = 1;
    while (k) {
        if (k & 1) b = mul(b, a, n);
        a = mul(a, a, n);
        k >>= 1;
    }
    return b;
}

int main() {
    assert(PolyPow::pow({1, 2, 3}, 3, 5) == vector<int>({1, 6, 21, 44, 63}));
    assert(PolyPow::pow({}, 0, 0).empty());
    mt19937_64 rng(20261104);
    vector<ll> powers{0, 1, 2, 3, MOD - 1, MOD, MOD + 1LL, LLONG_MAX};
    int cases = 0;
    for (int t = 0; t < 500; t++) {
        int n = rng() % 41;
        vector<int> a(1 + rng() % 45);
        for (int& x : a) x = rng() % MOD;
        a[0] = 1;
        ll k = t % 2 ? powers[rng() % powers.size()] : rng() % 30;
        assert(PolyPow::pow(a, k, n) == brute(a, k, n));
        cases++;
    }
    assert(PolyPow::pow({1}, LLONG_MAX, 50) == brute({1}, LLONG_MAX, 50));
    cout << "PASS: " << cases << " random cases and boundary checks\n";
}
