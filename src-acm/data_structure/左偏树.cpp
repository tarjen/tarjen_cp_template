// 用法：
// LeftistHeap<int> hp(n);  // 创建节点池，n 仅用于预留空间，不代表创建了一个堆。
// int x = 0;               // 新建空堆：用一个根变量保存 0；其他空堆也各用一个根变量。
// x = hp.push(x, 5);       // 插入 5，接住返回的新根。
// int y = hp.newNode(2);   // 新建仅含 2 的堆；也可以 int y = hp.push(0, 2)。
// x = hp.merge(x, y); y = 0;  // 合并两堆；旧根不可再作为独立堆使用。
// int minimum = hp.top(x);  // 2；top/pop 要求堆非空。
// x = hp.pop(x);  // 删除堆顶，返回新根；可用 hp.size(x)、hp.empty(x)。
// 所有根必须属于同一个 hp；默认小根，大根用 LeftistHeap<int, greater<int>>。
// merge/push/pop 最坏 O(log n)，top/size/empty O(1)，空间 O(插入节点数)。
#include <bits/stdc++.h>
using namespace std;

template <class T = long long, class Compare = less<T>>
struct LeftistHeap {
    struct Node {
        T val{};
        int ls = 0, rs = 0, dist = 0, sz = 0;
    };
    vector<Node> a;
    Compare cmp;

    LeftistHeap(int _n = 0, Compare _cmp = Compare()) : a(1), cmp(_cmp) {
        a.reserve(_n + 1);
    }
    int newNode(T val) {
        a.push_back({std::move(val), 0, 0, 1, 1});
        return (int)a.size() - 1;
    }
    int merge(int x, int y) {
        if (!x || !y) return x | y;
        if (cmp(a[y].val, a[x].val)) swap(x, y);
        a[x].rs = merge(a[x].rs, y);
        if (a[a[x].ls].dist < a[a[x].rs].dist)
            swap(a[x].ls, a[x].rs);
        a[x].dist = a[a[x].rs].dist + 1;
        a[x].sz = a[a[x].ls].sz + a[a[x].rs].sz + 1;
        return x;
    }

    int push(int root, T val) { return merge(root, newNode(std::move(val))); }
    int pop(int root) {
        assert(root);
        return merge(a[root].ls, a[root].rs);
    }
    const T& top(int root) const {
        assert(root);
        return a[root].val;
    }
    int size(int root) const { return a[root].sz; }
    bool empty(int root) const { return root == 0; }
};
