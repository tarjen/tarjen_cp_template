// 复合结果逐点和 g(f(x)) 比较，核对常量、相接、反向复合与极值。
#include <bits/stdc++.h>
using namespace std;
#ifdef ACM_VARIANT
#include "../src-acm/others/relu.cpp"
#else
#include "../src/others/relu.cpp"
#endif

int evaluate(node a, int x) {
    if (x <= a.l) return a.lv;
    if (x >= a.r) return a.rv;
    return int(1LL * x - a.l + a.lv);
}

void check(node a, node b) {
    node c = a + b;
    assert(c.l <= c.r);
    assert(1LL * c.r - c.l == 1LL * c.rv - c.lv);
    vector<int> points{INT_MIN, INT_MAX, -100, 0, 100};
    for (int p : {a.l, a.r, c.l, c.r}) {
        points.push_back(p);
        if (p != INT_MIN) points.push_back(p - 1);
        if (p != INT_MAX) points.push_back(p + 1);
    }
    for (int x : points) {
        int expected = evaluate(b, evaluate(a, x));
        assert(c.get(x) == expected);
        assert(evaluate(c, x) == expected);
    }
}

int main() {
    vector<node> small;
    for (int l = -3; l <= 3; l++)
        for (int lv = -3; lv <= 3; lv++)
            for (int len = 0; len <= 5; len++) small.push_back({l, lv, l + len, lv + len});
    for (node a : small)
        for (node b : small) check(a, b);
    mt19937 rng(20261119);
    for (int trial = 0; trial < 10000; trial++) {
        auto random = [&] {
            int l = int(rng() % 20001) - 10000;
            int lv = int(rng() % 20001) - 10000, len = rng() % 1000;
            return node{l, lv, l + len, lv + len};
        };
        node a = random(), b = random(), c = random();
        check(a, b);
        check(a + b, c);
        check(a, b + c);
        node left = (a + b) + c, right = a + (b + c);
        for (int x : {INT_MIN, -10000, a.l, a.r, 0, 10000, INT_MAX})
            assert(left.get(x) == right.get(x));
    }
    vector<node> extreme{{INT_MIN, INT_MIN, INT_MAX, INT_MAX},
                         {INT_MIN, 0, INT_MIN + 1, 1},
                         {INT_MAX - 1, -1, INT_MAX, 0},
                         {0, INT_MIN, 0, INT_MIN}, {0, INT_MAX, 0, INT_MAX}};
    for (node a : extreme)
        for (node b : extreme) check(a, b);
    node f{0, 0, 10, 10}, g{2, 1, 8, 7};
    assert((f + g).get(12) == 7);
    assert((g + f).get(-100) == 1);
    ostringstream out;
    out << (f + g) << ' ' << node{1, 2, 1, 2};
    assert(out.str() == "(2,1,8,7) (1,2,1,2)");
    cout << "PASS: ReLU composition / exhaustive pairs / 10000 random triples / limits / stream output\n";
}
