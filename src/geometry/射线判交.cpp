// 用法：
// 依赖：几何开头、点、极角排序、直线、线段。
// Segment a{{0,0},{1,0}}, b{{2,-1},{2,0}};
// bool intersect = ray_inter_judge(a, b);  // true，两射线在 (2,0) 相交。
// 虽然参数类型叫 Segment，这里表示从 a 指向 b 的无限射线。
// 原理：两支撑直线交点须同时满足两个射线参数 t>=0；用叉积符号免除法。
// 共线时改用点积，判断某条射线起点是否落在另一条射线的正向上。
// 单次 O(1)，两个方向须非零；此处 sgn 直接比较 0，浮点临界处需留意精度。
bool ray_inter_judge(
    Segment a,
    Segment b) {  // 射线判交,这里用segment但实际是射线 p_a->p_b
    pt s1, s2;
    s1 = (a.b - a.a) ^ (b.a - a.a);
    s2 = (a.b - a.a) ^ (b.b - a.a);
    auto sgn = [&](pt x) {
        if (x > 0) return 1;
        if (x == 0) return 0;
        return -1;
    };
    if (sgn(s1) == 0 && sgn(s2) == 0) {
        return sgn((a.b - a.a) * (b.a - a.a)) >= 0 ||
               sgn((b.b - b.a) * (a.a - b.a)) >= 0;
    }
    if (!sgn(s1 - s2) || sgn(s1) == sgn(s2 - s1)) return 0;
    swap(a, b);
    s1 = (a.b - a.a) ^ (b.a - a.a);
    s2 = (a.b - a.a) ^ (b.b - a.a);
    return sgn(s1) != sgn(s2 - s1);
}
