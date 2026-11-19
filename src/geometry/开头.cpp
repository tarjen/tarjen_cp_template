// 用法：
// 几何板子先复制本文件，再按依赖顺序复制点与向量、极角排序、直线等。
// pt 默认为 long double，eps 为比较容差，PI 为圆周率。
// 需要更大整数判定范围时可调整 pt；涉及交点/距离时用浮点类型。
// 原理：几何关系主要化为点积（投影）和叉积（方向、有向面积）。
// eps 用于判定接近 0；坐标放大后，叉积误差也会放大，须按题目选精度。
// 整数判定可令 eps=0；乘积、叉积和面积累加的范围也要容纳。
#include <bits/stdc++.h>
using namespace std;

using pt = long double;  // 全局数据类型，可修改为 long long 等

constexpr pt eps = 1e-8;
constexpr long double PI = 3.1415926535897932384l;
