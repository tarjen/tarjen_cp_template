// 用法：
// 依赖：开头.cpp（pt/eps）。
// Point a{0,0}, b{3,4};
// auto distance = a.dis(b);  // 距离为 5；b.len2()=25。
// Point u{1,0}, v{0,1};
// auto dot = u*v;
// auto cross = u^v;  // 点积 0，叉积 1，叉积注意括号。
// point<T> 可指定类型；Point 是 point<pt> 的别名。
// 原理：点相减得到向量；u*v=|u||v|cosθ，u^v=|u||v|sinθ。
// 叉积正/负表示 v 在 u 的左/右侧，绝对值是平行四边形面积。
// 平方距离用点积，旋转用二维旋转矩阵；基本操作均为 O(1)。
template <typename T>
struct point {
    T x, y;

    bool operator==(const point& a) const {
        return (abs(x - a.x) <= eps && abs(y - a.y) <= eps);
    }
    bool operator<(const point& a) const {
        if (abs(x - a.x) <= eps) return y < a.y - eps;
        return x < a.x - eps;
    }
    bool operator>(const point& a) const { return !(*this < a || *this == a); }
    point operator+(const point& a) const { return {x + a.x, y + a.y}; }
    point operator-(const point& a) const { return {x - a.x, y - a.y}; }
    point operator-() const { return {-x, -y}; }
    point operator*(const T k) const { return {k * x, k * y}; }
    point operator/(const T k) const { return {x / k, y / k}; }
    T operator*(const point& a) const { return x * a.x + y * a.y; }  // 点积
    T operator^(const point& a) const {
        return x * a.y - y * a.x;
    }  // 叉积，注意优先级
    int toleft(const point& a) const {
        const auto t = (*this) ^ a;
        return (t > eps) - (t < -eps);
    }  // to-left 测试
    T len2() const { return (*this) * (*this); }  // 向量长度的平方
    T dis2(const point& a) const {
        return (a - (*this)).len2();
    }  // 两点距离的平方

    // 涉及浮点数
    long double len() const { return sqrtl(len2()); }  // 向量长度
    long double dis(const point& a) const {
        return sqrtl(dis2(a));
    }  // 两点距离
    long double ang(const point& a) const {
        // 余弦公式求夹角，截到 [-1,1] 避免舍入越界；两个向量均须非零。
        return acosl(max(-1.0l, min(1.0l, ((*this) * a) / (len() * a.len()))));
    }  // 向量夹角
    point rot(const long double rad) const {
        return {x * cos(rad) - y * sin(rad), x * sin(rad) + y * cos(rad)};
    }  // 逆时针旋转（给定角度）
    point rot(const long double cosr, const long double sinr) const {
        return {x * cosr - y * sinr, x * sinr + y * cosr};
    }  // 逆时针旋转（给定角度的正弦与余弦）
};

using Point = point<pt>;
