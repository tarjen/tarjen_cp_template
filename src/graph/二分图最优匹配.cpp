// 1base完整n*n权值矩阵；KM km(weights); km.maxmatch();
// 求最大权完美匹配；权值不可作缺边哨兵。
#include <bits/stdc++.h>
using namespace std;
struct KM {
    int n;
    vector<vector<long long>> a;
    vector<long long> lx, ly;
    vector<int> link;
    vector<char> vx, vy;
    explicit KM(const vector<vector<long long>>& weights)
        : n((int)weights.size() - 1),
          a(weights),
          lx(n + 1),
          ly(n + 1),
          link(n + 1, -1),
          vx(n + 1),
          vy(n + 1) {}
    int dfs(int x) {
        if (x == -1) return 0;
        vx[x] = 1;
        for (int i = 1; i <= n; i++) {
            if (!vy[i] && lx[x] + ly[i] == a[x][i]) {
                vy[i] = 1;
                if (link[i] == -1 || dfs(link[i])) {
                    link[i] = x;
                    return 1;
                }
            }
        }
        return 0;
    }
    bool deal() {
        fill(ly.begin(), ly.end(), 0);
        fill(lx.begin(), lx.end(), numeric_limits<long long>::lowest() / 4);
        fill(link.begin(), link.end(), -1);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) lx[i] = max(lx[i], a[i][j]);
        }
        for (int i = 1; i <= n; i++) {
            while (1) {
                fill(vx.begin(), vx.end(), 0);
                fill(vy.begin(), vy.end(), 0);
                if (dfs(i)) break;
                long long delta = numeric_limits<long long>::max() / 4;
                for (int j = 1; j <= n; j++) {
                    if (vx[j] == 1)
                        for (int k = 1; k <= n; k++)
                            if (vy[k] == 0)
                                delta = min(delta, lx[j] + ly[k] - a[j][k]);
                }
                if (delta == numeric_limits<long long>::max() / 4) return 0;
                for (int j = 1; j <= n; j++)
                    if (vx[j] == 1) lx[j] -= delta;
                for (int k = 1; k <= n; k++)
                    if (vy[k] == 1) ly[k] += delta;
            }
        }
        return 1;
    }
    long long maxmatch() {
        if (!deal()) throw runtime_error("No perfect matching");
        long long ans = 0;
        for (int v = 1; v <= n; v++) ans += a[link[v]][v];
        return ans;
    }
};
