// 用法：
// vector<ll> prefix = {0, 1, 0};  // 已知 mu 的前缀和，prefix[i]=sum(mu(1..i))。
// DuJiaoSieve tr(prefix, [](ll n)->ll { return n>0; }, [](ll n) { return n; });
// ll sum = tr.F(10);  // sum(mu(1..10))=-1。
// 两个回调依次返回 (f*g) 的前缀和与 g 的前缀和，本例 f=mu、g=1。
// prefix 从下标 0 开始；g(1) 非零，超出预处理范围会自动记忆化。
#include <bits/stdc++.h>
using namespace std;

struct DuJiaoSieve {
    typedef long long ll;
    vector<ll> sumf;
    function<ll(ll)> convolution_prefix, g_prefix;
    unordered_map<ll, ll> cache;
    DuJiaoSieve(vector<ll> prefix, function<ll(ll)> sum, function<ll(ll)> sumg)
        : sumf(move(prefix)),
          convolution_prefix(move(sum)),
          g_prefix(move(sumg)) {
        assert(!sumf.empty() && g_prefix(1) != 0);
    }
    ll F(ll n) {
        assert(n >= 0);
        if (n < (ll)sumf.size()) return sumf[n];
        auto it = cache.find(n);
        if (it != cache.end()) return it->second;
        ll ans = convolution_prefix(n);
        for (ll l = 2, r; l <= n; l = r + 1) {
            r = n / (n / l);
            ans -= (g_prefix(r) - g_prefix(l - 1)) * F(n / l);
        }
        return cache[n] = ans / g_prefix(1);
    }
};
