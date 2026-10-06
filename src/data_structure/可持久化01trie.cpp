// 用法：
// Persistent_Trie tr;          // 默认 31 位，支持 [0, 2^31-1]。
// tr.append(5);               // 加入 a[1]，返回版本号 1。
// tr.append(2);               // 加入 a[2]，返回版本号 2。
// int ans = tr.max_xor(1, 2, 3);  // max(5^3, 2^3) = 6；返回异或值。
// l,r 是插入序列的 1base 闭区间；查询要求 1 <= l <= r <= 插入次数。
// root[k] 是前 k 个数的根节点编号，root[0] 是空版本。
// 等价底层调用：tr.query(tr.root[l-1], tr.root[r], x)，传根编号而非版本号。
// 可用 Persistent_Trie tr(b) 指定 1..31 位；插入值和 x 都须在 [0, 2^b-1]。
#include <bits/stdc++.h>
using namespace std;

struct Persistent_Trie {
    struct Node {
        array<int, 2> ch{};
        int sum = 0;
    };
    int bits;
    vector<Node> a{Node()};
    vector<int> root{0};
    explicit Persistent_Trie(int bits = 31) : bits(bits) {
        assert(1 <= bits && bits <= 31);
    }
    int insert(int old, int num, int bit) {
        Node copy = a[old];
        copy.sum++;
        int now = a.size();
        a.push_back(copy);
        if (bit < 0) return now;
        int c = (num >> bit) & 1;
        a[now].ch[c] = insert(a[old].ch[c], num, bit - 1);
        return now;
    }
    int insert(int old, int num) {
        assert(num >= 0);
        return insert(old, num, bits - 1);
    }
    int append(int num) {
        int p = insert(root.back(), num);
        root.push_back(p);
        return (int)root.size() - 1;
    }
    // s,t是两个根编号；t版本必须包含s版本，且差集非空。
    int query(int s, int t, int x) const {
        assert(a[t].sum > a[s].sum);
        int ans = 0;
        for (int bit = bits - 1; bit >= 0; bit--) {
            int c = (x >> bit) & 1, want = c ^ 1;
            if (a[a[t].ch[want]].sum > a[a[s].ch[want]].sum)
                c = want, ans |= 1 << bit;
            s = a[s].ch[c];
            t = a[t].ch[c];
        }
        return ans;
    }
    int max_xor(int l, int r, int x) const {
        return query(root[l - 1], root[r], x);
    }
};
