// DuJiaoSieve d(prefix,sum_fg,sum_g); F(n)；prefix为0base已知前缀和，两个回调提供卷积和g的前缀和。
#include <bits/stdc++.h>
using namespace std;

struct DuJiaoSieve {
    using ll=long long;
    vector<ll> sumf;
    function<ll(ll)> convolution_prefix,g_prefix;
    unordered_map<ll,ll> cache;
    DuJiaoSieve(vector<ll> prefix,function<ll(ll)> sum,function<ll(ll)> sumg):
        sumf(move(prefix)),convolution_prefix(move(sum)),g_prefix(move(sumg)) { assert(!sumf.empty()&&g_prefix(1)!=0); }
    ll F(ll n) {
        assert(n>=0);
        if(n<(ll)sumf.size()) return sumf[n];
        auto it=cache.find(n); if(it!=cache.end()) return it->second;
        ll ans=convolution_prefix(n);
        for(ll l=2,r;l<=n;l=r+1) { r=n/(n/l); ans-=(g_prefix(r)-g_prefix(l-1))*F(n/l); }
        return cache[n]=ans/g_prefix(1);
    }
};
