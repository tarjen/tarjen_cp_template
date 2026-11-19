// 构造耗时：当前 DC3、当前倍增（含 ST）、仅移除 ST 构建的倍增。
// 生成输入、逐项核对 sa/rk/ht 和析构均不计时；先预热，再轮换顺序。
#include <bits/stdc++.h>
using namespace std;
namespace dc3_impl {
#include "../src/string/dc3.cpp"
}
namespace doubling_impl {
#include "../src/string/倍增sa.cpp"
}
namespace doubling_core {
#include "suffix_without_st.h"
}
using Clock = chrono::steady_clock;
vector<int> expected_sa, expected_rk, expected_ht;

template<class T, int Base = 0>
double measure(const string& s, bool save = false) {
    auto start = Clock::now();
    T tr(s);
    auto end = Clock::now();
    int n = s.size();
    if (save) {
        expected_sa.resize(n);
        expected_rk.resize(n);
        expected_ht.resize(n);
        for (int i = 0; i < n; i++) {
            expected_sa[i] = tr.sa[i + Base] - Base;
            expected_rk[i] = tr.rk[i + Base] - Base;
            expected_ht[i] = tr.ht[i + Base];
        }
    } else {
        for (int i = 0; i < n; i++) {
            if (expected_sa[i] != tr.sa[i + Base] - Base ||
                expected_rk[i] != tr.rk[i + Base] - Base ||
                expected_ht[i] != tr.ht[i + Base])
                throw runtime_error("sa/rk/ht mismatch");
        }
    }
    return chrono::duration<double, milli>(end - start).count();
}

int main(int argc, char** argv) {
    int rounds = argc > 1 ? stoi(argv[1]) : 5;
    if (rounds < 1) return 1;
    cout << "n,kind,dc3_ms,sa_with_st_ms,sa_without_st_ms,rounds\n";
    cout << fixed << setprecision(3);
    for (int n : {1200000, 2000000, 5000000}) {
        for (string kind : {"random26", "random2", "identical", "periodic13"}) {
            string s(n, 'a');
            mt19937 rng(20261119);
            string period = "abacababacaba";
            for (int i = 0; i < n; i++) {
                if (kind == "random26") s[i] += rng() % 26;
                if (kind == "random2") s[i] += rng() % 2;
                if (kind == "periodic13") s[i] = period[i % period.size()];
            }
            vector<double> times[3];
            for (int round = -1; round < rounds; round++) {
                for (int j = 0; j < 3; j++) {
                    int algo = (j + round + 1) % 3;
                    double elapsed;
                    if (algo == 0) elapsed = measure<dc3_impl::Suffix, 1>(s, round == -1);
                    if (algo == 1) elapsed = measure<doubling_impl::Suffix>(s);
                    if (algo == 2) elapsed = measure<doubling_core::Suffix>(s);
                    if (round >= 0) times[algo].push_back(elapsed);
                }
            }
            cout << n << ',' << kind;
            for (auto& samples : times) {
                sort(samples.begin(), samples.end());
                cout << ',' << samples[samples.size() / 2];
            }
            cout << ',' << rounds << endl;
        }
    }
}
