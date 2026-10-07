// 用法：
// WeightedDSU tr(3);  // 节点 [0,2]。
// bool ok = tr.unit(0, 1, 5);  // 加入约束 value[0]-value[1]=5。
// tr.unit(1, 2, 2);
// bool consistent = tr.unit(0, 2, 7);  // true；矛盾约束返回 false。
// tr.getf(0);
// tr.getf(2);  // 压缩后 dis[x] 为 x 到代表元的势差。
// ll delta = tr.dis[0] - tr.dis[2];  // 同集合时即 value[0]-value[2]=7。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
struct WeightedDSU {
    vector<int> f;
    vector<ll> dis;
    explicit WeightedDSU(int n) : f(n), dis(n) { iota(f.begin(), f.end(), 0); }
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
