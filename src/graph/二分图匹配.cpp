// 用法：
// Matching tr(2, 2);  // 左右两侧分别使用 [1,2]。
// tr.add(1, 1);
// tr.add(2, 2);  // 参数是左节点、右节点。
// int count = tr.maxmatch();  // 最大匹配边数为 2。
// int right = tr.left[1];  // 左点 1 匹配右点 1；match[v] 保存对应左点。
// 未匹配为 0；maxmatch 自动重置求解状态。
#include <bits/stdc++.h>
using namespace std;

struct Matching {
    int n, m;
    vector<vector<int>> ve;
    vector<int> match, left;
    vector<char> st;
    Matching(int n, int m)
        : n(n), m(m), ve(n + 1), match(m + 1), left(n + 1), st(m + 1) {}
    void add(int u, int v) { ve[u].push_back(v); }
    void addedge(int u, int v) { add(u, v); }
    bool find(int x) {
        for (int v : ve[x])
            if (!st[v]) {
                st[v] = 1;
                if (!match[v] || find(match[v])) {
                    match[v] = x;
                    return true;
                }
            }
        return false;
    }
    int maxmatch() {
        fill(match.begin(), match.end(), 0);
        fill(left.begin(), left.end(), 0);
        int ans = 0;
        for (int u = 1; u <= n; u++) {
            fill(st.begin(), st.end(), 0);
            ans += find(u);
        }
        for (int v = 1; v <= m; v++)
            if (match[v]) left[match[v]] = v;
        return ans;
    }
};
