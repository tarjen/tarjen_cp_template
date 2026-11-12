// 手抄版：沿用原算法与类封装；//? 标记为按需抄写。
// 用法：
// 先提供 typedef long long ll; 以及标准库头文件。
// LinearBasis tr;
// 本板支持位号 [0,35]；这里用默认构造逐个插入，不依赖外部数组。
struct LinearBasis {
    static const int maxbase = 35;
    bool flag = false;
    ll a[maxbase + 1];
    int tot;
    LinearBasis() {
        memset(a, 0, sizeof a);
        tot = 0;
    }
    LinearBasis(ll* x, int n) : LinearBasis() { build(x, n); }
    void build(ll* x, int n) {
        for (int i = 0; i < n; ++i) insert(x[i]);
    }
    void clear() { memset(a, 0, sizeof a); flag = false; tot = 0; }
    bool insert(ll t) {
        // 暴力插入一个数，维护的是一个上三角型的线性基矩阵，时间复杂度低，当待插入元素能插入时，返回true
        for (int i = maxbase; i >= 0; --i) {
            if (t & (1ll << i)) {
                if (!a[i]) {
                    a[i] = t;  // 这里表示插入成功
                    break;
                }
                t ^= a[i];
            }
        }
        if (t == 0) flag = true, tot++;
        return t;
    }
    bool query(ll t) {
        // 询问t是否可以被当前线性基表示，不插入
        if (t == 0) return true;
        for (int i = maxbase; i >= 0; --i) {
            if (t & (1ll << i)) {
                if (!a[i]) {
                    return false;
                }
                t ^= a[i];
            }
        }
        return true;
    }
// 按需启用：以下整个函数组一起取消注释。
//?     void Insert(ll t) {
//?         // 插入一个线性基，利用高斯消元法维护一个对角矩阵
//?         for (int i = maxbase; i >= 0; --i) {
//?             if (t >> i & 1) {
//?                 if (a[i])
//?                     t ^= a[i];
//?                 else {
//?                     a[i] = t;
//?                     for (int j = i - 1; j >= 0; --j)
//?                         if (a[j] && (a[i] >> j & 1)) a[i] ^= a[j];
//?                     for (int j = i + 1; j <= maxbase; ++j)
//?                         if (a[j] >> i & 1) a[j] ^= a[i];
//?                     break;
//?                 }
//?             }
//?         }
//?     }
// 按需启用：以下整个函数组一起取消注释。
//?     LinearBasis merge(const LinearBasis& l1, const LinearBasis& l2) {
//?         // 得到两个线性基的并
//?         LinearBasis ret = l1;
//?         for (int i = maxbase; i >= 0; --i)
//?             if (l2.a[i]) ret.insert(l2.a[i]);
//?         return ret;
//?     }
// 按需启用：以下整个函数组一起取消注释。
//?     LinearBasis intersection(const LinearBasis& l1, const LinearBasis& l2) {
//?         // 得到两个线性基的交
//?         LinearBasis all, ret, full;
//?         ret.clear();
//?         for (int i = maxbase; i >= 0; --i) {
//?             all.a[i] = l1.a[i];
//?             full.a[i] = 1ll << i;
//?         }
//?         for (int i = maxbase; i >= 0; --i) {
//?             if (l2.a[i]) {
//?                 ll v = l2.a[i], k = 0;
//?                 bool flag = true;
//?                 for (int j = maxbase; j >= 0; --j) {
//?                     if (v & (1ll << j)) {
//?                         if (all.a[j]) {
//?                             v ^= all.a[j];
//?                             k ^= full.a[j];
//?                         } else {
//?                             // l2's basis is not in l1's;
//?                             flag = false;
//?                             all.a[j] = v;
//?                             full.a[j] = k;
//?                             break;
//?                         }
//?                     }
//?                 }
//?                 if (flag) {
//?                     ll v = 0;  // get intersection by k;
//?                     for (int j = maxbase; j >= 0; --j) {
//?                         if (k & (1ll << j)) {
//?                             v ^= l1.a[j];
//?                         }
//?                     }
//?                     ret.insert(v);
//?                 }
//?             }
//?         }
//?         return ret;
//?     }
    // 询问最值
    ll queryMax() {
        ll ret = 0;
        for (int i = maxbase; i >= 0; --i)
            if ((ret ^ a[i]) > ret) ret ^= a[i];
        return ret;
    }
// 按需启用：以下整个函数组一起取消注释。
//?     ll queryMin() {
//?         for (int i = 0; i <= maxbase; ++i)
//?             if (a[i]) return a[i];
//?         return 0;
//?     }
    // 旧接口存在越界且未规约，请勿使用；不在当前测试支持范围内。
// 按需启用：以下整个函数组一起取消注释。
// 已知旧实现不正确（越界且未规约），请勿启用。
//?     ll Kth_Max(ll k) {
//?         ll res = 0;
//?         for (int i = 62; i >= 0; i--)
//?             if (k & (1LL << i)) res ^= a[i];
//?         return res;
//?     }
};
