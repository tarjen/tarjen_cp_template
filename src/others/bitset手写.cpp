// 用法：
// Bitset tr(10);  // 位编号 [0,9]，初始全 0。
// tr.setBit(3);
// tr.setBit(7);
// int count = tr.count();  // 2；tr.getBit(3)=true。
// Bitset shifted = tr << 1;  // 第 4、8 位为 1，越界位舍弃。
// 按位运算的两个对象长度应相同；减法按模 2^n 进行。
#include <bits/stdc++.h>
using namespace std;

struct Bitset {
    using ull = unsigned long long;
    int n;
    vector<ull> v;
    explicit Bitset(int n) : n(n), v((n + 63) / 64) {}
    void init() { fill(v.begin(), v.end(), 0); }
    void trim() {
        if (n % 64 && !v.empty()) v.back() &= (1ULL << (n % 64)) - 1;
    }
    bool getBit(int pos) const {
        assert(0 <= pos && pos < n);
        return v[pos / 64] >> (pos % 64) & 1;
    }
    void setBit(int pos, bool value = true) {
        assert(0 <= pos && pos < n);
        ull mask = 1ULL << (pos % 64);
        if (value)
            v[pos / 64] |= mask;
        else
            v[pos / 64] &= ~mask;
    }
    // 保留模板库旧入口。
    void add(int pos) { setBit(pos); }
    void shift1() { *this = *this << 1; }
    int count() const {
        int res = 0;
        for (ull w : v) res += __builtin_popcountll(w);
        return res;
    }
    Bitset operator<<(int t) const {
        assert(t >= 0);
        Bitset r(n);
        if (t >= n) return r;
        int high = t / 64, low = t % 64;
        for (int i = 0; i + high < (int)v.size(); i++) {
            r.v[i + high] |= v[i] << low;
            if (low && i + high + 1 < (int)v.size())
                r.v[i + high + 1] |= v[i] >> (64 - low);
        }
        r.trim();
        return r;
    }
    Bitset operator>>(int t) const {
        assert(t >= 0);
        Bitset r(n);
        if (t >= n) return r;
        int high = t / 64, low = t % 64;
        for (int i = high; i < (int)v.size(); i++) {
            r.v[i - high] |= v[i] >> low;
            if (low && i > high) r.v[i - high - 1] |= v[i] << (64 - low);
        }
        return r;
    }
    Bitset operator|(const Bitset& x) const {
        assert(n == x.n);
        Bitset r(n);
        for (int i = 0; i < (int)v.size(); i++) r.v[i] = v[i] | x.v[i];
        return r;
    }
    Bitset operator&(const Bitset& x) const {
        assert(n == x.n);
        Bitset r(n);
        for (int i = 0; i < (int)v.size(); i++) r.v[i] = v[i] & x.v[i];
        return r;
    }
    Bitset operator^(const Bitset& x) const {
        assert(n == x.n);
        Bitset r(n);
        for (int i = 0; i < (int)v.size(); i++) r.v[i] = v[i] ^ x.v[i];
        return r;
    }
    // 无符号n位减法，结果模2^n；借位计算避开x.v[i]+borrow溢出。
    Bitset operator-(const Bitset& x) const {
        assert(n == x.n);
        Bitset r(n);
        ull borrow = 0;
        for (int i = 0; i < (int)v.size(); i++) {
            ull a = v[i], b = x.v[i], next = (a < b) || (borrow && a == b);
            r.v[i] = a - b - borrow;
            borrow = next;
        }
        r.trim();
        return r;
    }
};
