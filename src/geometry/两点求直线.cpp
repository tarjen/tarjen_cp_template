// 用法：auto [a,b,c] = line_abc({1,2}, {3,4});  // (1,-1,1)，即 x-y+1=0。
// 参数为 pair<ll,ll> 整数点，返回 array<ll,3>，可直接作 map/set 的键。
// 原理：法向量 (y1-y2,x2-x1) 与两点连线垂直，代入任一点得到 c。
// 先将 (a,b) 除以 gcd，再令首个非零系数为正，故同一直线的三元组唯一。
// 两点须不同；坐标绝对值 <=1e9 时 ll 足够，更大范围须检查差与乘积溢出。
// 仅依赖标准库及 using namespace std；gcd 复杂度 O(log C)，C 为坐标范围。
using ll = long long;
array<ll, 3> line_abc(pair<ll, ll> p, pair<ll, ll> q) {
    auto [x1, y1] = p;
    auto [x2, y2] = q;
    ll a = y1 - y2, b = x2 - x1, g = gcd(abs(a), abs(b));
    assert(g);
    a /= g; b /= g;
    if (a < 0 || (a == 0 && b < 0)) a = -a, b = -b;
    return {a, b, -a * x1 - b * y1};
}
