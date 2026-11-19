// 用法：node f{0,0,10,10}, g{2,1,8,7}; node h = f + g;
// h(x)=g(f(x))；cout << h 输出 (l,lv,r,rv)。
// 表示斜率为 1、两端截断的函数；须 l<=r 且 r-l=rv-lv。
// l==r 时为常量函数；标准库头文件与 using namespace std 由调用处提供。
struct node {
    int l, lv, r, rv;
    int get(int x) const {
        return int(clamp(1LL * x - l + lv, 1LL * lv, 1LL * rv));
    }
};
node operator+(node a, node b) {
    auto cut = [&](int x) {
        return int(clamp(1LL * x + a.l - a.lv, 1LL * a.l, 1LL * a.r));
    };
    return {cut(b.l), b.get(a.lv), cut(b.r), b.get(a.rv)};
}
ostream& operator<<(ostream& out, const node& a) {
    return out << "(" << a.l << "," << a.lv << "," << a.r << "," << a.rv << ")";
}
