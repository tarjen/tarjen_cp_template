// 用法：
// 依赖：几何开头、点、极角排序、直线。
// vector<Line> sides = {{{0,0},{1,0}}, {{2,0},{-1,1}}, {{0,2},{0,-1}}};
// auto boundary = halfinter(sides);  // 每条直线的左侧为可行半平面。
// 返回边界直线集合；函数额外加入 [-lim,lim]^2 的包围框，默认 lim=1e9。
// 原理：按边界方向排序，双端队列维护当前交集的有效边界，整体 O(n log n)。
// 新半平面排除某个相邻边界交点时，弹去对应队首/队尾；最后检查首尾闭合。
// lim 须包住需要的区域；加框后求的是截断交集，不能用它直接判断原交集无界。
vector<Line> halfinter(vector<Line> l, const pt lim = 1e9) {
    const auto check = [](const Line& a, const Line& b, const Line& c) {
        return a.toleft(b.inter(c)) < 0;
    };
    // 免除法版本：整数乘积范围扩大到三次方；浮点计算仍有舍入误差。
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
    // 直线排序已让同向的更紧约束在前，因此后续同向边界可以跳过。
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
    // 扫描时只保证局部相邻可行，闭合时还须满足首尾两条边界。
    while (q.size() > 1 && check(q.back(), q[0], q[1])) q.pop_front();
    return vector<Line>(q.begin(), q.end());
}
