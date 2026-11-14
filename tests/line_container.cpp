// 对拍任意顺序插入与查询；覆盖同斜率、重复直线、负数交点和清空重用。
#include "../src/data_structure/LineContainer.cpp"

int main() {
    LineContainer hull;
    vector<pair<ll, ll>> lines;
    auto add = [&](ll k, ll b) {
        hull.add(k, b);
        lines.push_back({k, b});
    };
    auto check = [&](ll x) {
        ll expected = LLONG_MAX;
        for (auto [k, b] : lines) expected = min(expected, k * x + b);
        assert(hull.query(x) == expected);
    };
    assert(hull.empty());
    for (auto [k, b] : vector<pair<ll, ll>>{{2,3}, {-1,4}, {2,3}, {2,-5},
                                          {2,9}, {0,0}, {3,2}, {-3,-2}}) {
        add(k, b);
        for (ll x = -30; x <= 30; x++) check(x);
    }
    mt19937_64 rng(20261114);
    for (int t = 0; t < 300; t++) {
        hull.clear();
        lines.clear();
        assert(hull.empty());
        for (int i = 0; i < 150; i++) {
            ll k = (ll)(rng() % 2001) - 1000;
            ll b = (ll)(rng() % 20001) - 10000;
            // 小斜率范围频繁制造重复斜率；同时验证较大系数。
            if (t % 3 == 0) k %= 5;
            if (t % 3 == 1) k *= 1000000, b *= 100000;
            add(k, b);
            assert(!hull.empty());
            for (int j = 0; j < 5; j++) check((ll)(rng() % 2000000001) - 1000000000);
            check(-1); check(0); check(1);
        }
    }
    cout << "PASS: LineContainer, 300 random sequences and boundary checks\n";
}
