// 用法：
// 先填写 f(x)，例如 return -(x-2)*(x-2);（单峰求最大值）。
// double best = sanfen(0.0, 4.0);  // 返回最大函数值 0，不是最优横坐标 2。
// 当前 f 留空，使用前必须实现；最小值问题需要反转比较方向。
double f(double x) {
    // something
}
const double eps = 1e-8;
double sanfen(double l, double r) {
    double mid, midr, ans;
    while (fabs(r - l) > eps) {
        mid = (l + r) / 2;
        midr = (mid + r) / 2;
        if (f(mid) < f(midr))
            l = mid;
        else
            r = midr;  // 求最大值
    }
    ans = f(l);
    return ans;
}