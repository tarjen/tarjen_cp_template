// 用法：
// MobiusSieve tr(20);  // 构造即预处理 [1,20]。
// int mu = tr.mul[6];  // 莫比乌斯函数为 1。
// int phi = tr.phi[6];  // 欧拉函数为 2。
// int prime = tr.pr[1];  // 首个质数为 2；pr 的第 0 格不用。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct MobiusSieve {
    int n, tot = 0;
    vector<int> pr, mul, phi;
    vector<char> vis;
    explicit MobiusSieve(int n)
        : n(n), pr(1, 0), mul(n + 1), phi(n + 1), vis(n + 1) {
        if (n == 0) return;
        mul[1] = phi[1] = 1;
        for (int i = 2; i <= n; i++) {
            if (!vis[i]) {
                mul[i] = -1;
                pr.push_back(i);
                ++tot;
                phi[i] = i - 1;
            }
            for (int j = 1; j <= tot && (ll)pr[j] * i <= n; j++) {
                int num = pr[j] * i;
                vis[num] = 1;
                mul[num] = -mul[i];
                phi[num] = phi[i] * phi[pr[j]];
                if (i % pr[j] == 0) {
                    phi[num] = pr[j] * phi[i];
                    mul[num] = 0;
                    break;
                }
            }
        }
    }
};
