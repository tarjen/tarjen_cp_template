#include <bits/stdc++.h>
using namespace std;
#define int long long 
const int maxn=1e6+10;
const int inf =2e9;
struct Node{
    int l,r,res,tag,tag2,res2;
};
struct SegmentTree{
    Node a[maxn*4];
    void tag_init(int i){
        a[i].tag=a[i].tag2=0;
    }
    void tag_union(int fa,int i){
        if(a[fa].tag2<0)a[i].tag2=min(a[i].tag2,a[i].tag+a[fa].tag2);
        a[i].tag+=a[fa].tag;
    }
    void tag_cal(int i){
        if(a[i].tag2<0)a[i].res2=min(a[i].res2,a[i].res+a[i].tag2);
        a[i].res+=a[i].tag;
    }
    void pushdown(int i){
        tag_cal(i);
        if(a[i].l!=a[i].r){
            tag_union(i,i*2);
            tag_union(i,i*2+1);
        }
        tag_init(i);
    }
    void pushup(int i){
        if(a[i].l==a[i].r)return;
        pushdown(i*2);
        pushdown(i*2+1);
        a[i].res=min(a[i*2].res,a[i*2+1].res);
        a[i].res2=min(a[i*2].res2,a[i*2+1].res2);
    }
    void build(int i,int l,int r){
        a[i].l=l,a[i].r=r;tag_init(i);
        if(l>=r)return;
        int mid=(l+r)/2;
        build(i*2,l,mid);
        build(i*2+1,mid+1,r);
    }
    void update(int i,int l,int r,int w){
        if(a[i].r<l||a[i].l>r||l>r)return;
        pushdown(i);
        if(a[i].l>=l&&a[i].r<=r){
            a[i].tag+=w;
            a[i].tag2=min(a[i].tag2,a[i].tag);
            return;
        }
        update(i*2,l,r,w);
        update(i*2+1,l,r,w);
        pushup(i);
    }
    int query(int i,int l,int r){
        pushdown(i);
        if(a[i].r<l||a[i].l>r||l>r)return inf;
        if(a[i].l>=l&&a[i].r<=r){
            return a[i].res2;
        }
        return min(query(i*2,l,r),query(i*2+1,l,r));
    }
};
SegmentTree tri;
signed main()
{
    int n,m;
    cin>>n>>m;
    tri.build(1,1,n);
    for(int i=1;i<=m;i++){
        int ops;cin>>ops;
        if(ops==1){
            int l,r,x;cin>>l>>r>>x;
            tri.update(1,l,r,x);
        }
        else{
            int l,r;cin>>l>>r;
            cout<<tri.query(1,l,r)<<"\n";
        }
    }
    return 0;
}