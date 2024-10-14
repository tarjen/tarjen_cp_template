//seive 和 init 要求的 n  
#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=l;i<=r;++i)
#define repd(i,l,r) for(int i=l;i>=r;--i)
using namespace std;
typedef long long ll;
#define int long long
const int N=1e5+100;
const int M=1e4;
const ll mod=1e9+7;
ll p[M];
int cnt;
ll getmi(ll x,ll y){
    ll ret=1;
    while(y){
        if(y&1) ret=ret*x%mod;
        x=x*x%mod;
        y=y>>1;
}
return ret;
}
const ll inv2=getmi(2,mod-2);
const ll inv4=getmi(4,mod-2);
const ll inv6=getmi(6,mod-2);
bitset<N> v;
void seive()
{
    for(int i=2;i<N;++i)
    {
        if(!v[i])
            p[++cnt]=i;
        for(int j=1;j<=cnt && i*p[j]<N;++j)
        {
            v[i*p[j]]=true;
            if(i%p[j]==0)
                break;
        }
    }
}
struct min25
{
    ll n,sum0[M],sum1[M],sum2[M],sum3[M];
    ll w[N<<1],g0[N<<1],g1[N<<1],g2[N<<1],g3[N<<1],G[N<<1];
    int id1[N],id2[N],tot,sq;
    //min25使用条件：积性函数前缀和&&素数幂次值的点可以快速求
    ll calc(ll j,ll x)//f(p^x)的值 是一个积性函数
    {
        return p[j]^x;
    }

    int getid(ll x)
    {
        if(x<=sq)
            return id1[x];
        return id2[n/x];
    }
    void init(ll nn)
    {
        for(int i=1;i<=cnt;++i)
        {
            sum0[i]=(sum0[i-1]+1)%mod;
            sum1[i]=(sum1[i-1]+p[i])%mod;
            sum2[i]=(sum2[i-1]+p[i]*p[i]%mod)%mod;
            sum3[i]=(sum3[i-1]+p[i]*p[i]%mod*p[i]%mod)%mod;
        }//前i个素数幂和
        tot=0;
        n=nn;
        sq=sqrt(n);
        for(ll r,mm,m,l=1;l<=n;l=r+1)
        {
            r=n/(n/l);

            w[tot]=m=mm=n/l;
            mm%=mod;
            g0[tot]=(mm-1)%mod;
            g1[tot]=mm*(mm+1)%mod*inv2%mod-1;
            g2[tot]=mm*(mm+1)%mod*(2*mm%mod+1)%mod*inv6%mod-1;
            g3[tot]=mm*mm%mod*(mm+1)%mod*(mm+1)%mod*inv4%mod-1;
            if(m<=sq)
                id1[m]=tot;
            else
                id2[n/m]=tot;
            ++tot;
        }
        for(int i=1;i<=cnt;++i)
        {
            for(int j=0;j<tot && p[i]*p[i]<=w[j];++j)
            {
                ll t=getid(w[j]/p[i]);
                g0[j]=(g0[j]-(g0[t]-sum0[i-1])%mod)%mod;
                g1[j]=(g1[j]-p[i]*(g1[t]-sum1[i-1])%mod)%mod;
                g2[j]=(g2[j]-p[i]*p[i]%mod*(g2[t]-sum2[i-1])%mod)%mod;
                g3[j]=(g3[j]-p[i]*p[i]%mod*p[i]%mod*(g3[t]-sum3[i-1])%mod)%mod;
            }
        }//g_i表示素数i次幂和
        //下面是积性函数求和部分
        rep(i,0,tot-1) G[i]=((g1[i]-g0[i])%mod+mod)%mod;//G[i]表示1到i中所有积性函数在素数点值的和
        repd(j,cnt,1)
            rep(i,0,tot-1)
            {
                if((ll)p[j]*p[j]>w[i]) break;
                for(ll k=p[j],c=1; k*p[j]<=w[i]; ++c,k*=p[j],(G[i]+=calc(j,c))%=mod)
                    (G[i]+=(calc(j,c))%mod*(G[getid(w[i]/k)]-(g1[getid(p[j])]-g0[getid(p[j])])%mod+mod)%mod)%=mod;//后面减掉的部分是函数在前j个数组处值的和
            }

    }
    ll get(ll x)
    {
        return G[getid(x)]+1;
    }
    ll cal0(ll r)
    {
        return (g0[getid(r)])%mod;
    }
    ll cal1(ll r)
    {
        return (g1[getid(r)])%mod;
    }
    ll cal2(ll r)
    {
        return (g2[getid(r)])%mod;
    }
    ll cal3(ll r)
    {
        return (g3[getid(r)])%mod;
    }
}m2;
