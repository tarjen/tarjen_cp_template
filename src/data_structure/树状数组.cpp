// 1base；RangeTreearray tr(n); 区间加、区间求和；初值为0。
#include <bits/stdc++.h>
using namespace std;

struct RangeTreearray {
    int n;
    vector<long long> tree1,tree2;
    explicit RangeTreearray(int n): n(n),tree1(n+1),tree2(n+1) {}
    // 输入a为1base，a[0]不参与计算。
    explicit RangeTreearray(const vector<long long>& a): RangeTreearray((int)a.size()-1) {
        for(int i=1;i<=n;i++) add(i,a[i]-(i==1?0:a[i-1]));
    }
    void add(int x,long long k) {
        assert(x>=1);
        for(int i=x;i<=n;i+=i&-i) tree1[i]+=k,tree2[i]+=(x-1)*k;
    }
    void update(int l,int r,long long k) { if(l<=r) add(l,k),add(r+1,-k); }
    long long getsum(int x) const {
        long long ans=0;
        for(int i=x;i>0;i-=i&-i) ans+=tree1[i]*x-tree2[i];
        return ans;
    }
    long long query(int l,int r) const { return getsum(r)-getsum(l-1); }
};
