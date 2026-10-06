// 用法：
// PAM tr(string("ababa"));  // 小写字母，构造即逐字插入。
// int distinct = tr.cnt - 1;  // 不同非空回文子串数为 5。
// int longest_suffix = tr.b[tr.last].len;  // 当前最长回文后缀长度为 5。
// int suffix_count = tr.b[tr.last].num;  // 当前回文后缀有 3 个。
// int state = tr.insert('c');  // 追加字符，返回新的最长回文后缀状态。
// 状态 0/1 是两个虚根；num 不是该回文在全文中的出现次数。
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
