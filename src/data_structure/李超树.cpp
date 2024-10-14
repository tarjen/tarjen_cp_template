#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double lf;
const int maxn=40000+10;
struct Line{
    lf k,b;
    int id;
    lf y(int x){
        return k*x+b;
    }
};
const Line inf = {0,-2e9,0};
struct Node{
    int l,r;
    Line res;  
};
const lf eps=1e-9;
int linecmp(Line l1,Line l2,int x){// l1>l2 return 1
    lf y1=l1.y(x),y2=l2.y(x);
    if(y1>y2||(fabs(y1-y2)<eps&&l1.id<l2.id))return 1;
    return 0;
}
struct SegmentTree{
    Node a[maxn*4];
    void build(int i,int l,int r){
        a[i].l=l,a[i].r=r;a[i].res=inf;
        if(l>=r)return;
        int mid=(l+r)/2;
        build(i*2,l,mid);
        build(i*2+1,mid+1,r);
    }
    void upd(int i,Line line){
        if(linecmp(line,a[i].res,(a[i].l+a[i].r)/2))swap(a[i].res,line);
        int opl=linecmp(line,a[i].res,a[i].l);
        int opr=linecmp(line,a[i].res,a[i].r);
        if(opl&&opr){a[i].res=line;return;}
        if((!opl)&&(!opr))return;
        if(opl)upd(i*2,line);
        if(opr)upd(i*2+1,line);
    }
    void update(int i,int l,int r,Line line){
        if(a[i].r<l||a[i].l>r||l>r)return;
        if(a[i].l>=l&&a[i].r<=r){
            upd(i,line);
            return;
        }
        update(i*2,l,r,line);
        update(i*2+1,l,r,line);
    }
    void query(int i,int x,Line &line){
        if(a[i].r<x||a[i].l>x)return;
        if(linecmp(a[i].res,line,x))line=a[i].res; 
        if(a[i].l==a[i].r)return;
        query(i*2,x,line);
        query(i*2+1,x,line);
    }
};
SegmentTree tri;