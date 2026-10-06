// 用法：
// Trie tr;
// tr.insert(5);
// tr.insert(5);  // 非负 31 位整数；重复插入会累计次数。
// int u = 0;
// for (int b = 30; b >= 0; b--) u = tr.tree[u][(5 >> b) & 1];
// int count = tr.e[u];  // 5 出现 2 次；本板仅提供 insert，没有最大异或查询。
#include <bits/stdc++.h>
using namespace std;
struct Trie {
    vector<array<int, 2>> tree;
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
