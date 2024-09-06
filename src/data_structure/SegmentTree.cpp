//?????????? ???????>=??sum??????
#include <bits/stdc++.h>
using namespace std;
const int maxn=1e6+10;
struct Node{
    int l,r,res,tag;  
};
struct SegmentTree{
    Node a[maxn*4];
    void tag_init(int i){
        a[i].tag=0;
    }
    void tag_union(int fa,int i){
        a[i].tag+=a[fa].tag;
    }
    void tag_cal(int i){
        a[i].res+=a[i].tag*(a[i].r-a[i].l+1);
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
        a[i].res=a[i*2].res+a[i*2+1].res;
    }
    void build(int i,int l,int r){
        a[i].l=l,a[i].r=r;tag_init(i);
        if(l>=r)return;
        int mid=(l+r)/2;
        build(i*2,l,mid);
        build(i*2+1,mid+1,r);
    }
    void update(int i,int l,int r,int w){
        pushdown(i);
        if(a[i].r<l||a[i].l>r||l>r)return;
        if(a[i].l>=l&&a[i].r<=r){
            a[i].tag=w;
            return;
        }
        update(i*2,l,r,w);
        update(i*2+1,l,r,w);
        pushup(i);
    }
    int query(int i,int l,int r){
        pushdown(i);
        if(a[i].r<l||a[i].l>r||l>r)return 0;
        if(a[i].l>=l&&a[i].r<=r){
            return a[i].res;
        }
        return query(i*2,l,r)+query(i*2+1,l,r);
    }
    int min_right(int qL, int& nowsum,int querysum, int i) {//???????>=sum???
        pushdown(i);
        if (a[i].r < qL)return -1;
        if (qL <= a[i].l) {
            int ss = nowsum+a[i].res;
            if (ss<querysum) {
                nowsum = ss;
                return -1;
            }
            if (a[i].l == a[i].r)return a[i].l;
        }
        int pos = min_right(qL, nowsum,querysum,i*2);
        if (pos != -1)return pos;
        return min_right(qL, nowsum,querysum,2*i+1);
    }
    int max_left(int qR,int &nowsum,int querysum,int i){//???????>=sum???
        pushdown(i);
        if(a[i].l > qR)return -1;
        if(qR>=a[i].r){
            int ss=nowsum+a[i].res;
            if(ss<querysum){
                nowsum=ss;
                return -1;
            }
            if(a[i].l==a[i].r)return a[i].r;
        }
        int pos=max_left(qR,nowsum,querysum,i*2+1);
        if(pos!=-1)return pos;
        return max_left(qR,nowsum,querysum,i*2);
    }
};
SegmentTree tri;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,q;cin>>n>>q;
    tri.build(1,1,n);
    for(int i=1;i<=n;i++){
        int x;cin>>x;tri.update(1,i,i,x);
    }
    while(q--){
        int ops;cin>>ops;
        if(ops==1){
            int l,r,x;cin>>l>>r>>x;
            tri.update(1,l,r,x);
        }
        if(ops==2){
            int l,r;cin>>l>>r;
            cout<<tri.query(1,l,r)<<"\n";
        }
        if(ops==3){
            int x,sum;cin>>x>>sum;
            int nowsum=0;
            cout<<tri.min_right(x,nowsum,sum,1)<<"\n";
        }
        if(ops==4){
            int x,sum;cin>>x>>sum;
            int nowsum=0;
            cout<<tri.max_left(x,nowsum,sum,1)<<"\n";
        }
    }
}
