// 用法：
// 依赖：几何开头、点、极角排序、直线、线段、多边形。
// Convex poly; poly.p = {{0,0}, {2,0}, {0,2}};
// auto diameter_squared = poly.diameter2();  // 直径平方为 8。
// int relation = poly.is_in(Point{0.5,0.5});  // 1 内部，0 外部，-1 边上。
// 顶点逆时针、无重复或连续共线点，首点为字典序最小点；可先 convexhull。
// 原理：凸性使边方向、支撑点和扇形分区具有单调性，可用双指针或二分。
// 闵可夫斯基和/直径为线性，点包含/切点查询为对数复杂度。
// 除单独处理的 1/2 点情况外，按至少 3 点的非退化凸多边形使用；不传空集。
struct convex : polygon {
    // 闵可夫斯基和
    convex operator+(const convex& c) const {
        // 和多边形的边方向是两组凸包边方向的有序归并，起点也取两起点之和。
        // 累加边向量得到边界，并删去同向共线的中间点；O(n+m)。
        const auto& p = this->p;
        vector<Segment> e1(p.size()), e2(c.p.size()),
            edge(p.size() + c.p.size());
        vector<point> res;
        res.reserve(p.size() + c.p.size());
        const auto cmp = [](const Segment& u, const Segment& v) {
            return argcmp()(u.b - u.a, v.b - v.a);
        };
        for (size_t i = 0; i < p.size(); i++) e1[i] = {p[i], p[this->nxt(i)]};
        for (size_t i = 0; i < c.p.size(); i++) e2[i] = {c.p[i], c.p[c.nxt(i)]};
        rotate(e1.begin(), min_element(e1.begin(), e1.end(), cmp), e1.end());
        rotate(e2.begin(), min_element(e2.begin(), e2.end(), cmp), e2.end());
        merge(e1.begin(), e1.end(), e2.begin(), e2.end(), edge.begin(), cmp);
        const auto check = [](const vector<point>& res, const point& u) {
            const auto back1 = res.back(), back2 = *prev(res.end(), 2);
            return (back1 - back2).toleft(u - back1) == 0 &&
                   (back1 - back2) * (u - back1) >= -eps;
        };
        auto u = e1[0].a + e2[0].a;
        for (const auto& v : edge) {
            while (res.size() > 1 && check(res, u)) res.pop_back();
            res.push_back(u);
            u = u + v.b - v.a;
        }
        if (res.size() > 1 && check(res, res[0])) res.pop_back();
        return {res};
    }

    // 旋转卡壳
    // func 为更新答案的函数，可以根据题目调整位置
    template <typename F>
    void rotcaliper(const F& func) const {
        // 对固定边，离边最远的对踵点使三角形面积最大；边转动时 j 只向前。
        // 面积相等也枚举以免漏掉平行边端点；严格凸包上共 O(n)，要求至少 3 点。
        const auto& p = this->p;
        const auto area = [](const point& u, const point& v,
                             const point& w) { return (w - u) ^ (w - v); };
        for (size_t i = 0, j = 1; i < p.size(); i++) {
            const auto nxti = this->nxt(i);
            func(p[i], p[nxti], p[j]);
            while (area(p[this->nxt(j)], p[i], p[nxti]) >=
                   area(p[j], p[i], p[nxti])) {
                j = this->nxt(j);
                func(p[i], p[nxti], p[j]);
            }
        }
    }

    // 凸多边形的直径的平方
    pt diameter2() const {
        // 最远点对一定出现在对踵点对中，枚举对踵点与当前边的两个端点。
        const auto& p = this->p;
        if (p.size() == 1) return 0;
        if (p.size() == 2) return p[0].dis2(p[1]);
        pt ans = 0;
        auto func = [&](const point& u, const point& v,
                        const point& w) {
            ans = max({ans, w.dis2(u), w.dis2(v)});
        };
        rotcaliper(func);
        return ans;
    }

    // 判断点是否在凸多边形内
    // 复杂度 O(logn)
    // -1 点在多边形边上 | 0 点在多边形外 | 1 点在多边形内
    int is_in(const point& a) const {
        // 以 p[0] 为中心划分扇形，先排除外部角域，再二分所在三角形。
        // 最后判断相对该三角形外侧边的位置，边界单独返回 -1。
        const auto& p = this->p;
        if (p.size() == 1) return a == p[0] ? -1 : 0;
        if (p.size() == 2) return segment{p[0], p[1]}.is_on(a) ? -1 : 0;
        if (a == p[0]) return -1;
        if ((p[1] - p[0]).toleft(a - p[0]) == -1 ||
            (p.back() - p[0]).toleft(a - p[0]) == 1)
            return 0;
        const auto cmp = [&](const Point& u, const Point& v) {
            return (u - p[0]).toleft(v - p[0]) == 1;
        };
        const size_t i =
            lower_bound(p.begin() + 1, p.end(), a, cmp) - p.begin();
        if (i == 1) return segment{p[0], p[i]}.is_on(a) ? -1 : 0;
        if (i == p.size() - 1 && segment{p[0], p[i]}.is_on(a)) return -1;
        if (segment{p[i - 1], p[i]}.is_on(a)) return -1;
        return (p[i] - p[i - 1]).toleft(a - p[i - 1]) > 0;
    }

    // 凸多边形关于某一方向的极点
    // 复杂度 O(logn)
    // 参考资料：https://codeforces.com/blog/entry/48868
    template <typename F>
    size_t extreme(const F& dir) const {
        // 支撑点附近，方向与相邻边的叉积符号会改变；拆开环序后可二分转折。
        // dir 用于下方的固定方向或外点视线，不能随意传入不满足单调性的函数。
        const auto& p = this->p;
        const auto check = [&](const size_t i) {
            return dir(p[i]).toleft(p[this->nxt(i)] - p[i]) >= 0;
        };
        const auto dir0 = dir(p[0]);
        const auto check0 = check(0);
        if (!check0 && check(p.size() - 1)) return 0;
        const auto cmp = [&](const Point& v) {
            const size_t vi = &v - p.data();
            if (vi == 0) return 1;
            const auto checkv = check(vi);
            const auto t = dir0.toleft(v - p[0]);
            if (vi == 1 && checkv == check0 && t == 0) return 1;
            return checkv ^ (checkv == check0 && t <= 0);
        };
        return partition_point(p.begin(), p.end(), cmp) - p.begin();
    }

    // 过凸多边形外一点求凸多边形的切线，返回切点下标
    // 复杂度 O(logn)
    // 必须保证点在多边形外
    pair<size_t, size_t> tangent(const point& a) const {
        // 从外点观察凸包，正反两个视线方向的极点分别给出两个切点。
        const size_t i = extreme([&](const point& u) { return u - a; });
        const size_t j = extreme([&](const point& u) { return a - u; });
        return {i, j};
    }

    // 求平行于给定直线的凸多边形的切线，返回切点下标
    // 复杂度 O(logn)
    pair<size_t, size_t> tangent(const line& a) const {
        // 两侧平行支撑线对应 v 与 -v 的极点，无须逐点扫描。
        const size_t i = extreme([&](...) { return a.v; });
        const size_t j = extreme([&](...) { return -a.v; });
        return {i, j};
    }
};

using Convex = convex;
