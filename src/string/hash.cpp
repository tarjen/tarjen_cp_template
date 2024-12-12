typedef long long ll;
const int G = 2;
typedef array<ll, G> hs;
const hs p = {31, 131};
const hs mod = {998244353, 1'000'000'007};
hs &operator+=(hs &a, hs b) {
    for (int i = 0; i < G; i++) {
        if ((a[i] += b[i]) >= mod[i]) a[i] -= mod[i];
    }
    return a;
}
hs operator+(hs a, hs b) { return a += b; }
hs &operator-=(hs &a, hs b) {
    for (int i = 0; i < G; i++) {
        if ((a[i] -= b[i]) < 0) a[i] += mod[i];
    }
    return a;
}
hs operator-(hs a, hs b) { return a -= b; }
hs &operator*=(hs &a, hs b) {
    for (int i = 0; i < G; i++) {
        a[i] = (a[i] * b[i]) % mod[i];
    }
    return a;
}
hs operator*(hs a, hs b) { return a *= b; }

struct Hash {
    int n;
    vector<hs> has1, has2, Pow;
    void Hash_init(string &s) {
        n = (int)s.size();
        Pow.resize(n + 2);
        has1.resize(n + 2);
        has2.resize(n + 2);
        Pow[0] = make_pair(1ll, 1ll);
        for (int i = 1; i <= n; i++) Pow[i] = Pow[i - 1] * p;
        for (int i = 1; i <= n; i++)
            has1[i] =
                has1[i - 1] * p + hs{s[i - 1] - 'a' + 1, s[i - 1] - 'a' + 1};
        for (int i = n; i >= 1; i--)
            has2[i] =
                has2[i + 1] * p + hs{s[i - 1] - 'a' + 1, s[i - 1] - 'a' + 1};
    }
    hs get1(int l, int r) { return has1[r] - has1[l - 1] * Pow[r - l + 1]; }
    hs get2(int l, int r) { return has2[l] - has2[r + 1] * Pow[r - l + 1]; }
};