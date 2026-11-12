// 手抄版：沿用原算法与类封装；//? 标记为按需抄写。
// 用法：
// Trie tr;
#include <bits/stdc++.h>
using namespace std;
struct Trie {
    vector<array<int, 2>> tree;
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
    void insert(int t) {
        int x = 0;
        for (int i = 30; i >= 0; i--) {
            int c = (t >> i) & 1;
            if (!tree[x][c]) {
                int id = newnode();
                tree[x][c] = id;
            }
            x = tree[x][c];
        }
        e[x]++;
    }
};
