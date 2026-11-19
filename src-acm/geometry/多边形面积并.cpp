// 用法：
// 依赖：几何基础类型与多边形.cpp。
// Polygon a; a.p = {{0,0}, {1,0}, {0,1}};
// auto area = area_union(vector<Polygon>{a});  // 并面积应为 area[0]=0.5。
// area[i] 是至少覆盖 i+1 次的面积；输入顶点须逆时针。
// 原理：把每条有向边按其他多边形的交点切开，扫描区间内的覆盖次数。
// 被其他多边形覆盖 k 次的边段，归入“至少覆盖 k+1 次”的边界。
// 对边界累加端点叉积再除 2；同向重合边逐层后移，反向内边界相互抵消。
// 设总边数 E，逐边收集并排序至多 O(E) 个事件，整体 O(E² log E)。
vector<long double> area_union(const vector<Polygon>& polys) {
    const size_t siz = polys.size();
    vector<vector<pair<Point, Point>>> segs(siz);
    const auto check = [](const Point& u, const Segment& e) {
        return !((u < e.a && u < e.b) || (u > e.a && u > e.b));
    };

    auto cut_edge = [&](const Segment& e, const size_t i) {
        // 输入逆时针使内部位于边的左侧，穿过其他边界时更新覆盖数 sum。
        const Line le{e.a, e.b - e.a};
        vector<pair<Point, int>> evt;
        evt.push_back({e.a, 0}); evt.push_back({e.b, 0});
        for (size_t j = 0; j < polys.size(); j++) {
            if (i == j) continue;
            const auto& pj = polys[j];
            for (size_t k = 0; k < pj.p.size(); k++) {
                const Segment s = {pj.p[k], pj.p[pj.nxt(k)]};
                if (le.toleft(s.a) == 0 && le.toleft(s.b) == 0) {
                    evt.push_back({s.a, 0}); evt.push_back({s.b, 0});
                } else if (s.is_inter(le)) {
                    const Line ls{s.a, s.b - s.a};
                    const Point u = le.inter(ls);
                    if (le.toleft(s.a) < 0 && le.toleft(s.b) >= 0)
                        evt.push_back({u, -1});
                    else if (le.toleft(s.a) >= 0 && le.toleft(s.b) < 0)
                        evt.push_back({u, 1});
                }
            }
        }
        sort(evt.begin(), evt.end());
        if (e.a > e.b) reverse(evt.begin(), evt.end());
        // 事件沿当前边方向扫描；共线边只切分位置，重复边在汇总时分层处理。
        int sum = 0;
        for (size_t i = 0; i < evt.size(); i++) {
            sum += evt[i].second;
            const Point u = evt[i].first, v = evt[i + 1].first;
            if (!(u == v) && check(u, e) && check(v, e))
                segs[sum].push_back({u, v});
            if (v == e.b) break;
        }
    };

    for (size_t i = 0; i < polys.size(); i++) {
        const auto& pi = polys[i];
        for (size_t k = 0; k < pi.p.size(); k++) {
            const Segment ei = {pi.p[k], pi.p[pi.nxt(k)]};
            cut_edge(ei, i);
        }
    }
    vector<long double> ans(siz);
    for (size_t i = 0; i < siz; i++) {
        long double sum = 0;
        sort(segs[i].begin(), segs[i].end());
        int cnt = 0;
        for (size_t j = 0; j < segs[i].size(); j++) {
            if (j > 0 && segs[i][j] == segs[i][j - 1])
                segs[i + (++cnt)].push_back(segs[i][j]);
            else
                cnt = 0, sum += segs[i][j].first ^ segs[i][j].second;
        }
        ans[i] = sum / 2;
    }
    return ans;
}
