// 用法：
// SegmentTree tr(0, 10);  // 整数横坐标闭区间 [0,10]。
// tr.update(0, 10, Line{2, 1, 1});  // 在 [0,10] 加入 y=2x+1，编号 1。
// Line best = tr.query(3);  // 返回最优直线；best.y(3)=7，best.id=1。
// 求最大值，同值优先较小编号；无直线时 id=0、值为负无穷。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double lf;
struct Line {
    lf k, b;
    int id;
    lf y(int x) { return k * x + b; }
};
const Line inf = {0, -numeric_limits<lf>::infinity(), 0};
struct Node {
    int l, r;
    Line res;
};
const lf eps = 1e-9;
int linecmp(Line l1, Line l2, int x) {  // l1>l2 return 1
    lf y1 = l1.y(x), y2 = l2.y(x);
    if (y1 > y2 + eps || (fabs(y1 - y2) < eps && l1.id < l2.id)) return 1;
    return 0;
}
struct SegmentTree {
    int lo, hi;
    vector<Node> a;
    SegmentTree(int lo, int hi) : lo(lo), hi(hi), a(4 * (hi - lo + 1) + 4) {
        assert(lo <= hi);
        build(1, lo, hi);
    }
    explicit SegmentTree(int n) : SegmentTree(1, n) {}
    void update(int l, int r, Line line) { update(1, l, r, line); }
    Line query(int x) {
        Line line = inf;
        query(1, x, line);
        return line;
    }
    void build(int i, int l, int r) {
        a[i].l = l, a[i].r = r;
        a[i].res = inf;
        if (l >= r) return;
        int mid = l + (r - l) / 2;
        build(i * 2, l, mid);
        build(i * 2 + 1, mid + 1, r);
    }
    void upd(int i, Line line) {
        if (linecmp(line, a[i].res, a[i].l + (a[i].r - a[i].l) / 2))
            swap(a[i].res, line);
        if (a[i].l == a[i].r) return;
        int opl = linecmp(line, a[i].res, a[i].l);
        int opr = linecmp(line, a[i].res, a[i].r);
        if (opl && opr) {
            a[i].res = line;
            return;
        }
        if ((!opl) && (!opr)) return;
        if (opl) upd(i * 2, line);
        if (opr) upd(i * 2 + 1, line);
    }
    void update(int i, int l, int r, Line line) {
        if (a[i].r < l || a[i].l > r || l > r) return;
        if (a[i].l >= l && a[i].r <= r) {
            upd(i, line);
            return;
        }
        update(i * 2, l, r, line);
        update(i * 2 + 1, l, r, line);
    }
    void query(int i, int x, Line& line) {
        if (a[i].r < x || a[i].l > x) return;
        if (linecmp(a[i].res, line, x)) line = a[i].res;
        if (a[i].l == a[i].r) return;
        query(i * 2, x, line);
        query(i * 2 + 1, x, line);
    }
};
