// 用法：
// init();  // 先预处理幂表，全程序一次。
// extendable_sequence tr;
// tr.add_back({2,3});
// tr.add_front({1});  // 当前序列 {1,2,3}。
// auto hash = tr.calc(1, 3);  // 子区间哈希，1base 闭区间。
// auto value = tr[2].second;  // 位置 2 的值为 2。
// 输入 vector 不补首格；序列长度及幂偏移不能超过预处理容量。
// 元素和哈希用 ll，长度和下标用 int；底层 dq[0] 是空前缀。
typedef long long ll;
/*
1base闭区间，dq[0]为空前缀；输入vector不需要补首格。
pair<ll,ll> first表示哈希sum，second表示当前位置的值
*/
#define sz(a) (int)((a).size())
const int maxn = 3e5 + 10;
const ll mod = 1e9 + 7, base = 1331;
ll fpow(ll n, ll k, ll p = mod) {
    ll r = 1;
    for (; k; k >>= 1) {
        if (k & 1) r = r * n % p;
        n = n * n % p;
    }
    return r;
}
void add(ll& a, ll val, ll p = mod) {
    if ((a = (a + val)) >= p) a -= p;
}
void sub(ll& a, ll val, ll p = mod) {
    if ((a = (a - val)) < 0) a += p;
}
ll mul(ll a, ll b, ll p = mod) { return a * b % p; }
ll inv(ll a, ll p = mod) { return fpow(a, p - 2, p); }
ll p[maxn], ip[maxn];
void init() {
    p[0] = 1;
    for (int i = 1; i < maxn; i++) p[i] = mul(p[i - 1], base, mod);
    ip[0] = 1;
    ll ib = inv(base);  // 一次求逆，线性递推逆幂。
    for (int i = 1; i < maxn; i++) ip[i] = mul(ip[i - 1], ib);
}
struct extendable_sequence {
    deque<pair<ll, ll>> dq;
    int pow_offset;

    extendable_sequence() {
        pow_offset = 0;
        dq.push_back(make_pair(0, 0));
    }

    int size() { return sz(dq) - 1; }

    pair<ll, ll>& operator[](int i) { return dq[i]; }

    void add_back(vector<ll> vals) {
        ll t = dq.back().first;
        for (int i = 0; i < sz(vals); i++) {
            add(t, mul(vals[i], mul(p[sz(dq) - 1], ip[pow_offset], mod), mod),
                mod);
            dq.push_back(make_pair(t, vals[i]));
        }
    }

    void add_front(vector<ll> vals) {
        pow_offset += sz(vals);
        ll t = dq.front().first;
        for (int i = sz(vals) - 1; i >= 0; i--) {
            dq.front().second = vals[i];
            sub(t, mul(vals[i], mul(p[i], ip[pow_offset], mod), mod), mod);
            dq.push_front(make_pair(t, 0));
        }
    }

    ll calc(int l, int r) {
        if (l > r) return 0;
        ll res = dq[r].first;
        sub(res, dq[l - 1].first, mod);
        res = mul(res, ip[l - 1], mod);
        res = mul(res, p[pow_offset], mod);
        return res;
    }
};

ll calc(extendable_sequence& x, extendable_sequence& y, int l,
         int r) {  // 返回(x+y)[l到r]的哈希值
    ll res = x.calc(l, min(r, sz(x)));
    add(res,
        mul(y.calc(max(1, l - sz(x)), r - sz(x)), p[max(0, sz(x) - l + 1)],
            mod),
        mod);
    return res;
}

ll calc(extendable_sequence& x, extendable_sequence& y,
         int i) {  // 返回(x+y)[i]单个元素的值
    if (i <= sz(x)) {
        return x[i].second;
    }
    if (i - sz(x) <= sz(y)) {
        return y[i - sz(x)].second;
    }
    return -1;
}
