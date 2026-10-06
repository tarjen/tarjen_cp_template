// 用法：
// Gauss tr(2, 2);  // 两个方程、两个未知量，矩阵下标 0base。
// tr.a = {{1,1}, {1,-1}};
// tr.rhs = {3,1};  // x+y=3，x-y=1。
// auto status = tr.solve();  // 1：唯一解，tr.x={2,1}。
// status 为 0 无解、1 唯一解、2 多解；多解时 x 是自由变量取 0 的一组解。
// 浮点版可指定 eps；输入 a/rhs 在求解后保留。
#include <bits/stdc++.h>
using namespace std;

struct Gauss {
    enum Status { no_solution = 0, unique = 1, infinite = 2 };
    int equ, var, rank = 0;
    double eps;
    vector<vector<double>> a;
    vector<double> rhs, x;
    Gauss(int equ, int var, double eps = 1e-9)
        : equ(equ),
          var(var),
          eps(eps),
          a(equ, vector<double>(var)),
          rhs(equ),
          x(var) {}
    Gauss(const vector<vector<double>>& coefficients,
          const vector<double>& values, double eps = 1e-9)
        : Gauss(values.size(),
                coefficients.empty() ? 0 : coefficients[0].size(), eps) {
        a = coefficients;
        rhs = values;
    }
    // 保留输入，每次solve使用工作副本；自由变量取0。
    Status solve() {
        auto m = a;
        auto b = rhs;
        vector<int> pivot;
        rank = 0;
        fill(x.begin(), x.end(), 0);
        for (int col = 0; col < var && rank < equ; col++) {
            int row = rank;
            for (int i = rank + 1; i < equ; i++)
                if (abs(m[i][col]) > abs(m[row][col])) row = i;
            if (abs(m[row][col]) < eps) continue;
            swap(m[row], m[rank]);
            swap(b[row], b[rank]);
            double divisor = m[rank][col];
            for (int j = col; j < var; j++) m[rank][j] /= divisor;
            b[rank] /= divisor;
            for (int i = 0; i < equ; i++)
                if (i != rank) {
                    double factor = m[i][col];
                    for (int j = col; j < var; j++)
                        m[i][j] -= factor * m[rank][j];
                    b[i] -= factor * b[rank];
                }
            pivot.push_back(col);
            rank++;
        }
        for (int i = rank; i < equ; i++)
            if (abs(b[i]) >= eps) return no_solution;
        for (int i = 0; i < rank; i++) x[pivot[i]] = b[i];
        return rank == var ? unique : infinite;
    }
};
