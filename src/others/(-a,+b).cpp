if ((a <= b) ^ (x.a <= x.b)) return a <= b;
if (a <= b) {
    if (a == x.a) return b < x.b;
    return a < x.a;
} else {
    if (b == x.b) return a > x.a;
    return b > x.b;
}