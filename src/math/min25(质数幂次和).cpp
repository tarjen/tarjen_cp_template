// 用法：
// min25 tr(10);  // 默认质数模数 1000000007。
// ll sum = tr.cal1(10);  // <=10 的质数之和为 17。
// tr.build_multiplicative({-1,1,0,0}, [&](ll p, ll e) {
//     return (p-1) * tr.powmod(p, e-1) % tr.mod;  // phi(p^e)。
// });
// ll phi_sum = tr.get(10);  // sum(phi(i),i=1..10)=32。
// 系数表示 f(p)=-1+p；cal0..cal3 分别是质数的 0..3 次幂和。
// 查询 x 必须是预处理的整除分块值 floor(n/i)；get 前须设置积性函数。
#include <bits/stdc++.h>
using namespace std;

struct min25 {
    using ll = long long;
    ll n;
    int sq, mod;
    vector<int> p, id1, id2;
    vector<ll> w, G;
    array<vector<ll>, 4> g, sum;
    bool multiplicative_ready = false;
    explicit min25(ll n, int mod = 1000000007)
        : n(n), sq(sqrt((long double)n)), mod(mod) {
        assert(n >= 1 && mod > 3);  // mod为质数。
        while (1LL * (sq + 1) * (sq + 1) <= n) sq++;
        while (1LL * sq * sq > n) sq--;
        vector<char> composite(sq + 1);
        p.push_back(0);
        for (int i = 2; i <= sq; i++) {
            if (!composite[i]) p.push_back(i);
            for (int j = 1; j < (int)p.size() && p[j] <= sq / i; j++) {
                composite[i * p[j]] = true;
                if (i % p[j] == 0) break;
            }
        }
        for (auto& s : sum) s.assign(p.size(), 0);
        for (int i = 1; i < (int)p.size(); i++) {
            ll power = 1;
            for (int k = 0; k < 4; k++)
                sum[k][i] = (sum[k][i - 1] + power) % mod,
                power = power * p[i] % mod;
        }
        id1.assign(sq + 1, -1);
        id2.assign(sq + 1, -1);
        ll inv2 = powmod(2, mod - 2), inv4 = powmod(4, mod - 2),
           inv6 = powmod(6, mod - 2);
        for (ll l = 1, r; l <= n; l = r + 1) {
            ll value = n / l;
            r = n / value;
            int id = w.size();
            w.push_back(value);
            if (value <= sq)
                id1[value] = id;
            else
                id2[n / value] = id;
            ll x = value % mod;
            g[0].push_back(norm(x - 1));
            g[1].push_back(norm(x * (x + 1) % mod * inv2 % mod - 1));
            g[2].push_back(
                norm(x * (x + 1) % mod * (2 * x + 1) % mod * inv6 % mod - 1));
            g[3].push_back(norm(
                x * x % mod * (x + 1) % mod * (x + 1) % mod * inv4 % mod - 1));
        }
        for (int i = 1; i < (int)p.size(); i++) {
            ll power[4] = {1, p[i], 1LL * p[i] * p[i] % mod,
                           1LL * p[i] * p[i] % mod * p[i] % mod};
            for (int j = 0; j < (int)w.size() && p[i] <= w[j] / p[i]; j++) {
                int t = getid(w[j] / p[i]);
                for (int k = 0; k < 4; k++)
                    g[k][j] =
                        norm(g[k][j] -
                             power[k] * norm(g[k][t] - sum[k][i - 1]) % mod);
            }
        }
    }
    ll norm(ll x) const {
        x %= mod;
        return x < 0 ? x + mod : x;
    }
    ll powmod(ll x, ll e) const {
        ll r = 1;
        for (; e; e >>= 1, x = x * x % mod)
            if (e & 1) r = r * x % mod;
        return r;
    }
    // 仅接受预处理的整除分块点x=floor(n/i)。
    int getid(ll x) const {
        assert(1 <= x && x <= n);
        int id = x <= sq ? id1[x] : id2[n / x];
        assert(id >= 0 && w[id] == x);
        return id;
    }
    ll cal0(ll x) const { return g[0][getid(x)]; }
    ll cal1(ll x) const { return g[1][getid(x)]; }
    ll cal2(ll x) const { return g[2][getid(x)]; }
    ll cal3(ll x) const { return g[3][getid(x)]; }
    // f(p)=coef[0]+coef[1]*p+coef[2]*p^2+coef[3]*p^3；calc(p,e)提供f(p^e)，f(1)=1。
    template <class Calc>
    void build_multiplicative(array<ll, 4> coef, Calc calc) {
        G.assign(w.size(), 0);
        for (int i = 0; i < (int)w.size(); i++)
            for (int k = 0; k < 4; k++)
                G[i] = norm(G[i] + norm(coef[k]) * g[k][i] % mod);
        vector<ll> prefix = G;
        for (int j = (int)p.size() - 1; j >= 1; j--) {
            ll prime = p[j];
            for (int i = 0; i < (int)w.size() && prime <= w[i] / prime; i++) {
                for (ll power = prime, e = 1; power <= w[i] / prime;
                     power *= prime, e++)
                    G[i] = norm(G[i] +
                                norm(calc(prime, e)) *
                                    norm(G[getid(w[i] / power)] -
                                         prefix[getid(prime)]) %
                                    mod +
                                norm(calc(prime, e + 1)));
            }
        }
        multiplicative_ready = true;
    }
    ll get(ll x) const {
        assert(multiplicative_ready);
        return norm(G[getid(x)] + 1);
    }
};
