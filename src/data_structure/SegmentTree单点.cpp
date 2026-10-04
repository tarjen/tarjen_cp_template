// 1base；SegmentTree tr(n)初值为0，或tr(a)接收1base数组；update/query省略根编号。
//单点赋值、区间求和；非负元素上支持线段树二分。
#include <bits/stdc++.h>
using namespace std;
struct Node{
    int l,r; long long res=0;
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

    void pushup(int i){
        if(a[i].l==a[i].r)return;
        a[i].res=a[i*2].res+a[i*2+1].res;
    }
    void build(int i,int l,int r){
        a[i].l=l,a[i].r=r;a[i].res=0;
        if(l>=r)return;
        int mid=(l+r)/2;
        build(i*2,l,mid);
        build(i*2+1,mid+1,r);
    }
    void update(int i,int x,long long w){
        if(a[i].r<x||a[i].l>x)return;
        if(a[i].l>=x&&a[i].r<=x){
            a[i].res=w;
            return;
        }
        update(i*2,x,w);
        update(i*2+1,x,w);
        pushup(i);
    }
    long long query(int i,int l,int r){
        if(a[i].r<l||a[i].l>r||l>r)return 0;
        if(a[i].l>=l&&a[i].r<=r){
            return a[i].res;
        }
        return query(i*2,l,r)+query(i*2+1,l,r);
    }
    int min_right(int qL, long long& nowsum,long long querysum, int i) {//从左往右第一个>=sum的位置
        if (a[i].r < qL)return -1;
        if (qL <= a[i].l) {
            long long ss = nowsum+a[i].res;
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
    int max_left(int qR,long long &nowsum,long long querysum,int i){//从右往左第一个>=sum的位置
        if(a[i].l > qR)return -1;
        if(qR>=a[i].r){
            long long ss=nowsum+a[i].res;
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
void update(int x,long long w) { if(n) update(1,x,w); }
    long long query(int l,int r) { return n?query(1,l,r):0; }
    // 二分要求所累加的元素非负，且need>0；找不到返回-1。
    int min_right(int l,long long need) { long long sum=0; return n?min_right(l,sum,need,1):-1; }
    int max_left(int r,long long need) { long long sum=0; return n?max_left(r,sum,need,1):-1; }
};
