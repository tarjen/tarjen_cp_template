// 用法：
// PrimeSieve tr(20);  // 构造即筛出 <=20 的质数。
// int first = tr.p[0];  // 2；p 为 0base 质数列表。
// bool composite = tr.v[4];  // true，合数标记。
// bool prime = tr.is_prime(7);  // true；同时检查 x 是否在筛表范围内。
#include <bits/stdc++.h>
using namespace std;

struct PrimeSieve {
    int n;
    vector<char> v;
    vector<int> p;
    explicit PrimeSieve(int n) : n(n), v(n + 1) {
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
