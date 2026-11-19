#include <bits/stdc++.h>
using namespace std;
#ifdef ACM_VARIANT
#include "../src-acm/geometry/两点求直线.cpp"
#else
#include "../src/geometry/两点求直线.cpp"
#endif

void check(pair<ll, ll> p, pair<ll, ll> q) {
    auto key = line_abc(p, q);
    auto [a, b, c] = key;
    assert(a > 0 || (a == 0 && b > 0));
    assert(gcd(abs(a), abs(b)) == 1);
    for (auto [x, y] : {p, q})
        assert((__int128)a * x + (__int128)b * y + c == 0);
    assert(key == line_abc(q, p));
}

int main() {
    assert((line_abc({1, 2}, {3, 4}) == array<ll, 3>{1, -1, 1}));
    assert((line_abc({2, -7}, {2, 9}) == array<ll, 3>{1, 0, -2}));
    assert((line_abc({-4, 3}, {8, 3}) == array<ll, 3>{0, 1, -3}));
    assert((line_abc({0, 0}, {-12, -18}) == array<ll, 3>{3, -2, 0}));
    mt19937 rng(20261119);
    for (int trial = 0; trial < 10000; trial++) {
        auto coord = [&]() { return ll(rng() % 2001) - 1000; };
        pair<ll, ll> p{coord(), coord()}, q{coord(), coord()};
        if (p == q) { trial--; continue; }
        check(p, q);
        ll u = ll(rng() % 21) - 10, v = u + 1 + rng() % 10;
        pair<ll, ll> r{p.first + u * (q.first - p.first), p.second + u * (q.second - p.second)};
        pair<ll, ll> s{p.first + v * (q.first - p.first), p.second + v * (q.second - p.second)};
        assert(line_abc(p, q) == line_abc(r, s));
        auto [a, b, c] = line_abc(p, q);
        pair<ll, ll> pp{p.first + a, p.second + b}, qq{q.first + a, q.second + b};
        assert(line_abc(p, q) != line_abc(pp, qq));
    }
    check({-1000000000, -1000000000}, {1000000000, 999999999});
    check({-1000000000, 1000000000}, {999999999, -1000000000});
    check({1000000000, 1000000000}, {1000000000, -1000000000});
    check({1000000000, 1000000000}, {-1000000000, 1000000000});
    map<array<ll, 3>, int> lines;
    lines[line_abc({1, 2}, {3, 4})]++;
    lines[line_abc({5, 6}, {-1, 0})]++;
    assert(lines.size() == 1 && lines.begin()->second == 2);
    cout << "PASS: normalized integer lines, 10000 random cases and boundaries\n";
}
