// 用法：
// EXKMP tr("ababa", "aba");  // 参数顺序：文本、模式串。
// int length = tr.extend[0];  // 文本后缀与模式串的 LCP 长度为 3。
// int z = tr.next[2];  // 模式串后缀与自身的 LCP 长度为 1。
// extend 对应文本位置，next 对应模式串位置，均 0base；构造即计算。
#include <bits/stdc++.h>
using namespace std;
struct EXKMP {
    string S, T;
    vector<int> next, extend;
    EXKMP(const string& text, const string& pattern)
        : S(text), T(pattern), next(T.size()), extend(S.size()) {
        Get_Next();
        ExKMP();
    }
    void Get_Next() {
        int m = T.size();
        if (!m) return;
        next[0] = m;
        for (int i = 1, l = 0, r = -1; i < m; i++) {
            if (i <= r) next[i] = min(r - i + 1, next[i - l]);
            while (i + next[i] < m && T[next[i]] == T[i + next[i]]) next[i]++;
            if (i + next[i] - 1 > r) l = i, r = i + next[i] - 1;
        }
    }
    void ExKMP() {
        fill(extend.begin(), extend.end(), 0);
        int n = S.size(), m = T.size();
        for (int i = 0, l = 0, r = -1; i < n; i++) {
            if (i <= r) extend[i] = min(r - i + 1, next[i - l]);
            while (extend[i] < m && i + extend[i] < n &&
                   T[extend[i]] == S[i + extend[i]])
                extend[i]++;
            if (i + extend[i] - 1 > r) l = i, r = i + extend[i] - 1;
        }
    }
};
