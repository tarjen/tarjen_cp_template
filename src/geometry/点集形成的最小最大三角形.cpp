// 用法：
// 依赖：几何开头、点与向量、极角排序。
// vector<Point> points = {{0,0}, {2,0}, {0,2}};
// auto [small, large] = minmax_triangle(points);  // 本例均为 4。
// 返回最小、最大三角形面积的两倍；实际面积需除以 2。
// 原理：转动投影方向；两点投影相等时交换次序，按法向量极角处理这些事件。
// 固定底边时面积正比于第三点到直线的距离：最小看邻近点，最大看两端极点。
// 共 O(n²) 个事件，排序 O(n² log n)，vx/pos 分别维护投影序及其逆排列。
pair<pt, pt> minmax_triangle(const vector<Point>& vec) {
    if (vec.size() <= 2) return {0, 0};
    vector<pair<int, int>> evt;
    evt.reserve(vec.size() * vec.size());
    pt maxans = 0, minans = numeric_limits<pt>::max();
    for (size_t i = 0; i < vec.size(); i++) {
        for (size_t j = 0; j < vec.size(); j++) {
            if (i == j) continue;
            if (vec[i] == vec[j])
                minans = 0;
            else
                evt.push_back({i, j});
        }
    }
    sort(evt.begin(), evt.end(),
         [&](const pair<int, int>& u, const pair<int, int>& v) {
             const Point du = vec[u.second] - vec[u.first],
                         dv = vec[v.second] - vec[v.first];
             return argcmp()({du.y, -du.x}, {dv.y, -dv.x});
         });
    vector<size_t> vx(vec.size()), pos(vec.size());
    for (size_t i = 0; i < vec.size(); i++) vx[i] = i;
    sort(vx.begin(), vx.end(), [&](int x, int y) { return vec[x] < vec[y]; });
    for (size_t i = 0; i < vx.size(); i++) pos[vx[i]] = i;
    for (auto [u, v] : evt) {
        // 当前 u,v 给出底边；先按交换前的投影序取最近/最远候选，再更新次序。
        const size_t i = pos[u], j = pos[v];
        const size_t l = min(i, j), r = max(i, j);
        const Point vecu = vec[u], vecv = vec[v];
        if (l > 0)
            minans = min(
                minans, abs((vec[vx[l - 1]] - vecu) ^ (vec[vx[l - 1]] - vecv)));
        if (r < vx.size() - 1)
            minans = min(
                minans, abs((vec[vx[r + 1]] - vecu) ^ (vec[vx[r + 1]] - vecv)));
        maxans = max({maxans, abs((vec[vx[0]] - vecu) ^ (vec[vx[0]] - vecv)),
                      abs((vec[vx.back()] - vecu) ^ (vec[vx.back()] - vecv))});
        if (i < j) swap(vx[i], vx[j]), pos[u] = j, pos[v] = i;
    }
    return {minans, maxans};
}
