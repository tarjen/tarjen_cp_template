#include <bits/stdc++.h>
using namespace std;
const int maxn=4e5+10;
struct Treearray{
    int c[maxn],n;
    void set_n(int _n){
        n=_n;
        for(int i=1;i<=n;i++)c[i]=0;
    }
    int lowbit(int x){
        return x&(-x);
    }
    void update(int i,int k){    //在i位置加上k
        while(i <= n){
            c[i] += k;
            i += lowbit(i);
        }
    }
    int getsum(int i){        //求A[1 - i]的和
        int res = 0;
        while(i > 0){
            res += c[i];
            i -= lowbit(i);
        }
        return res;
    }
};
Treearray tri;
int a[maxn],b[maxn],c[maxn];
int n,k; 
int ans[maxn],id[maxn],cnt[maxn],t[maxn];
void subdiv(int l,int r){
    if(l==r)return;
    int mid=(l+r)/2;
    subdiv(l,mid);
    subdiv(mid+1,r);
    sort(id+l,id+mid+1,[&](int x,int y){
        if(b[x]==b[y])return c[x]<c[y];
        return b[x]<b[y];
    });
    sort(id+mid+1,id+r+1,[&](int x,int y){
        if(b[x]==b[y])return c[x]<c[y];
        return b[x]<b[y];
    });

    // for(int i=l;i<=r;i++)cout<<id[i]<<" \n"[i==r];
    assert(tri.getsum(tri.n)==0);
    for(int i=l,j=mid+1;i<=mid||j<=r;){
        if(j!=r+1&&(i==mid+1||b[id[i]]>b[id[j]])){
            // cout<<"id="<<id[j]<<" +"<<tri.getsum(c[id[j]])<<"\n";
            ans[id[j]]+=tri.getsum(c[id[j]]);
            j++;
        }
        else{
            tri.update(c[id[i]],t[id[i]]);
            i++;
        }
    }
    for(int i=l;i<=mid;i++)tri.update(c[id[i]],-t[id[i]]);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>k;
    tri.set_n(200000);
    vector<tuple<int,int,int>> v(n);
    for(int i=0;i<n;i++){
        int x,y,z;cin>>x>>y>>z;v[i]=make_tuple(x,y,z);
    }
    sort(v.begin(),v.end());
    int g=0;
    for(int i=0;i<n;i++){
        int j=i;
        while(j+1<n&&v[i]==v[j+1])j++;
        g++;
        a[g]=get<0>(v[i]);
        b[g]=get<1>(v[i]);
        c[g]=get<2>(v[i]);
        t[g]=j-i+1;
        i=j;
        // cout<<"g="<<g<<" "<<a[g]<<" "<<b[g]<<" "<<c[g]<<"\n";
    }
    for(int i=1;i<=g;i++)id[i]=i;
    subdiv(1,g);
    for(int i=1;i<=g;i++){
        cnt[ans[i]+t[i]-1]+=t[i];
        // cout<<"i="<<i<<" ans="<<ans[i]<<"\n";
    }
    for(int i=0;i<n;i++)cout<<cnt[i]<<"\n";
    return 0;
}
