// 用法：
// 依赖：开头.cpp、点与向量.cpp、极角排序.cpp。
// Line a{{0,0}, {1,0}}, b{{1,-1}, {0,1}};  // 位置点、方向向量。
// Point p = a.inter(b);  // 非平行直线交点为 (1,0)。
// auto distance = a.dis(Point{0,2});  // 到无限直线的距离为 2。
// 第二个字段不是终点；方向须非零，inter 要求不平行。
template <typename T>
struct line {
    point<T> p, v;  // p 为直线上一点，v 为方向向量

    bool operator==(const line& a) const {
        return v.toleft(a.v) == 0 && v.toleft(p - a.p) == 0;
    }
    int toleft(const point<T>& a) const {
        return v.toleft(a - p);
    }  // to-left 测试
    bool operator<(const line& a) const  // 半平面交算法定义的排序
    {
        if (abs(v ^ a.v) <= eps && v * a.v >= -eps) return toleft(a.p) == -1;
        return argcmp()(v, a.v);
    }

    // 涉及浮点数
    point<T> inter(const line& a) const {
        return p + v * ((a.v ^ (p - a.p)) / (v ^ a.v));
    }  // 直线交点
    long double dis(const point<T>& a) const {
        return abs(v ^ (a - p)) / v.len();
    }  // 点到直线距离
    point<T> proj(const point<T>& a) const {
        return p + v * ((v * (a - p)) / (v * v));
    }  // 点在直线上的投影
};

using Line = line<point_t>;