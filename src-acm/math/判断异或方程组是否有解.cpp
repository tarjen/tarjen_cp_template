// 用户要求：封装原 bitset 高斯消元，判断异或方程组是否有解。
// XorEquations<> eq(3);  // 3 个未知量，编号 0..2；方程数量不限。
// eq.add({0, 1}, 1); eq.add({1, 2}, 0);  // x0^x1=1，x1^x2=0。
// bool ok = eq.solve();  // true；只判断是否有解，不输出一组解。
// 需标准库头文件和 using namespace std；n<N，b[i][n] 为右端值。
// solve() 原地消元，可重复调用或继续加方程；clear() 清空所有方程。
template<int N = 105>
struct XorEquations {
    int n;
    vector<bitset<N>> b;
    XorEquations(int n) : n(n) { assert(0 <= n && n < N); }
    void clear() { b.clear(); }
    void add(const vector<int>& vars, bool rhs) {
        bitset<N> row;
        for (int i : vars) { assert(0 <= i && i < n); row.flip(i); }
        row[n] = rhs;
        b.push_back(row);
    }
    bool solve() {
        int m = b.size(), p = 0;
        for (int i = 0; i < n && p < m; i++) {
            int j = p;
            while (j < m && !b[j][i]) j++;
            if (j == m) continue;
            swap(b[p], b[j]);
            for (j = p + 1; j < m; j++) if (b[j][i]) b[j] ^= b[p];
            p++;
        }
        for (int i = p; i < m; i++) if (b[i][n]) return false;
        return true;
    }
};
