// 用法：
// Trie tr;  // 小写字母，节点池自动增长。
// tr.insert(string("aba"));
// tr.insert(string("aba"));
// int u = 0;
// for (char c : string("aba")) u = tr.tree[u][c-'a'];
// int count = tr.e[u];  // "aba" 出现 2 次；中途走到 0 表示单词不存在。
// string 输入不用补首格；旧 char* 接口从 t[1] 开始。
#include <bits/stdc++.h>
using namespace std;
struct Trie {
    vector<array<int, 26>> tree;
    vector<int> e;
    int tot = 0;
    explicit Trie(int reserve_nodes = 0) : tree(1), e(1) {
        tree.reserve(max(1, reserve_nodes));
        e.reserve(max(1, reserve_nodes));
    }
    int newnode() {
        tree.push_back({});
        e.push_back(0);
        return ++tot;
    }
    void insert(const string& s) {
        int x = 0;
        for (char ch : s) {
            int c = ch - 'a';
            assert(0 <= c && c < 26);
            if (!tree[x][c]) {
                int id = newnode();
                tree[x][c] = id;
            }
            x = tree[x][c];
        }
        e[x]++;
    }
    // 保留旧char*接口：输入从t[1]开始。
    void insert(const char* t) { insert(string(t + 1)); }
};
