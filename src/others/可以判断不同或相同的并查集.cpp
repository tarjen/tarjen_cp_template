// 用法：
// RelationDSU tr(3);  // 节点 1base，相同/不同关系。
// bool ok = tr.merge(1, 2);  // 约束 1 与 2 相同。
// tr.merge(2, -3);  // 第二参数取负表示 2 与 3 不同。
// bool conflict = tr.merge(1, 3);  // false，表示与已有约束冲突。
// 返回 true 表示约束可满足；节点 0 不可用，符号用于编码关系。
#include <bits/stdc++.h>
using namespace std;
struct RelationDSU {
    vector<int> f;
    explicit RelationDSU(int n) : f(n + 1) { iota(f.begin(), f.end(), 0); }
    int getf(int x) {
        if (x < 0) return -getf(-x);
        if (x == f[x])
            return x;
        else
            return f[x] = getf(f[x]);
    }
    bool merge(int x, int y) {  // 如果是x!=y将y取反(x>0 y>0)
        x = getf(x), y = getf(y);
        if (x == -y) return false;
        if (x == y) return true;
        if (x < 0)
            f[-x] = -y;
        else
            f[x] = y;
        return true;
    }
};
