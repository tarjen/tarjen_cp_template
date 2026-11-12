// 用法：
// 几何板子先复制本文件，再按依赖顺序复制点与向量、极角排序、直线等。
// point_t 默认为 long double，eps 为比较容差，PI 为圆周率。
// 需要更大整数判定范围时可调整 point_t；涉及交点/距离时用浮点类型。
#include <bits/stdc++.h>
using namespace std;

using point_t = long double;  // 全局数据类型，可修改为 long long 等

constexpr point_t eps = 1e-8;
constexpr long double PI = 3.1415926535897932384l;
