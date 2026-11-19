/*
用户要求：最小环封装成接收二维 vector 的接口；保留原 Floyd 算法。
枚举环上编号最大的点，先计算最小环，再用该点更新最短路。
*/
// 用法：非负权无向图，0base 对称邻接矩阵，无边为 INT_MAX，对角线忽略。
// vector<vector<int>> a = {{0,2,4}, {2,0,3}, {4,3,0}};
// long long ans = min_cycle(a);  // 9；无环返回 -1，不修改 a。
// 可用 min_cycle(a, inf) 指定无边标记，所有边权须小于 inf。
// 仅考虑至少三个点的简单环，不计自环、重边二元环；时间 O(n^3)，空间 O(n^2)。
#include <bits/stdc++.h>
using namespace std;
long long min_cycle(const vector<vector<int>>& a, int inf = INT_MAX) {
    int n = a.size();
    const long long INF = 1LL << 60;
    vector<vector<long long>> b(n, vector<long long>(n, INF));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            if (a[i][j] < inf) b[i][j] = a[i][j];
        b[i][i] = 0;
    }
    long long ans = INF;
    for (int i = 0; i < n; i++) {
        // b[j][k] 的中间点均小于 i，因此与两条原边拼成简单环。
        for (int j = 0; j < i; j++)
            for (int k = j + 1; k < i; k++)
                if (a[i][j] < inf && a[i][k] < inf && b[j][k] < INF)
                    ans = min(ans, (long long)a[i][j] + a[i][k] + b[j][k]);
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                if (b[j][i] < INF && b[i][k] < INF)
                    b[j][k] = min(b[j][k], b[j][i] + b[i][k]);
    }
    return ans == INF ? -1 : ans;
}
