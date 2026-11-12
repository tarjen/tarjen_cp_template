// 手抄版：沿用原算法与类封装；//? 标记为按需抄写。
// 用法：
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
struct WeightedDSU {
    vector<int> f;
    vector<ll> dis;
    WeightedDSU(int n) : f(n), dis(n) { iota(f.begin(), f.end(), 0); }
    int getf(int x) {
        if (x == f[x]) return x;
        int old = f[x], z = getf(old);
        dis[x] += dis[old];
        return f[x] = z;
    }
    // 约束dis(i)-dis(j)=len；同一集合时返回约束是否一致。
    bool unit(int i, int j, ll len) {
        int x = getf(i), y = getf(j);
        if (x == y) return dis[i] - dis[j] == len;
        f[x] = y;
        dis[x] = dis[j] - dis[i] + len;
        return true;
    }
};
