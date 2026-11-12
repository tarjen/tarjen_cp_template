// 手抄版：保留说明与用法，适度压行；//? 为按需代码，调用可选接口前需恢复对应函数组。
// 用法：
// KMP tr("aba");
// vector<int> positions = tr.find("ababa");  // {1,3}，允许重叠匹配。
// 输入普通 string；返回起始位置 1base，nxt 也是 1base。
#include <bits/stdc++.h>
using namespace std;

struct KMP {
    int n;
    string s;
    vector<int> nxt;
    KMP(const string& pattern)
        : n(pattern.size()), s(" " + pattern), nxt(n + 1) {
        for (int i = 2, j = 0; i <= n; i++) {
            while (j && s[i] != s[j + 1]) j = nxt[j];
            if (s[i] == s[j + 1]) j++;
            nxt[i] = j;
        }
    }
    // 返回匹配起点（1base），包含重叠匹配；空模式匹配所有n+1个边界。
    vector<int> find(const string& text) const {
        vector<int> ans;
        if (!n) {
            ans.resize(text.size() + 1);
            iota(ans.begin(), ans.end(), 1);
            return ans;
        }
        for (int i = 0, j = 0; i < (int)text.size(); i++) {
            while (j && text[i] != s[j + 1]) j = nxt[j];
            if (text[i] == s[j + 1]) j++;
            if (j == n) {
                ans.push_back(i - n + 2);
                j = nxt[j];
            }
        }
        return ans;
    }
};
