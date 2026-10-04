// 1base；SegmentTree tr(n)初值为0，或tr(a)接收1base数组；update/query省略根编号。
#include <bits/stdc++.h>
using namespace std;
const long long inf = numeric_limits<long long>::max();
struct Node{
    int l,r; long long res=0,tag=0; bool has_tag=false;
};
struct SegmentTree{
    int n;
    vector<Node> a;
    explicit SegmentTree(int n): n(n),a(4*n+4) { if(n) build(1,1,n); }
    // 输入v为1base，v[0]不参与计算。
    explicit SegmentTree(const vector<long long>& v): SegmentTree((int)v.size()-1) {
        if(n) load(1,v);
    }
    void load(int i,const vector<long long>& v) {
        if(a[i].l==a[i].r) {
            a[i].res=v[a[i].l];

            return;
        }
        load(i*2,v); load(i*2+1,v); pushup(i);
    }

    void tag_init(int i){
        a[i].has_tag=false;
    }
    void tag_union(int fa,int i){
        if(a[fa].has_tag) a[i].tag=a[fa].tag,a[i].has_tag=true;
    }
    void tag_cal(int i){
        if(a[i].has_tag) a[i].res=a[i].tag;
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
    }
    void build(int i,int l,int r){
        a[i].l=l,a[i].r=r;tag_init(i);a[i].res=0;
        if(l>=r)return;
        int mid=(l+r)/2;
        build(i*2,l,mid);
        build(i*2+1,mid+1,r);
    }
    void update(int i,int l,int r,long long w){
        pushdown(i);
        if(a[i].r<l||a[i].l>r||l>r)return;
        if(a[i].l>=l&&a[i].r<=r){
            a[i].tag=w; a[i].has_tag=true;
            return;
        }
        update(i*2,l,r,w);
        update(i*2+1,l,r,w);
        pushup(i);
    }
    long long query(int i,int l,int r){
        pushdown(i);
        if(a[i].r<l||a[i].l>r||l>r)return inf;
        if(a[i].l>=l&&a[i].r<=r){
            return a[i].res;
        }
        return min(query(i*2,l,r),query(i*2+1,l,r));
    }
void update(int l,int r,long long w) { if(n) update(1,l,r,w); }
    long long query(int l,int r) { return n?query(1,l,r):inf; }
};
