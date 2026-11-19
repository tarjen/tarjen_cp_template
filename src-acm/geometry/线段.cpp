// 用法：
// 依赖：开头.cpp、点与向量.cpp、极角排序.cpp、直线.cpp。
// Segment a{{0,0}, {2,0}}, b{{1,-1}, {1,1}};  // 两个端点。
// int relation = a.is_inter(b);  // 1：严格相交。
// int on = a.is_on(Point{0,0});  // -1：在线段端点；0 不在，1 严格在内部。
// auto distance = a.dis(Point{1,2});  // 点到线段距离为 2。
// 原理：叉积判断共线/跨立，点积判断点是否夹在两个端点之间。
// 两线段严格相交须互相跨立；端点接触或共线重叠先单独判断。
// 点到线段距离先看投影是否越过端点；基本操作 O(1)，距离接口要求 a!=b。
struct segment {
    point a, b;

    bool operator<(const segment& s) const {
        return make_pair(a, b) < make_pair(s.a, s.b);
    }

    // 判定性函数建议在整数域使用

    // 判断点是否在线段上
    // -1 点在线段端点 | 0 点不在线段上 | 1 点严格在线段上
    int is_on(const point& p) const {
        if (p == a || p == b) return -1;
        return (p - a).toleft(p - b) == 0 && (p - a) * (p - b) < -eps;
    }

    // 判断线段直线是否相交
    // -1 直线经过线段端点 | 0 线段和直线不相交 | 1 线段和直线严格相交
    int is_inter(const line& l) const {
        if (l.toleft(a) == 0 || l.toleft(b) == 0) return -1;
        return l.toleft(a) != l.toleft(b);
    }

    // 判断两线段是否相交
    // -1 在某一线段端点处相交 | 0 两线段不相交 | 1 两线段严格相交
    int is_inter(const segment& s) const {
        if (is_on(s.a) || is_on(s.b) || s.is_on(a) || s.is_on(b)) return -1;
        const line l{a, b - a}, ls{s.a, s.b - s.a};
        return l.toleft(s.a) * l.toleft(s.b) == -1 &&
               ls.toleft(a) * ls.toleft(b) == -1;
    }

    // 点到线段距离
    long double dis(const point& p) const {
        // 投影在线段外取较近端点，否则取点到支撑直线的垂距。
        if ((p - a) * (b - a) < -eps || (p - b) * (a - b) < -eps)
            return min(p.dis(a), p.dis(b));
        const line l{a, b - a};
        return l.dis(p);
    }

    // 两线段间距离
    long double dis(const segment& s) const {
        if (is_inter(s)) return 0;
        return min({dis(s.a), dis(s.b), s.dis(a), s.dis(b)});
    }
};

using Segment = segment;
