// 小写字母；PAM pam(s)或PAM pam; pam.insert(c); 不在模板内部输出。
#include <bits/stdc++.h>
using namespace std;

struct PAM {
    struct Node {
        array<int, 26> ch{};
        int fail = 0, len = 0, num = 0;
    };
    vector<Node> b;
    vector<int> s;
    int n = 0, last = 0, cnt = 1;
    explicit PAM(int reserve_length = 0) : b(2), s(1, -1) {
        b[0].len = 0;
        b[0].fail = 1;
        b[1].len = -1;
        b.reserve(reserve_length + 2);
        s.reserve(reserve_length + 1);
    }
    explicit PAM(const string& text) : PAM((int)text.size()) {
        for (char c : text) insert(c);
    }
    int get_fail(int x) const {
        while (s[n - b[x].len - 1] != s[n]) x = b[x].fail;
        return x;
    }
    // 返回以当前字符结尾的最长回文状态；b[last].num为回文后缀数量。
    int insert(char ch) {
        int c = ch - 'a';
        assert(0 <= c && c < 26);
        s.push_back(c);
        n++;
        int p = get_fail(last);
        if (!b[p].ch[c]) {
            int tmp = get_fail(b[p].fail);
            Node node;
            node.len = b[p].len + 2;
            node.fail = b[tmp].ch[c];
            node.num = b[node.fail].num + 1;
            b.push_back(node);
            b[p].ch[c] = ++cnt;
        }
        return last = b[p].ch[c];
    }
};
