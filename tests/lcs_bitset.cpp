// 直接拼接通用 Bitset 与 LCS 片段，和普通 DP 对拍。
#ifdef ACM_VARIANT
#include "../src-acm/others/bitset手写.cpp"
#else
#include "../src/others/bitset手写.cpp"
#endif

int reference(const string& s, int mid) {
    int n = (int)s.size() - 1;
    vector<int> dp(n + 1);
    for (int i = 1; i <= mid; i++) {
        int old = 0;
        for (int j = mid + 1; j <= n; j++) {
            int current = dp[j];
            dp[j] = s[i] == s[j] ? old + 1 : max(dp[j], dp[j - 1]);
            old = current;
        }
    }
    return dp[n];
}

void check(string s, const vector<int>& splits) {
    int n = (int)s.size() - 1;
#ifdef ACM_VARIANT
#include "../src-acm/others/lcslen(n2w).cpp"
#else
#include "../src/others/lcslen(n2w).cpp"
#endif
    for (int mid : splits) {
        int expected = reference(s, mid);
        assert(getans(mid) == expected);
        assert(getans(mid) == expected);  // 工作位集须清空，支持重复调用。
    }
}

int main() {
    mt19937 rng(20261119);
    for (int trial = 0; trial < 500; trial++) {
        int n = rng() % 41;
        string s = " ";
        while ((int)s.size() <= n) s += char('a' + rng() % 4);
        vector<int> splits(n + 1);
        iota(splits.begin(), splits.end(), 0);
        shuffle(splits.begin(), splits.end(), rng);
        check(s, splits);
    }
    for (int n : {63, 64, 65, 127, 128, 129, 257, 3010}) {
        string same = " " + string(n, 'a'), random = same;
        for (int i = 1; i <= n; i++) random[i] = char('a' + rng() % 26);
        vector<int> splits{0, n, n / 2, min(n, 64), min(n, 128)};
        check(same, splits);
        check(random, splits);
    }
    // 跨机器字借位也使用通用实现，第三字应保留借位。
    Bitset a(192), b(192);
    b.setBit(0);
    for (int i = 64; i < 128; i++) b.setBit(i);
    auto difference = a - b;
    assert(difference.v[2] == ULLONG_MAX);
    cout << "PASS: shared Bitset LCS / 500 random strings / word boundaries / reuse\n";
}
