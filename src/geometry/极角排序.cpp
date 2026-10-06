// 用法：
// 依赖：开头.cpp、点与向量.cpp。
// vector<Point> vectors = {{1,0}, {0,1}, {-1,0}, {0,-1}};
// sort(vectors.begin(), vectors.end(), argcmp());
// 按 (-1,0) 方向作为结尾的逆时针极角序排序，同方向视为等价。
// argcmp 是比较器，用于 sort，不是需要预处理的数据结构。
struct argcmp {
    bool operator()(const Point& a, const Point& b) const {
        const auto quad = [](const Point& a) {
            if (a.y < -eps) return 1;
            if (a.y > eps) return 4;
            if (a.x < -eps) return 5;
            if (a.x > eps) return 3;
            return 2;
        };
        const int qa = quad(a), qb = quad(b);
        if (qa != qb) return qa < qb;
        const auto t = a ^ b;
        // if (abs(t)<=eps) return a*a<b*b-eps;  // 不同长度的向量需要分开
        return t > eps;
    }
};