// 用法：
// int x, y;
// int d = exgcd(12, 18, x, y);  // d=6，且 12*x+18*y=6。
// 求 a*x+b*y=gcd(a,b) 的一组解，要求 a,b 不同时为 0。
int exgcd(int a, int b, int& x, int& y) {  // 求ax+by=gcd(a,b)  !(a==0&&b==0)
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int d = exgcd(b, a % b, x, y);
    int t = x;
    x = y;
    y = t - (a / b) * y;
    return d;
}