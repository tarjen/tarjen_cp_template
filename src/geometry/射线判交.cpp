bool ray_inter_judge(
    Segment a,
    Segment b) {  // 射线判交,这里用segment但实际是射线 p_a->p_b
    point_t s1, s2;
    s1 = (a.b - a.a) ^ (b.a - a.a);
    s2 = (a.b - a.a) ^ (b.b - a.a);
    auto sgn = [&](point_t x) {
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