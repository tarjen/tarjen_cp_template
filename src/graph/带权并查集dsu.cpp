// 1base；WeightedDSU dsu(n);
#include <bits/stdc++.h>
using namespace std;

struct WeightedDSU {
    vector<int> f;
    vector<long long> dis;
    explicit WeightedDSU(int n): f(n+1),dis(n+1) { iota(f.begin(),f.end(),0); }
    int getf(int x) {
        if(x==f[x]) return x;
        int old=f[x],z=getf(old);
        dis[x]+=dis[old];
        return f[x]=z;
    }
    // 约束dis(i)-dis(j)=len；同一集合时返回约束是否一致。
    bool unit(int i,int j,long long len) {
        int x=getf(i),y=getf(j);
        if(x==y) return dis[i]-dis[j]==len;
        f[x]=y; dis[x]=dis[j]-dis[i]+len;
        return true;
    }
};
