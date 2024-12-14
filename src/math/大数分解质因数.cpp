typedef long long ll;
map<ll, bool> P;
mt19937_64 rnd(time(0));
namespace Pollard_Rho {
#define ldb long double
ll mul(ll x, ll y, ll mod) {
    return ((x * y - (ll)((ldb)x / mod * y) * mod) + mod) % mod;
}
ll gcd(ll a, ll b) { return (b == 0 ? a : gcd(b, a % b)); }
ll ksm(ll a, ll b, ll mod) {
    ll ans = 1;
    a %= mod;
    while (b) {
        if (b & 1) ans = mul(ans, a, mod);
        b >>= 1;
        a = mul(a, a, mod);
    }
    return ans;
}
int pr[15] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
bool Miller_Rabin(ll n) {
    if (n == 2 || n == 3) return 1;
    if (n % 2 == 0 || n == 1) return 0;
    ll d = n - 1;
    int s = 0;
    while (d % 2 == 0) s++, d >>= 1;
    for (int i = 0; i <= 11; i++) {
        if (pr[i] >= n) break;
        ll a = pr[i];
        ll x = ksm(a, d, n);
        ll y = 0;
        for (int j = 0; j <= s - 1; j++) {
            y = mul(x, x, n);
            if (y == 1 && x != 1 && x != (n - 1)) return 0;
            x = y;
        }
        if (y != 1) return 0;
    }
    return 1;
}
ll Pollard_Rho(ll n) {
    ll now, pre, g;
    while (true) {
        now = pre = rnd() % (n - 1) + 1;
        g = 1;
        ll c = rnd() % (n - 1) + 1;
        for (int i = 1, fst = 1;; i++) {
            now = (mul(now, now, n) + c) % n;
            g = mul(g, abs(now - pre), n);
            if (now == pre || !g) break;
            if (!(i & 127) || i == fst) {
                g = gcd(g, n);
                if (g > 1) return g;
                if (i == fst) pre = now, fst <<= 1;
            }
        }
    }
}
void Find(ll n) {
    if (n == 1) return;
    if (Miller_Rabin(n)) {
        P[n] = 1;
        return;
    }
    ll p = Pollard_Rho(n);
    int c = 0;
    while (!(n % p)) {
        n /= p, c++;
    }
    Find(p);
    Find(n);
}
}  // namespace Pollard_Rho
void solve(int x, set<int> &s) {
    Pollard_Rho ::Find(x);
    for (auto [x, _] : P) s.insert(x);
    P.clear();
}