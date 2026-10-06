// 用法：
// 依赖：几何开头、点、极角排序、直线。
// vector<Line> sides = {{{0,0},{1,0}}, {{2,0},{-1,1}}, {{0,2},{0,-1}}};
// auto boundary = halfinter(sides);  // 每条直线的左侧为可行半平面。
// 返回边界直线集合；函数额外加入 [-lim,lim]^2 的包围框，默认 lim=1e9。
vector<Line> halfinter(vector<Line> l, const point_t lim = 1e9) {
    const auto check = [](const Line& a, const Line& b, const Line& c) {
        return a.toleft(b.inter(c)) < 0;
    };
    // 无精度误差的方法，但注意取值范围会扩大到三次方
    /*const auto check=[](const Line &a,const Line &b,const Line &c)
    {
        const Point
    p=a.v*(b.v^c.v),q=b.p*(b.v^c.v)+b.v*(c.v^(b.p-c.p))-a.p*(b.v^c.v); return
    p.toleft(q)<0;
    };*/
    l.push_back({{-lim, 0}, {0, -1}});
    l.push_back({{0, -lim}, {1, 0}});
    l.push_back({{lim, 0}, {0, 1}});
    l.push_back({{0, lim}, {-1, 0}});
    sort(l.begin(), l.end());
    deque<Line> q;
    for (size_t i = 0; i < l.size(); i++) {
        if (i > 0 && l[i - 1].v.toleft(l[i].v) == 0 &&
            l[i - 1].v * l[i].v > eps)
            continue;
        while (q.size() > 1 && check(l[i], q.back(), q[q.size() - 2]))
            q.pop_back();
        while (q.size() > 1 && check(l[i], q[0], q[1])) q.pop_front();
        if (!q.empty() && q.back().v.toleft(l[i].v) <= 0) return vector<Line>();
        q.push_back(l[i]);
    }
    while (q.size() > 1 && check(q[0], q.back(), q[q.size() - 2])) q.pop_back();
    while (q.size() > 1 && check(q.back(), q[0], q[1])) q.pop_front();
    return vector<Line>(q.begin(), q.end());
}