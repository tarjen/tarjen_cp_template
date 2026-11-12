// 手抄版：沿用原算法与类封装；//? 标记为按需抄写。
// 用法：
// Trie tr;  // 小写字母，节点池自动增长。
// string 输入不用补首格；旧 char* 接口从 t[1] 开始。
#include <bits/stdc++.h>
using namespace std;
struct Trie {
    vector<array<int, 26>> tree;
    vector<int> e;
    int tot = 0;
    Trie(int reserve_nodes = 0) : tree(1), e(1) {
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
            //? assert(0 <= c && c < 26);
            if (!tree[x][c]) {
                int id = newnode();
                tree[x][c] = id;
            }
            x = tree[x][c];
        }
        e[x]++;
    }
    // 保留旧char*接口：输入从t[1]开始。
    //? void insert(const char* t) { insert(string(t + 1)); }
};
