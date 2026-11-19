#include <bits/stdc++.h>
using namespace std;
#ifdef ACM_VARIANT
#include "../src-acm/math/判断异或方程组是否有解.cpp"
#else
#include "../src/math/判断异或方程组是否有解.cpp"
#endif

bool brute(int n, const vector<int>& rows) {
    for (int mask = 0; mask < (1 << n); mask++) {
        bool ok = true;
        for (int row : rows)
            if ((__builtin_popcount((row & ((1 << n) - 1)) & mask) & 1) != (row >> n))
                ok = false;
        if (ok) return true;
    }
    return false;
}

int main() {
    int cases = 0;
    for (int n = 0; n <= 3; n++) {
        int choices = 1 << (n + 1);
        XorEquations<> eq(n);
        for (int m = 0, count = 1; m <= 3; m++, count *= choices) {
            for (int code = 0; code < count; code++) {
                eq.clear();
                vector<int> rows;
                int value = code;
                for (int i = 0; i < m; i++) {
                    int row = value % choices;
                    value /= choices;
                    rows.push_back(row);
                    vector<int> vars;
                    for (int j = 0; j < n; j++) if (row >> j & 1) vars.push_back(j);
                    eq.add(vars, row >> n);
                }
                bool expected = brute(n, rows);
                assert(eq.solve() == expected);
                assert(eq.solve() == expected);
                eq.add({}, true);
                assert(!eq.solve());
                cases++;
            }
        }
    }
    mt19937 rng(20261119);
    for (int trial = 0; trial < 1000; trial++) {
        int n = rng() % 11, m = rng() % 25;
        XorEquations<> eq(n);
        vector<int> rows;
        for (int i = 0; i < m; i++) {
            int row = rng() % (1 << (n + 1));
            rows.push_back(row);
            vector<int> vars;
            for (int j = 0; j < n; j++) if (row >> j & 1) vars.push_back(j);
            eq.add(vars, row >> n);
            assert(eq.solve() == brute(n, rows));
        }
        cases++;
    }
    XorEquations<> duplicates(2);
    duplicates.add({0, 0, 1}, 1);
    duplicates.add({1}, 0);
    assert(!duplicates.solve());
    duplicates.clear();
    assert(duplicates.solve());
    XorEquations<> full(104);
    for (int i = 0; i < 104; i++) full.add({i}, i % 2);
    assert(full.solve());
    full.add({103}, false);
    assert(!full.solve());
    XorEquations<1025> wide(1024);
    wide.add({0, 63, 64, 127, 511, 1023}, 1);
    assert(wide.solve());
    wide.add({1023, 511, 127, 64, 63, 0}, 0);
    assert(!wide.solve());
    cout << "PASS: XOR equations, " << cases << " exhaustive/random cases\n";
}
