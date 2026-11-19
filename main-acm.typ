#import "template.typ": *

// ACM 赛时抄写版：完整收录所有模板、工具与笔记，目录顺序与完整版一致。
// C++ 使用 src-acm/ 的手抄源码；其他资源与完整版共用。
#show: project.with(
  title: "Tarjen ACM Contest Template",
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

== 对拍（Python）
#import_code("src/prepare/duipai.py")
== Solve
#import_code("src-acm/prepare/solve.cpp")

= 杂项
== Rand
#import_code("src-acm/others/rand.cpp")
== Time
#import_code("src-acm/others/time.cpp")
== 子集枚举
#import_code("src-acm/others/子集枚举.cpp")
== 高维前缀和
#import_code("src-acm/others/高维前缀和.cpp")
== 三分
#import_code("src-acm/others/三分.cpp")
== Bitset手写
#import_code("src-acm/others/bitset手写.cpp")
== Lcslen(n2/w)
#import_code("src-acm/others/lcslen(n2w).cpp")
== wqs二分
#include "src/others/wqs二分.typ"
== 可以判断不同或相同的并查集
#import_code("src-acm/others/可以判断不同或相同的并查集.cpp")
== Int128
#import_code("src-acm/others/大数int128.cpp")
== 树哈希
#import_code("src-acm/others/树哈希.cpp")
== 求s所有前缀对于t的所有子串的最长公共子序列长度
#import_code("src-acm/others/求s所有前缀对于t的所有子串的lcs长度.cpp")
== 线性基
#import_code("src-acm/others/线性基.cpp")
#pagebreak(weak: true)
== 维护多个二维向量能够表示的范围
#import_code("src-acm/others/维护多个二维向量能够表示的范围.cpp")
== relu
#import_code("src-acm/others/relu.cpp")
== (-a,+b)贪心
#import_code("src-acm/others/(-a,+b).cpp")

= 字符串
== AC自动机
#import_code("src-acm/string/AC自动机.cpp")
== 字典树Trie
#import_code("src-acm/string/字典树trie.cpp")
== Dequehash
#import_code("src-acm/string/dequehash.cpp")
== Exkmp
#import_code("src-acm/string/exkmp.cpp")
#pagebreak(weak: true)
== Hash
#import_code("src-acm/string/hash.cpp")
== Kmp
#import_code("src-acm/string/kmp.cpp")
== Manacher
#import_code("src-acm/string/manacher.cpp")
== 倍增SA
#import_code("src-acm/string/倍增sa.cpp")
== DC3后缀数组
#import_code("src-acm/string/dc3.cpp")
== 后缀自动机SAM
#import_code("src-acm/string/后缀自动机SAM.cpp")
== 回文自动机PAM
#import_code("src-acm/string/回文自动机PAM.cpp")
== 最小表示
#import_code("src-acm/string/最小表示.cpp")
== Runs
#import_code("src-acm/string/runs.cpp")


= 图论
== Johnson全源最短路
#import_code("src-acm/graph/johnson全源最短路.cpp")
== Kosaraju
#import_code("src-acm/graph/kosaraju.cpp")
== K短路
#import_code("src-acm/graph/K短路.cpp")
== Maxflow只算值版本
#import_code("src-acm/graph/maxflow只算值版本.cpp")
== Maxflow网络流最大流
#import_code("src-acm/graph/maxflow网络流最大流.cpp")
== Tarjan缩点
#import_code("src-acm/graph/tarjan缩点.cpp")
== 点双边双
#import_code("src-acm/graph/点双边双.cpp")
== 二分图匹配
#import_code("src-acm/graph/二分图匹配.cpp")
== HK 二分图最大匹配
#import_code("src-acm/graph/HK.cpp")
#pagebreak(weak: true)
== 二分图最优匹配
#import_code("src-acm/graph/二分图最优匹配.cpp")
== 二分图染色
#import_code("src-acm/graph/二分图染色.cpp")
== 圆方树
#import_code("src-acm/graph/圆方树.cpp")
== 基环树
#import_code("src-acm/graph/基环树.cpp")
== 带权并查集dsu
#import_code("src-acm/graph/带权并查集dsu.cpp")
== 带花树
#import_code("src-acm/graph/带花树.cpp")
== 带负环最小费用最大流
#import_code("src-acm/graph/带负环最小费用最大流.cpp")
== 支配树
#import_code("src-acm/graph/支配树.cpp")
== 最小环
#import_code("src-acm/graph/最小环.cpp")
== 最小费用最大流
#import_code("src-acm/graph/最小费用最大流.cpp")
#pagebreak(weak: true)
== 欧拉回路
#import_code("src-acm/graph/欧拉回路.cpp")
== 三四元环计数
#import_code("src-acm/graph/三四元环计数.cpp")
== 有向图动态加边缩点
#import_code("src-acm/graph/有向图动态加边缩点.cpp")

= 数据结构
== LineContainer（动态凸包单点最小值）
#import_code("src-acm/data_structure/LineContainer.cpp")

== SegmentSet
#import_code("src-acm/data_structure/SegmentSet.cpp")
== SegmentTree
#import_code("src-acm/data_structure/SegmentTree.cpp")
#pagebreak(weak: true)
== SegmentTree单点
#import_code("src-acm/data_structure/SegmentTree单点.cpp")
== 线段树区间加区间求和
#import_code("src-acm/data_structure/线段树区间加区间求和getsum.cpp")
== 线段树区间加区间最小值
#import_code("src-acm/data_structure/线段树区间加区间getmin.cpp")
#pagebreak(weak: true)
== 线段树区间赋值区间最小值
#import_code("src-acm/data_structure/线段树区间赋值区间getmin.cpp")
== 01Trie
#import_code("src-acm/data_structure/01trie.cpp")
== 树状数组单点修改区间查询
#import_code("src-acm/data_structure/树状数组单点修改区间查询tree.cpp")
#pagebreak(weak: true)
== 树状数组区间修改区间查询
#import_code("src-acm/data_structure/树状数组.cpp")
== 三维偏序cdq
#import_code("src-acm/data_structure/三维偏序cdq.cpp")
== 主席树
#import_code("src-acm/data_structure/主席树.cpp")
== 二维树状数组
#import_code("src-acm/data_structure/二维树状数组.cpp")
== 动态开点线段树
#import_code("src-acm/data_structure/动态开点线段树.cpp")
== 可持久化01trie
#import_code("src-acm/data_structure/可持久化01trie.cpp")
== 最近公共祖先LCA
#import_code("src-acm/data_structure/最近公共祖先LCA.cpp")
== Lca(o1)
#import_code("src-acm/data_structure/lca(o1).cpp")
#pagebreak(weak: true)
== 点分治
#import_code("src-acm/data_structure/点分治.cpp")
== 珂朵莉树
#import_code("src-acm/data_structure/珂朵莉树.cpp")
== 笛卡尔树
#import_code("src-acm/data_structure/笛卡尔树.cpp")
== 线段树区间加区间历史最小值
#import_code("src-acm/data_structure/线段树区间加区间历史最小值.cpp")
== 线段树合并
#import_code("src-acm/data_structure/线段树合并.cpp")
#pagebreak(weak: true)
== 左偏树（可合并堆）
#import_code("src-acm/data_structure/左偏树.cpp")
== 可持久化线段树
#import_code("src-acm/data_structure/可持久化线段树.cpp")
#pagebreak(weak: true)
== 动态树直径
#import_code("src-acm/data_structure/动态树直径.cpp")
== 莫队
#import_code("src-acm/data_structure/莫队mo.cpp")
== 虚树
#import_code("src-acm/data_structure/虚树xushu.cpp")
== LCT维护联通性
#import_code("src-acm/data_structure/LCT维护联通性.cpp")
#pagebreak(weak: true)
== 树链剖分
#import_code("src-acm/data_structure/树链剖分.cpp")
== 树上k级祖先
#import_code("src-acm/data_structure/树上k级祖先.cpp")
== Splay
#import_code("src-acm/data_structure/Splay.cpp")
== 楼房重建
#import_code("src-acm/data_structure/楼房重建.cpp")
== 李超树
#import_code("src-acm/data_structure/李超树.cpp")
== 分层位图
#import_code("src-acm/data_structure/分层位图.cpp")

= 数学
== 组合数
#import_code("src-acm/math/组合数带模运算ca.cpp")
== BSGS指数方程余数问题(求a^x=b%p)
#import_code("src-acm/math/BSGS指数方程余数问题(求a^x=b%p).cpp")
== EXGCD
#import_code("src-acm/math/exgcd.cpp")
== FFT
#import_code("src-acm/math/FFT.cpp")
#pagebreak(weak: true)
== FWT
#import_code("src-acm/math/FWT.cpp")
== 莫比乌斯反演
#import_code("src-acm/math/mob莫比乌斯反演.cpp")
== NTT
#import_code("src-acm/math/ntt.cpp")
== 多项式 k 次幂（平方复杂度）
#import_code("src-acm/math/多项式幂(n2).cpp")
== 任意模数NTT
#import_code("src-acm/math/任意模数ntt.cpp")
== Pollard_Rho
#import_code("src-acm/math/大数分解质因数.cpp")
== 扩展中国剩余定理
#import_code("src-acm/math/扩展中国剩余定理.cpp")
#pagebreak(weak: true)
== 拉格朗日插值
#import_code("src-acm/math/拉格朗日插值.cpp")
== 拉格朗日插值没有模数
#import_code("src-acm/math/拉格朗日插值没有模数.cpp")
#pagebreak(weak: true)
== 杜教筛
#import_code("src-acm/math/杜教筛.cpp")
== 线性筛质数
#import_code("src-acm/math/线性筛质数.cpp")
== Meissel Lehmer质数计数
#import_code("src-acm/math/Meissel-Lehmer(求1-n质数数量).cpp")
== 线性递推
#import_code("src-acm/math/线性递推.cpp")
== 辛普森积分
#import_code("src-acm/math/辛普森积分.cpp")
== 高斯消元(模意义)
#import_code("src-acm/math/高斯消元(模意义).cpp")
#pagebreak(weak: true)
== 高斯消元(浮点数)
#import_code("src-acm/math/高斯消元(浮点数).cpp")
== 分数类
#import_code("src-acm/math/分数类.cpp")
#pagebreak(weak: true)
== 判断异或方程组是否有解
#import_code("src-acm/math/判断异或方程组是否有解.cpp")
== Matrix
#import_code("src-acm/math/matrix.cpp")
#pagebreak(weak: true)
== MIN25
#import_code("src-acm/math/min25(质数幂次和).cpp")


= 计算几何
== 开头
#import_code("src-acm/geometry/开头.cpp")
== 点与向量
#import_code("src-acm/geometry/点与向量.cpp")
== 极角排序
#import_code("src-acm/geometry/极角排序.cpp")
== 直线
#import_code("src-acm/geometry/直线.cpp")
#pagebreak(weak: true)
== 两点求直线标准式
#import_code("src-acm/geometry/两点求直线.cpp")
== 线段
#import_code("src-acm/geometry/线段.cpp")
== 射线判交
#import_code("src-acm/geometry/射线判交.cpp")
== 多边形
#import_code("src-acm/geometry/多边形.cpp")
== 凸多边形
#import_code("src-acm/geometry/凸多边形.cpp")
== 圆
#import_code("src-acm/geometry/圆.cpp")
#pagebreak(weak: true)
== 判断多条线段是否有交点
#import_code("src-acm/geometry/判断多条线段是否有交点.cpp")
== 半平面交
#import_code("src-acm/geometry/半平面交.cpp")
== 圆面积并
#import_code("src-acm/geometry/圆面积并.cpp")
== 多边形面积并
#import_code("src-acm/geometry/多边形面积并.cpp")
== 点集形成的最小最大三角形
#import_code("src-acm/geometry/点集形成的最小最大三角形.cpp")
== 点集的凸包
#import_code("src-acm/geometry/点集的凸包.cpp")
== 给定三点求圆心
#import_code("src-acm/geometry/给定三点求圆心.cpp")

#include "src/note/note.typ"
