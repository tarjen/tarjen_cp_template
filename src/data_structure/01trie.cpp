// Trie tr; 节点池自动增长；可选构造参数仅用于预留节点容量。
#include <bits/stdc++.h>
using namespace std;
struct Trie {
    vector<array<int,2>> tree;
    vector<int> e;
    int tot=0;
    explicit Trie(int reserve_nodes=0): tree(1),e(1) {
        tree.reserve(max(1,reserve_nodes)); e.reserve(max(1,reserve_nodes));
    }
    int newnode() { tree.push_back({}); e.push_back(0); return ++tot; }
    void insert(int t) {
        int x=0;
        for(int i=30;i>=0;i--) {
            int c=(t>>i)&1;
            if(!tree[x][c]) { int id=newnode(); tree[x][c]=id; }
            x=tree[x][c];
        }
        e[x]++;
    }
};
