// 0base；Gauss g(equ,var,prime_mod);
// 填a/rhs；solve返回0无解、1唯一解、2多解，x为一组解；模数须为质数。
#include <bits/stdc++.h>
using namespace std;

struct Gauss {
    enum Status { no_solution = 0, unique = 1, infinite = 2 };
    int equ, var, mod, rank = 0;
    vector<vector<int>> a;
    vector<int> rhs, x;
    Gauss(int equ, int var, int mod = 1000003)
        : equ(equ),
          var(var),
          mod(mod),
          a(equ, vector<int>(var)),
          rhs(equ),
          x(var) {}
    int norm(long long x) const {
        x %= mod;
        return x < 0 ? x + mod : x;
    }
    int inverse(int x) const {
        int res = 1;
        for (int k = mod - 2; k; k >>= 1, x = 1LL * x * x % mod)
            if (k & 1) res = 1LL * res * x % mod;
        return res;
    }
    Status solve() {
        auto m = a;
        auto b = rhs;
        vector<int> pivot;
        rank = 0;
        fill(x.begin(), x.end(), 0);
        for (auto& row : m)
            for (int& value : row) value = norm(value);
        for (int& value : b) value = norm(value);
        for (int col = 0; col < var && rank < equ; col++) {
            int row = rank;
            while (row < equ && !m[row][col]) row++;
            if (row == equ) continue;
            swap(m[row], m[rank]);
            swap(b[row], b[rank]);
            int inv = inverse(m[rank][col]);
            for (int j = col; j < var; j++)
                m[rank][j] = 1LL * m[rank][j] * inv % mod;
            b[rank] = 1LL * b[rank] * inv % mod;
            for (int i = 0; i < equ; i++)
                if (i != rank) {
                    int factor = m[i][col];
                    for (int j = col; j < var; j++)
                        m[i][j] = norm(m[i][j] - 1LL * factor * m[rank][j]);
                    b[i] = norm(b[i] - 1LL * factor * b[rank]);
                }
            pivot.push_back(col);
            rank++;
        }
        for (int i = rank; i < equ; i++)
            if (b[i]) return no_solution;
        for (int i = 0; i < rank; i++) x[pivot[i]] = b[i];
        return rank == var ? unique : infinite;
    }
};
