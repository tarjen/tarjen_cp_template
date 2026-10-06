// 用法：
// vec tr{};  // 值初始化为全 0，或先调用 clear()。
// tr.insert(2, 0);
// tr.insert(0, 3);
// bool possible = tr.query(4, 6);  // true，可用整数倍线性组合表示。
// bool impossible = tr.query(1, 0);  // false；不是仅允许非负系数的组合。
// 注意 int 中间运算范围；这是二维整数格，不是向量夹角范围。
int gcd(int x, int y) {
    if (y == 0)
        return x;
    else
        return gcd(y, x % y);
}
struct vec {
    int a00, a01, a11;
    void clear() { a00 = a01 = a11 = 0; }
    void insert(int x, int y) {
        while (x != 0) {
            int t = a00 / x;
            a00 -= x * t;
            a01 -= y * t;
            swap(a00, x);
            swap(a01, y);
        }
        a11 = gcd(a11, abs(y));
        if (a11 != 0) a01 %= a11;
    }
    bool query(int x, int y) {
        if (x != 0) {
            if (a00 == 0 || x % a00 != 0) return false;
            int t = x / a00;
            y -= a01 * t;
        }
        if (y == 0) {
            return true;
        } else
            return a11 != 0 && y % a11 == 0;
    }
};