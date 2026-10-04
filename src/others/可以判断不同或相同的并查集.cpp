// 1base；RelationDSU dsu(n); merge(x,y)表示相同，merge(x,-y)表示不同。
#include <bits/stdc++.h>
using namespace std;
struct RelationDSU {
    vector<int> f;
    explicit RelationDSU(int n): f(n+1) { iota(f.begin(),f.end(),0); }
int getf(int x){
    if(x<0)return -getf(-x);
    if(x==f[x])return x;
    else return f[x]=getf(f[x]);
}
bool merge(int x,int y){//如果是x!=y将y取反(x>0 y>0)
    x=getf(x),y=getf(y);
    if(x==-y)return false;
    if(x==y)return true;
    if(x<0)f[-x]=-y;
    else f[x]=y;
    return true;
}
};
