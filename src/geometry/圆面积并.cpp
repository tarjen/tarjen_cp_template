// 圆面积并
// 轮廓积分，复杂度 O(n^2logn)
// ans[i] 表示被至少覆盖了 i+1 次的区域的面积
vector<long double> area_union(const vector<Circle> &circs) {
    const size_t siz = circs.size();
    using arc_t = tuple<Point, long double, long double, long double>;
    vector<vector<arc_t>> arcs(siz);
    const auto eq = [](const arc_t &u, const arc_t &v) {
        const auto [u1, u2, u3, u4] = u;
        const auto [v1, v2, v3, v4] = v;
        return u1 == v1 && abs(u2 - v2) <= eps && abs(u3 - v3) <= eps &&
               abs(u4 - v4) <= eps;
    };

    auto cut_circ = [&](const Circle &ci, const size_t i) {
        vector<pair<long double, int>> evt;
        evt.push_back({-PI, 0});
        evt.push_back({PI, 0});
        int init = 0;
        for (size_t j = 0; j < circs.size(); j++) {
            if (i == j) continue;
            const Circle &cj = circs[j];
            if (ci.r < cj.r - eps && ci.relation(cj) >= 3) init++;
            const auto inters = ci.inter(cj);
            if (inters.size() == 1)
                evt.push_back(
                    {atan2l((inters[0] - ci.c).y, (inters[0] - ci.c).x), 0});
            if (inters.size() == 2) {
                const Point dl = inters[0] - ci.c, dr = inters[1] - ci.c;
                long double argl = atan2l(dl.y, dl.x),
                            argr = atan2l(dr.y, dr.x);
                if (abs(argl + PI) <= eps) argl = PI;
                if (abs(argr + PI) <= eps) argr = PI;
                if (argl > argr + eps) {
                    evt.push_back({argl, 1});
                    evt.push_back({PI, -1});
                    evt.push_back({-PI, 1});
                    evt.push_back({argr, -1});
                } else {
                    evt.push_back({argl, 1});
                    evt.push_back({argr, -1});
                }
            }
        }
        sort(evt.begin(), evt.end());
        int sum = init;
        for (size_t i = 0; i < evt.size(); i++) {
            sum += evt[i].second;
            if (abs(evt[i].first - evt[i + 1].first) > eps)
                arcs[sum].push_back(
                    {ci.c, ci.r, evt[i].first, evt[i + 1].first});
            if (abs(evt[i + 1].first - PI) <= eps) break;
        }
    };

    const auto oint = [](const arc_t &arc) {
        const auto [cc, cr, l, r] = arc;
        if (abs(r - l - PI - PI) <= eps) return 2.0l * PI * cr * cr;
        return cr * cr * (r - l) + cc.x * cr * (sin(r) - sin(l)) -
               cc.y * cr * (cos(r) - cos(l));
    };

    for (size_t i = 0; i < circs.size(); i++) {
        const auto &ci = circs[i];
        cut_circ(ci, i);
    }
    vector<long double> ans(siz);
    for (size_t i = 0; i < siz; i++) {
        long double sum = 0;
        sort(arcs[i].begin(), arcs[i].end());
        int cnt = 0;
        for (size_t j = 0; j < arcs[i].size(); j++) {
            if (j > 0 && eq(arcs[i][j], arcs[i][j - 1]))
                arcs[i + (++cnt)].push_back(arcs[i][j]);
            else
                cnt = 0, sum += oint(arcs[i][j]);
        }
        ans[i] = sum / 2;
    }
    return ans;
}