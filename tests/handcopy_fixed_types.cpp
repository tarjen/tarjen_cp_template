// 固定数值类型后的堆和几何接口检查，直接使用手抄源码。
#include <bits/stdc++.h>
using namespace std;
namespace heap_impl {
#include "../src-acm/data_structure/左偏树.cpp"
}
namespace geometry_impl {
#include "../src-acm/geometry/开头.cpp"
#include "../src-acm/geometry/点与向量.cpp"
#include "../src-acm/geometry/极角排序.cpp"
#include "../src-acm/geometry/直线.cpp"
#include "../src-acm/geometry/线段.cpp"
#include "../src-acm/geometry/多边形.cpp"
#include "../src-acm/geometry/凸多边形.cpp"
}

int main() {
    heap_impl::LeftistHeap heap;
    priority_queue<long long, vector<long long>, greater<long long>> reference;
    int root = 0;
    mt19937_64 random(20261113);
    for (int i = 0; i < 5000; ++i) {
        long long value = (long long)(random() % (1ULL << 45)) - (1LL << 44);
        root = heap.push(root, value);
        reference.push(value);
    }
    int other = heap.push(0, -(1LL << 50));
    root = heap.merge(root, other);
    reference.push(-(1LL << 50));
    while (!reference.empty()) {
        assert(heap.top(root) == reference.top());
        assert(heap.size(root) == (int)reference.size());
        root = heap.pop(root);
        reference.pop();
    }
    assert(heap.empty(root));

    using namespace geometry_impl;
    static_assert(is_same_v<decltype(Point{}.x), pt>);
    Point a{0, 0}, b{3, 4};
    assert(fabsl(a.dis(b) - 5) < eps);
    Line horizontal{{0, 0}, {1, 0}};
    assert(fabsl(horizontal.dis(Point{0, 2}) - 2) < eps);
    Segment segment{{0, 0}, {3, 0}};
    assert(segment.is_on(Point{1, 0}) == 1);
    assert(fabsl(segment.dis(Point{1, 2}) - 2) < eps);
    Polygon polygon;
    polygon.p = {{0, 0}, {2, 0}, {2, 2}, {0, 2}};
    static_assert(is_same_v<decltype(polygon.p), vector<point>>);
    assert(fabsl(polygon.area() - 8) < eps);
    auto inside = polygon.winding(Point{1, 1});
    assert(!inside.first && inside.second != 0);
    Convex convex;
    convex.p = polygon.p;
    assert(convex.is_in(Point{1, 1}) == 1);
    assert(fabsl(convex.diameter2() - 8) < eps);
    auto sum = convex + convex;
    assert(fabsl(sum.area() - 32) < eps);
    cout << "PASS: fixed long-long heap / pt geometry / vector storage\n";
}
