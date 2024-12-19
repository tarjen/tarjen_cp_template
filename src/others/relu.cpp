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