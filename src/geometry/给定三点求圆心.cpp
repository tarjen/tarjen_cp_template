void cal(Point& a, Point& b, Point& c) {  // 圆上三点定圆心
    double a1 = b.x - a.x, b1 = b.y - a.y, c1 = (a1 * a1 + b1 * b1) / 2;
    double a2 = c.x - a.x, b2 = c.y - a.y, c2 = (a2 * a2 + b2 * b2) / 2;
    double d = a1 * b2 - a2 * b1;
    X = a.x + (c1 * b2 - c2 * b1) / d;
    Y = a.y + (a1 * c2 - a2 * c1) / d;
    r = dis2(a);
}
