// 手抄版：沿用原算法与类封装；//? 标记为按需抄写。
// 用法：
#include <bits/stdc++.h>
using namespace std;

struct PrimeSieve {
    int n;
    vector<char> v;
    vector<int> p;
    PrimeSieve(int n) : n(n), v(n + 1) {
        v[0] = true;
        if (n >= 1) v[1] = true;
        for (int i = 2; i <= n; i++) {
            if (!v[i]) p.push_back(i);
            for (int prime : p) {
                if (prime > n / i) break;
                v[i * prime] = true;
                if (i % prime == 0) break;
            }
        }
    }
    bool is_prime(int x) const { return x >= 2 && x <= n && !v[x]; }
};
