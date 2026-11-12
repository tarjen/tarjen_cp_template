// 用法：
// 维护值域 [0,n) 中每个位置的占据状态，支持找前/后最近空位；要求 n<=2*64^3。
// 固定三层满块摘要，占 ~192KB 内存。
// HB t(n);
// t.has(x); t.set(x); t.del(x);
// t.prev(x);  // <=x 的最大空位，无则 -1
// t.next(x);  // >=x 的最小空位，无则 -1
#include <bits/stdc++.h>
using namespace std;

struct HB {
    using ull = unsigned long long;
    int n;
    ull f[3][8192];  // f[0]=占据位；f[k][i]=第 k-1 层第 i 个 64 位块是否全满
    HB(int n) : n(n) {
        assert(0 <= n && n <= 2 * 64 * 64 * 64);
        memset(f, ~0, sizeof f);  // 幻影位恒满，搜索不会越出值域
        int c = (n + 63) / 64, d = (c + 63) / 64, e = (d + 63) / 64;
        memset(f[0], 0, c * 8), memset(f[1], 0, d * 8), memset(f[2], 0, e * 8);
        if (n & 63) f[0][c - 1] = ~0ULL << (n & 63);
        if (c & 63) f[1][d - 1] = ~0ULL << (c & 63);
        if (d & 63) f[2][e - 1] = ~0ULL << (d & 63);
    }
    bool has(int x) const { return f[0][x >> 6] >> (x & 63) & 1; }
    void set(int x) {
        int i = x >> 6;
        f[0][i] |= 1ULL << (x & 63);
        if (f[0][i] != ~0ULL) return;
        int j = i >> 6;
        f[1][j] |= 1ULL << (i & 63);
        if (f[1][j] == ~0ULL) f[2][j >> 6] |= 1ULL << (j & 63);
    }
    void del(int x) {
        int i = x >> 6;
        if (f[0][i] == ~0ULL) {
            int j = i >> 6;
            if (f[1][j] == ~0ULL) f[2][j >> 6] &= ~(1ULL << (j & 63));
            f[1][j] &= ~(1ULL << (i & 63));
        }
        f[0][i] &= ~(1ULL << (x & 63));
    }
    int prev(int x) const {
        if ((x = min(x, n - 1)) < 0) return -1;
        int i = x >> 6;
        ull v = ~f[0][i] & (~0ULL >> (63 - (x & 63)));
        if (v) return (i << 6) + 63 - __builtin_clzll(v);
        int j = i >> 6;
        v = ~f[1][j] & ((1ULL << (i & 63)) - 1);
        if (v) {
            i = (j << 6) + 63 - __builtin_clzll(v);
            return (i << 6) + 63 - __builtin_clzll(~f[0][i]);
        }
        int k = j >> 6;
        v = ~f[2][k] & ((1ULL << (j & 63)) - 1);
        if (!v && k) v = ~f[2][--k];
        if (!v) return -1;
        j = (k << 6) + 63 - __builtin_clzll(v);
        i = (j << 6) + 63 - __builtin_clzll(~f[1][j]);
        return (i << 6) + 63 - __builtin_clzll(~f[0][i]);
    }
    int next(int x) const {
        if ((x = max(x, 0)) >= n) return -1;
        int i = x >> 6;
        ull v = ~f[0][i] & (~0ULL << (x & 63));
        if (v) return (i << 6) + __builtin_ctzll(v);
        int j = i >> 6;
        v = ~f[1][j] & (~0ULL << (i & 63) << 1);
        if (v) {
            i = (j << 6) + __builtin_ctzll(v);
            return (i << 6) + __builtin_ctzll(~f[0][i]);
        }
        int k = j >> 6;
        v = ~f[2][k] & (~0ULL << (j & 63) << 1);
        if (!v) v = ~f[2][++k];  // 幻影位恒满，v 仍为 0
        if (!v) return -1;
        j = (k << 6) + __builtin_ctzll(v);
        i = (j << 6) + __builtin_ctzll(~f[1][j]);
        return (i << 6) + __builtin_ctzll(~f[0][i]);
    }
};
