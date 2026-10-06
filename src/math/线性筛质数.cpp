// PrimeSieve sieve(n); p为0base质数列表，v[x]为合数标记，范围0..n。
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
