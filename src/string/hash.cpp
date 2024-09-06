const int N=1e6+10;
typedef long long ll;
const ll p1=31,p2=131;
const ll mod1=1e9+7,mod2=1e9+9;
typedef pair<ll,ll> hs;
const hs p = make_pair(p1,p2);
hs &operator+=(hs &a, hs b) {
    a.first=(a.first+b.first)%mod1;
    a.second=(a.second+b.second)%mod2;
    return a;
}
hs operator+(hs a, hs b) { return a += b; }
hs &operator-=(hs &a, hs b) {
    a.first=(a.first-b.first+mod1)%mod1;
    a.second=(a.second-b.second+mod2)%mod2;
    return a;
}
hs operator-(hs a, hs b) { return a -= b; }
hs &operator*=(hs &a, hs b) {
    a.first=(a.first*b.first)%mod1;
    a.second=(a.second*b.second)%mod2;
    return a;
}
hs operator*(hs a, hs b) { return a *= b; }
struct Hash{
    int n;
    vector<hs>has1,has2,Pow;
    void Hash_init(string &s){
        n=(int)s.size();
        Pow.resize(n+2);
        has1.resize(n+2);
        has2.resize(n+2);
        Pow[0]=make_pair(1ll,1ll);
        for(int i=1;i<=n;i++)Pow[i]=Pow[i-1]*p;
        for(int i=1;i<=n;i++)has1[i]=has1[i-1]*p+hs{s[i-1]-'a'+1,s[i-1]-'a'+1};
        for(int i=n;i>=1;i--)has2[i]=has2[i+1]*p+hs{s[i-1]-'a'+1,s[i-1]-'a'+1};
    }
    hs get1(int l,int r){
        return has1[r]-has1[l-1]*Pow[r-l+1];
    }
    hs get2(int l,int r){
        return has2[l]-has2[r+1]*Pow[r-l+1];
    }
};