// 用法：
// 依赖：几何开头、点、极角排序、直线、线段。
// vector<Segment> segments = {{{0,0},{2,2}}, {{0,2},{2,0}}};
// bool intersect = segs_inter(segments);  // true，判断是否存在一对相交线段。
// 参数为所有线段，返回布尔值，不返回交点或相交对数量。
bool segs_inter(const vector<Segment>& segs) {
    if (segs.empty()) return false;
    using seq_t = tuple<point_t, int, Segment>;
    const auto seqcmp = [](const seq_t& u, const seq_t& v) {
        const auto [u0, u1, u2] = u;
        const auto [v0, v1, v2] = v;
        if (abs(u0 - v0) <= eps) return make_pair(u1, u2) < make_pair(v1, v2);
        return u0 < v0 - eps;
    };
    vector<seq_t> seq;
    for (auto seg : segs) {
        if (seg.a.x > seg.b.x + eps) swap(seg.a, seg.b);
        seq.push_back({seg.a.x, 0, seg});
        seq.push_back({seg.b.x, 1, seg});
    }
    sort(seq.begin(), seq.end(), seqcmp);
    point_t x_now;
    auto cmp = [&](const Segment& u, const Segment& v) {
        if (abs(u.a.x - u.b.x) <= eps || abs(v.a.x - v.b.x) <= eps)
            return u.a.y < v.a.y - eps;
        return ((x_now - u.a.x) * (u.b.y - u.a.y) + u.a.y * (u.b.x - u.a.x)) *
                   (v.b.x - v.a.x) <
               ((x_now - v.a.x) * (v.b.y - v.a.y) + v.a.y * (v.b.x - v.a.x)) *
                       (u.b.x - u.a.x) -
                   eps;
    };
    multiset<Segment, decltype(cmp)> s{cmp};
    for (const auto [x, o, seg] : seq) {
        x_now = x;
        const auto it = s.lower_bound(seg);
        if (o == 0) {
            if (it != s.end() && seg.is_inter(*it)) return true;
            if (it != s.begin() && seg.is_inter(*prev(it))) return true;
            s.insert(seg);
        } else {
            if (next(it) != s.end() && it != s.begin() &&
                (*prev(it)).is_inter(*next(it)))
                return true;
            s.erase(it);
        }
    }
    return false;
}