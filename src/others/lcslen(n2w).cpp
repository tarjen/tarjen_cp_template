#include <bits/stdc++.h>
using namespace std;
const int N = 3010;
typedef unsigned long long ull;
const int lim = N / 64 + 3;
struct Bitset {
    ull v[N / 64 + 5];
    void init() {
        memset(v, 0, sizeof(v));
        return;
    }
    void add(int x) {
        v[x >> 6] |= (1ull << (x & 63));
        return;
    }
    void shift1() {
        int lst = 0;
        for (int i = 0; i <= lim; i++) {
            int cur = v[i] >> 63;
            v[i] <<= 1;
            v[i] |= lst;
            lst = cur;
        }
        return;
    }
    int count() {
        int res = 0;
        for (int i = 0; i <= lim; i++) res += __builtin_popcountll(v[i]);
        return res;
    }
    Bitset operator|(const Bitset &x) const {
        Bitset res;
        for (int i = 0; i <= lim; i++) res.v[i] = v[i] | x.v[i];
        return res;
    }
    Bitset operator&(const Bitset &x) const {
        Bitset res;
        for (int i = 0; i <= lim; i++) res.v[i] = v[i] & x.v[i];
        return res;
    }
    Bitset operator^(const Bitset &x) const {
        Bitset res;
        for (int i = 0; i <= lim; i++) res.v[i] = v[i] ^ x.v[i];
        return res;
    }
    Bitset operator-(const Bitset &x) const {
        Bitset res;
        ull lst = 0;
        for (int i = 0; i <= lim; i++) {
            ull cur = (v[i] < x.v[i] + lst);
            res.v[i] = v[i] - x.v[i] - lst;
            lst = cur;
        }
        return res;
    }
} ch[26], f, g;
auto getans = [&](int mid) {
    int l1 = mid, l2 = n - mid;
    f.init();
    g.init();
    for (int i = 0; i < 26; i++) {
        ch[i].init();
    }
    for (int i = mid + 1; i <= n; i++) ch[s[i] - 'a'].add(i);
    for (int i = 1; i <= mid; i++) {
        g = f | ch[s[i] - 'a'];
        f.shift1();
        f.add(1);
        f = g - f;
        f = f ^ g;
        f = f & g;
    }
    return f.count();
};