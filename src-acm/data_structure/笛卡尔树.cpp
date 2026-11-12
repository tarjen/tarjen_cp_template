// 手抄版：沿用原算法与类封装；//? 标记为按需抄写。
// 用法：
// 本例 ve[1][0] = 0，ve[1][1] = 2。
// 节点 0base；空树、空孩子为 -1；相等时靠右的节点在上。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template <class T = ll>
struct CartesianTree {
    int n, root;
    vector<T> a;
    vector<vector<int>> ve;

    void build() {
        ve.assign(n, vector<int>(2, -1));
        vector<int> st;
        st.reserve(n);
        for (int i = 0; i < n; i++) {
            int last = -1;
            while (!st.empty() && a[st.back()] >= a[i]) {
                last = st.back();
                st.pop_back();
            }
            ve[i][0] = last;
            if (!st.empty()) ve[st.back()][1] = i;
            st.push_back(i);
        }
        root = st.empty() ? -1 : st[0];
    }

    CartesianTree(const vector<T>& _a) : n(_a.size()), a(_a) { build(); }
};
