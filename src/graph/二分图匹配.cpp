// 两侧独立1base；Matching mat(n,m); add(u,v); maxmatch();
// match[v]与left[u]为匹配方案。
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
