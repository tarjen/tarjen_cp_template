#import "template.typ": *

// ACM 赛时抄写版：只保留高频、接口稳定、可以直接拼进题解的类封装。
// 完整复制黏贴版请使用 main-copy.typ（main.typ 仍保持兼容）。
#show: project.with(
  title: "Tarjen ACM Contest Template",
  authors: ("tarjen",),
  logo: "logo.png",
  twoside: true,
)

// 黑白打印时可打开：
// #set raw(theme: "BW.tmtheme")

#show heading.where(level: 1): it => {
  if counter(page).at(here()).first() != 1 { pagebreak(weak: true) }
  it
}

= 赛前准备（可选）
// 赛时通常不抄对拍工具；需要时取消注释。
// #import_code("src-acm/prepare/solve.cpp")
// #import_code("src-acm/prepare/duipai.cpp")

= 通用基础
== Int128
#import_code("src-acm/others/大数int128.cpp")
== 线性基
#import_code("src-acm/others/线性基.cpp")
== 并查集（带关系）
#import_code("src-acm/others/可以判断不同或相同的并查集.cpp")
== 树状数组
#import_code("src-acm/data_structure/树状数组.cpp")
== LineContainer（动态凸包单点最小值）
#import_code("src-acm/data_structure/LineContainer.cpp")
== 组合数
#import_code("src-acm/math/组合数带模运算ca.cpp")
== EXGCD
#import_code("src-acm/math/exgcd.cpp")

= 字符串
== KMP
#import_code("src-acm/string/kmp.cpp")
== Hash
#import_code("src-acm/string/hash.cpp")
== Trie
#import_code("src-acm/string/字典树trie.cpp")
== Manacher
#import_code("src-acm/string/manacher.cpp")
// 自动机和后缀数组篇幅较长，复制黏贴版保留；赛时按题目需要补充。
// #import_code("src-acm/string/AC自动机.cpp")
// #import_code("src-acm/string/后缀自动机SAM.cpp")
// #import_code("src-acm/string/倍增sa.cpp")

= 图论
== LCA
#import_code("src-acm/data_structure/最近公共祖先LCA.cpp")
== Segment Tree
#import_code("src-acm/data_structure/SegmentTree.cpp")
== HK 二分图最大匹配
#import_code("src-acm/graph/HK.cpp")
// 逐点增广版本按需抄写。
// #import_code("src-acm/graph/二分图匹配.cpp")
== 最大流（只返回流值）
#import_code("src-acm/graph/maxflow只算值版本.cpp")
== Tarjan 缩点
#import_code("src-acm/graph/tarjan缩点.cpp")
// 费用流、带花树、支配树等低频模板放在复制黏贴版。
// #import_code("src-acm/graph/最小费用最大流.cpp")
// #import_code("src-acm/graph/带花树.cpp")

= 几何基础
== 点与向量
#import_code("src-acm/geometry/点与向量.cpp")
== 直线
#import_code("src-acm/geometry/直线.cpp")
== 凸包
#import_code("src-acm/geometry/点集的凸包.cpp")
// 圆、半平面交等依赖较多，按题目需要从复制黏贴版取用。
// #import_code("src-acm/geometry/圆.cpp")
// #import_code("src-acm/geometry/半平面交.cpp")

= 数学补充（按需抄写）
== 多项式 k 次幂（平方复杂度）
#import_code("src-acm/math/多项式幂(n2).cpp")
// #import_code("src-acm/math/ntt.cpp")
// #import_code("src-acm/math/FFT.cpp")
// #import_code("src-acm/math/线性递推.cpp")
// #import_code("src-acm/math/高斯消元(模意义).cpp")
