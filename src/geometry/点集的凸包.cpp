// 用法：
// 依赖：几何开头、点、极角排序、直线、线段、多边形、凸多边形。
// vector<Point> points = {{0,0}, {2,0}, {0,2}, {0.5,0.5}};
// Convex hull = convexhull(points);  // hull.p 为逆时针凸包顶点。
// 内部点会去掉，本例保留 3 个顶点；点数 <=2 时单独处理后续凸多边形操作。
Convex convexhull(vector<Point> p) {
    vector<Point> st;
    if (p.size() <= 2) return Convex{p};
    sort(p.begin(), p.end());
    const auto check = [](const vector<Point>& st, const Point& u) {
        const auto back1 = st.back(), back2 = *prev(st.end(), 2);
        return (back1 - back2).toleft(u - back1) <= 0;
    };
    for (const Point& u : p) {
        while (st.size() > 1 && check(st, u)) st.pop_back();
        st.push_back(u);
    }
    size_t k = st.size();
    p.pop_back();
    reverse(p.begin(), p.end());
    for (const Point& u : p) {
        while (st.size() > k && check(st, u)) st.pop_back();
        st.push_back(u);
    }
    st.pop_back();
    return Convex{st};
}