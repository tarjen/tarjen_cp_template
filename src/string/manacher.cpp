// 用法：
// Manacher tr("ababa");  // 普通 string，构造即计算。
// int longest = tr.manacher();  // 最长回文长度为 5。
// bool palindrome = tr.is_palindrome(2, 4);  // "bab"，结果 true。
// 查询使用原串 1base 闭区间；Len 是变换串半径，不是原串位置数组。
#include <bits/stdc++.h>
using namespace std;

struct Manacher {
    string s;
    vector<int> str, Len;
    int len, ans = 0;
    explicit Manacher(const string& s)
        : s(s), str(2 * s.size() + 3), Len(str.size()) {
        // 字符映射为非负整数，负数分隔符与任意输入字节都不冲突。
        str[0] = -2;
        int k = 1;
        for (unsigned char c : s) str[k++] = -1, str[k++] = c;
        str[k++] = -1;
        str[k] = -3;
        len = k;
        for (int i = 1, mx = 0, id = 0; i < len; i++) {
            Len[i] = mx > i ? min(mx - i, Len[2 * id - i]) : 1;
            while (str[i + Len[i]] == str[i - Len[i]]) Len[i]++;
            if (i + Len[i] > mx) mx = i + Len[i], id = i;
            ans = max(ans, Len[i] - 1);
        }
    }
    int manacher() const { return ans; }
    // 原串1base闭区间，O(1)判断回文；变换串0为左哨兵。
    bool is_palindrome(int l, int r) const {
        return l > r || Len[l + r] >= r - l + 2;
    }
};
using ST = Manacher;
