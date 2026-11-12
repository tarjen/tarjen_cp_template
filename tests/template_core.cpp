// 检查两版默认启用的接口，以及 Hash / 线性基重复初始化。
#include <bits/stdc++.h>
#include "template_variant_types.h"
using namespace std;
using ll = long long;

namespace seg {
#ifdef ACM_VARIANT
#include "../src-acm/data_structure/SegmentTree.cpp"
#else
#include "../src/data_structure/SegmentTree.cpp"
#endif
}
namespace hashing {
#ifdef ACM_VARIANT
#include "../src-acm/string/hash.cpp"
#else
#include "../src/string/hash.cpp"
#endif
}
namespace basis {
#ifdef ACM_VARIANT
#include "../src-acm/others/线性基.cpp"
#else
#include "../src/others/线性基.cpp"
#endif
}

int main() {
    CP_TEST_TYPE(seg::SegmentTree) t(vector<ll>{1, 2, 3});
    t.update(0, 1, 4);
    assert(t.query(0, 2) == 14);
    CP_TEST_TYPE(seg::SegmentTree) single(0);
    single.update(0, 0, 7);
    assert(single.query(0, 0) == 7);

    hashing::Hash h;
    for (string s : {"ababa", "z", "", "abba", "abc"}) {
        h.Hash_init(s);
        hashing::Hash fresh;
        fresh.Hash_init(s);
        for (int l = 1; l <= (int)s.size(); ++l) {
            for (int r = l; r <= (int)s.size(); ++r) {
                assert(h.get1(l, r) == fresh.get1(l, r));
                assert(h.get2(l, r) == fresh.get2(l, r));
                string part = s.substr(l - 1, r - l + 1);
                string reversed = part;
                reverse(reversed.begin(), reversed.end());
                assert((h.get1(l, r) == h.get2(l, r)) == (part == reversed));
            }
        }
    }

    basis::LinearBasis b;
    b.insert(1);
    b.insert(2);
    assert(b.queryMax() == 3 && b.query(3) && !b.query(4));
    b.insert(0);
    b.clear();
    assert(!b.flag && b.tot == 0 && b.queryMax() == 0);
    b.insert(4);
    assert(b.query(4) && !b.query(1));
    cout << "PASS: default segment tree / hash reuse / linear basis reset\n";
}
