/*
严格0base，不用管任何函数里面的东西，用就可以了，不要越界
pair<int,int> first表示哈希sum，second表示当前位置的值
*/
#define int long long
#define sz(a) (int)((a).size())
const int maxn = 3e5 + 10;
const int mod = 1e9 + 7, base = 1331;
int fpow(int n, int k, int p = mod) {
    int r = 1;
    for (; k; k >>= 1) {
        if (k & 1) r = r * n % p;
        n = n * n % p;
    }
    return r;
}
void add(int& a, int val, int p = mod) {
    if ((a = (a + val)) >= p) a -= p;
}
void sub(int& a, int val, int p = mod) {
    if ((a = (a - val)) < 0) a += p;
}
int mul(int a, int b, int p = mod) { return (int)a * b % p; }
int inv(int a, int p = mod) { return fpow(a, p - 2, p); }
int p[maxn], ip[maxn];
void init() {
    p[0] = 1;
    for (int i = 1; i < maxn; i++) p[i] = mul(p[i - 1], base, mod);
    for (int i = 0; i < maxn; i++) ip[i] = inv(p[i], mod);
}
struct extendable_sequence {
    deque<pair<int, int>> dq;
    int pow_offset;

    extendable_sequence() {
        pow_offset = 0;
        dq.push_back(make_pair(0, 0));
    }

    int size() { return sz(dq) - 1; }

    pair<int, int>& operator[](int i) { return dq[i + 1]; }

    void add_back(vector<int> vals) {
        int t = dq.back().first;
        for (int i = 0; i < sz(vals); i++) {
            add(t, mul(vals[i], mul(p[sz(dq) - 1], ip[pow_offset], mod), mod),
                mod);
            dq.push_back(make_pair(t, vals[i]));
        }
    }

    void add_front(vector<int> vals) {
        pow_offset += sz(vals);
        int t = dq.front().first;
        for (int i = sz(vals) - 1; i >= 0; i--) {
            dq.front().second = vals[i];
            sub(t, mul(vals[i], mul(p[i], ip[pow_offset], mod), mod), mod);
            dq.push_front(make_pair(t, 0));
        }
    }

    int calc(int l, int r) {
        l++, r++;
        if (l > r) return 0;
        int res = dq[r].first;
        sub(res, dq[l - 1].first, mod);
        res = mul(res, ip[l - 1], mod);
        res = mul(res, p[pow_offset], mod);
        return res;
    }
};
// 返回(x+y)[l到r]的哈希值
int calc(extendable_sequence& x, extendable_sequence& y, int l, int r) {
    int res = x.calc(l, min(r, sz(x) - 1));
    add(res, mul(y.calc(max(0ll, l - sz(x)), r - sz(x)), p[sz(x)], mod), mod);
    return res;
}
// 返回(x+y)[i]单个元素的值
int calc(extendable_sequence& x, extendable_sequence& y, int i) {
    if (i < sz(x)) {
        return x[i].second;
    }
    if (i - sz(x) < sz(y)) {
        return y[i - sz(x)].second;
    }
    return -1;
}