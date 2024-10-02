#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct Runs {
    int l, r, p;
};
namespace RunsGetter {
    const int N = 2e5 + 5;
    using namespace std;
    struct StrHash{
        ll p[N],h[N];int mod,buf;
        StrHash (int _buf,int _mod){buf=_buf;mod=_mod;}
        void Init(char *s,int n)
        {
            p[0]=1;
            for (int i=1;i<=n;i++){
                p[i]=p[i-1]*buf%mod;
                h[i]=(h[i-1]*buf+s[i]-'a'+1)%mod;
            }
        }
        bool tl(int u,int v,int len){
            return (h[u]-h[v]+(h[v-len]-h[u-len])*p[len])%mod==0;
        }
        bool tr(int u,int v,int len){
            return (h[u+len-1]-h[v+len-1]+(h[v-1]-h[u-1])*p[len])%mod==0;
        }
        int get(int l,int r){
            return (h[r]+(mod-h[l-1])*p[r-l+1])%mod;
        }
    }h1(10,1000000007),h2(13,1000000009);
        int n;char s[N];
    int extl(int u,int v){
        if (s[u]!=s[v])return 0;
        int l=1,r=min(u,v),mid;
        while(l<r){
            mid=(l+r+1)>>1;
            if (h1.tl(u,v,mid)&&h2.tl(u,v,mid))l=mid;
            else r=mid-1;
        }return l;
    }
    int extr(int u,int v)
    {
        if (s[u]!=s[v])return 0;
        int l=1,r=n-max(u,v)+1,mid;
        while(l<r){
            mid=(l+r+1)>>1;
            if (h1.tr(u,v,mid)&&h2.tr(u,v,mid))l=mid;
            else r=mid-1;
        }
        return l;
    }
    Runs b[N*20];
    bool cmpR(const Runs &A, const Runs &B)
    {return A.l==B.l ? (A.r==B.r  ? A.p<B.p : A.r<B.r) : A.l<B.l;}
    int tot;
    int chk(int u,int v)
    {
        int tl=extl(u,v),tr=extr(u,v);
        if (tl+tr>=v-u+1){
            b[++tot]=(Runs){u-tl+1,v+tr-1,v-u};
            return v+tr-1;
        }
        return 0;
    }
    vector<Runs> getRuns(int n0, char* t0)
    {
        n=n0;
        for(int i=1;i<=n0;i++)s[i]=t0[i];
        h1.Init(s,n);h2.Init(s,n);
        for (int p=1;p<=n;p++)
            for (int k=p,mx=0;k+p<=n;k+=p)
            if (mx<k)
                mx=max(mx,chk(k,k+p)-p);
        sort(b+1,b+tot+1,cmpR);
        int m=0;
        for (int i=1;i<=tot;i++)
            if (b[i].l!=b[i-1].l||b[i].r!=b[i-1].r)
            b[++m]=b[i];
        tot=m;
        vector<Runs> e;
        for(int i=1;i<=m;i++)e.push_back(b[i]);
        return e;
    }
}