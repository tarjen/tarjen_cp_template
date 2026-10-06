// 用法：
// node f{0, 0, 10, 10};  // 在 [0,10] 线性增长，两端截断。
// int y = f.get(12);  // 返回 10；f.get(-2)=0。
// node g{2, 1, 8, 7};
// node h = f + g;  // 复合函数，h(x)=g(f(x))。
// l/lv、r/rv 是两个拐点的坐标与函数值。
struct node {
    int l, lv, r, rv;
    int get(int x) {
        if (x >= r) return rv;
        if (x >= l && x <= r) return x - l + lv;
        return lv;
    }
    // node write(string name){
    //     cout<<name<<" l="<<l<<" lv="<<lv<<" r="<<r<<" rv="<<rv<<"
    //     val="<<val<<endl; return *this;
    // }
};
node operator+(node a, node b) {
    if (a.lv >= b.r) {
        auto mid = b.get(a.lv);
        return node{a.l, mid, a.l, mid};
    }
    if (a.rv <= b.l) {
        auto mid = b.get(a.rv);
        return node{a.r, mid, a.r, mid};
    }
    if (a.lv <= b.l) {
        int d = b.l - a.lv;
        a.l += d;
        a.lv = b.lv;
    } else
        a.lv = b.get(a.lv);
    if (a.rv >= b.r) {
        int d = a.rv - b.r;
        a.r -= d;
        a.rv = b.rv;
    } else
        a.rv = b.get(a.rv);
    return a;
};