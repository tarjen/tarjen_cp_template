// 用法：
// 三点不共线；先准备 Point a,b,c，以及输出变量 X/Y/r 和 dis2 函数。
// 例如 a=(1,0)、b=(0,1)、c=(-1,0)，cal(a,b,c) 后圆心为 (0,0)。
// 当前 r 由外部 dis2(a) 计算，其含义取决于该函数，不能默认当半径。
// 通用圆相关操作另见 圆.cpp。
// 原理：令圆心 O=a+u，由 |O-a|²=|O-b|² 得 (b-a)*u=|b-a|²/2。
// 对 c 同理得到二元一次方程组，用克拉默法则解出 u，再加回 a。
// d 是 (b-a)^(c-a)，三点共线时为 0，不能唯一确定圆；计算 O(1)。
void cal(Point& a, Point& b, Point& c) {  // 圆上三点定圆心
    double a1 = b.x - a.x, b1 = b.y - a.y, c1 = (a1 * a1 + b1 * b1) / 2;
    double a2 = c.x - a.x, b2 = c.y - a.y, c2 = (a2 * a2 + b2 * b2) / 2;
    double d = a1 * b2 - a2 * b1;
    X = a.x + (c1 * b2 - c2 * b1) / d;
    Y = a.y + (a1 * c2 - a2 * c1) / d;
    r = dis2(a);
}
