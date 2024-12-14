#import "template.typ": *

// Take a look at the file `template.typ` in the file panel
// to customize this template and discover how it works.
#show: project.with(
  title: "Antiamuny Code Library",
  authors: ("tarjen",),
  logo: "logo.png",
  twoside: true,
)

// for balck printing
// #set raw(theme: "BW.tmtheme")

// auto pagebreak after each section
#show heading.where(level: 1): it => {
  if counter(page).at(here()).first()  != 1 {
    pagebreak(weak: true)
  }
  it
}

= 赛前准备
== 测样例脚本(python版)
#import_code("src/prepare/test.py")
#pagebreak(weak: true)

== 对拍(cpp版本)
#import_code("src/prepare/duipai.cpp")
== 对拍(bat版本)
#import_code("src/prepare/duipai.bat")

= 杂项
== Rand
#import_code("src/others/rand.cpp")
== Time
#import_code("src/others/time.cpp")
== 子集枚举
#import_code("src/others/子集枚举.cpp")
== 高维前缀和
#import_code("src/others/高维前缀和.cpp")
== 三分
#import_code("src/others/三分.cpp")
== Bitset
#import_code("src/others/bitset.cpp")
== Bitset手写
#import_code("src/others/bitset手写.cpp")
== Lcslen(n2/w)
#import_code("src/others/lcslen(n2w).cpp")
== wqs二分
#import_code("src/others/wqs二分.cpp")
== 可以判断不同或相同的并查集
#import_code("src/others/可以判断不同或相同的并查集.cpp")
== Int128
#import_code("src/others/大数int128.cpp")
== 树哈希
#import_code("src/others/树哈希.cpp")
== 求s所有前缀对于t的所有子串的最长公共子序列长度
#import_code("src/others/求s所有前缀对于t的所有子串的lcs长度.cpp")
== 线性基
#import_code("src/others/线性基.cpp")
== 维护多个二维向量能够表示的范围
#import_code("src/others/维护多个二维向量能够表示的范围.cpp")


= 字符串
== AC自动机
#import_code("src/string/AC自动机.cpp")
== Dequehash
#import_code("src/string/dequehash.cpp")
== Exkmp
#import_code("src/string/exkmp.cpp")
== Hash
#import_code("src/string/hash.cpp")
== Kmp
#import_code("src/string/kmp.cpp")
== Manacher
#import_code("src/string/manacher.cpp")
== 倍增SA
#import_code("src/string/倍增sa.cpp")
== 后缀自动机SAM
#import_code("src/string/后缀自动机SAM.cpp")
== 回文自动机PAM
#import_code("src/string/回文自动机PAM.cpp")
== 最小表示
#import_code("src/string/最小表示.cpp")
== Runs
#import_code("src/string/runs.cpp")


= 图论
== Johnson全源最短路
#import_code("src/graph/johnson全源最短路.cpp")
== Kosaraju
#import_code("src/graph/kosaraju.cpp")
== K短路
#import_code("src/graph/K短路.cpp")
== Maxflow只算值版本
#import_code("src/graph/maxflow只算值版本.cpp")
== Maxflow网络流最大流
#import_code("src/graph/maxflow网络流最大流.cpp")
== Tarjan缩点
#import_code("src/graph/tarjan缩点.cpp")
== 二分图匹配
#import_code("src/graph/二分图匹配.cpp")
== 二分图最优匹配
#import_code("src/graph/二分图最优匹配.cpp")
== 二分图染色
#import_code("src/graph/二分图染色.cpp")
== 圆方树
#import_code("src/graph/圆方树.cpp")
== 基环树
#import_code("src/graph/基环树.cpp")
== 带权并查集dsu
#import_code("src/graph/带权并查集dsu.cpp")
== 带花树
#import_code("src/graph/带花树.cpp")
== 带负环最小费用最大流
#import_code("src/graph/带负环最小费用最大流.cpp")
== 支配树
#import_code("src/graph/支配树.cpp")
== 最小环
#import_code("src/graph/最小环.cpp")
== 最小费用最大流
#import_code("src/graph/最小费用最大流.cpp")
== 欧拉回路
#import_code("src/graph/欧拉回路.cpp")
== 三四元环计数
#import_code("src/graph/三四元环计数.cpp")

= 数据结构

== SegmentSet
#import_code("src/data_structure/SegmentSet.cpp")
== SegmentTree
#import_code("src/data_structure/SegmentTree.cpp")
== 三维偏序cdq
#import_code("src/data_structure/三维偏序cdq.cpp")
== 主席树
#import_code("src/data_structure/主席树.cpp")
== 二维树状数组
#import_code("src/data_structure/二维树状数组.cpp")
== 动态开点线段树
#import_code("src/data_structure/动态开点线段树.cpp")
== 可持久化01trie
#import_code("src/data_structure/可持久化01trie.cpp")
== 最近公共祖先LCA
#import_code("src/data_structure/最近公共祖先LCA.cpp")
== Lca(o1)
#import_code("src/data_structure/lca(o1).cpp")
== 点分治
#import_code("src/data_structure/点分治.cpp")
== 珂朵莉树
#import_code("src/data_structure/珂朵莉树.cpp")
== 笛卡尔树
#import_code("src/data_structure/笛卡尔树.cpp")
== 线段树区间加区间历史最小值
#import_code("src/data_structure/线段树区间加区间历史最小值.cpp")
== 莫队
#import_code("src/data_structure/莫队mo.cpp")
== 虚树
#import_code("src/data_structure/虚树xushu.cpp")
== LCT维护联通性
#import_code("src/data_structure/LCT维护联通性.cpp")
== 树链剖分
#import_code("src/data_structure/树链剖分.cpp")
== 树上k级祖先
#import_code("src/data_structure/树上k级祖先.cpp")
== Splay
#import_code("src/data_structure/Splay.cpp")
== 楼房重建
#import_code("src/data_structure/楼房重建.cpp")
== 李超树
#import_code("src/data_structure/李超树.cpp")

= 数学
== 组合数
#import_code("src/math/组合数带模运算ca.cpp")
== BSGS指数方程余数问题(求a^x=b%p)
#import_code("src/math/BSGS指数方程余数问题(求a^x=b%p).cpp")
== EXGCD
#import_code("src/math/exgcd.cpp")
== FFT
#import_code("src/math/FFT.cpp")
== FWT
#import_code("src/math/FWT.cpp")
== 莫比乌斯反演
#import_code("src/math/mob莫比乌斯反演.cpp")
== NTT
#import_code("src/math/NTT.cpp")
== 任意模数NTT
#import_code("src/math/任意模数ntt.cpp")
== Pollard_Rho
#import_code("src/math/大数分解质因数.cpp")
== 扩展中国剩余定理
#import_code("src/math/扩展中国剩余定理.cpp")
== 拉格朗日插值
#import_code("src/math/拉格朗日插值.cpp")
== 拉格朗日插值没有模数
#import_code("src/math/拉格朗日插值没有模数.cpp")
== 杜教筛
#import_code("src/math/杜教筛.cpp")
== 线性筛质数
#import_code("src/math/线性筛质数.cpp")
== 线性递推
#import_code("src/math/线性递推.cpp")
== 辛普森积分
#import_code("src/math/辛普森积分.cpp")
== 高斯消元(模意义)
#import_code("src/math/高斯消元(模意义).cpp")
== 高斯消元(浮点数)
#import_code("src/math/高斯消元(浮点数).cpp")
== Matrix
#import_code("src/math/matrix.cpp")
== MIN25
#import_code("src/math/min25(质数幂次和).cpp")


= 计算几何
== 开头
#import_code("src/geometry/开头.cpp")
== 点与向量
#import_code("src/geometry/点与向量.cpp")
== 极角排序
#import_code("src/geometry/极角排序.cpp")
== 直线
#import_code("src/geometry/直线.cpp")
== 线段
#import_code("src/geometry/线段.cpp")
== 多边形
#import_code("src/geometry/多边形.cpp")
== 凸多边形
#import_code("src/geometry/凸多边形.cpp")
== 圆
#import_code("src/geometry/圆.cpp")
== 判断多条线段是否有交点
#import_code("src/geometry/判断多条线段是否有交点.cpp")
== 半平面交
#import_code("src/geometry/半平面交.cpp")
== 圆面积并
#import_code("src/geometry/圆面积并.cpp")
== 多边形面积并
#import_code("src/geometry/多边形面积并.cpp")
== 点集形成的最小最大三角形
#import_code("src/geometry/点集形成的最小最大三角形.cpp")
== 点集的凸包
#import_code("src/geometry/点集的凸包.cpp")
== 给定三点求圆心
#import_code("src/geometry/给定三点求圆心.cpp")

#include "src/note/note.typ"