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
// #import_code("src/prepare/solve.cpp")
// #import_code("src/prepare/duipai.cpp")

= 通用基础
== Int128
#import_code("src/others/大数int128.cpp")
== 线性基
#import_code("src/others/线性基.cpp")
== 并查集（带关系）
#import_code("src/others/可以判断不同或相同的并查集.cpp")
== 树状数组
#import_code("src/data_structure/树状数组.cpp")
== 组合数
#import_code("src/math/组合数带模运算ca.cpp")
== EXGCD
#import_code("src/math/exgcd.cpp")

= 字符串
== KMP
#import_code("src/string/kmp.cpp")
== Hash
#import_code("src/string/hash.cpp")
== Trie
#import_code("src/string/字典树trie.cpp")
== Manacher
#import_code("src/string/manacher.cpp")
// 自动机和后缀数组篇幅较长，复制黏贴版保留；赛时按题目需要补充。
// #import_code("src/string/AC自动机.cpp")
// #import_code("src/string/后缀自动机SAM.cpp")
// #import_code("src/string/倍增sa.cpp")

= 图论
== LCA
#import_code("src/data_structure/最近公共祖先LCA.cpp")
== Segment Tree
#import_code("src/data_structure/SegmentTree.cpp")
== 二分图匹配
#import_code("src/graph/二分图匹配.cpp")
== 最大流（只返回流值）
#import_code("src/graph/maxflow只算值版本.cpp")
== Tarjan 缩点
#import_code("src/graph/tarjan缩点.cpp")
// 费用流、带花树、支配树等低频模板放在复制黏贴版。
// #import_code("src/graph/最小费用最大流.cpp")
// #import_code("src/graph/带花树.cpp")

= 几何基础
== 点与向量
#import_code("src/geometry/点与向量.cpp")
== 直线
#import_code("src/geometry/直线.cpp")
== 凸包
#import_code("src/geometry/点集的凸包.cpp")
// 圆、半平面交等依赖较多，按题目需要从复制黏贴版取用。
// #import_code("src/geometry/圆.cpp")
// #import_code("src/geometry/半平面交.cpp")

= 数学补充（按需抄写）
// #import_code("src/math/ntt.cpp")
// #import_code("src/math/FFT.cpp")
// #import_code("src/math/线性递推.cpp")
// #import_code("src/math/高斯消元(模意义).cpp")
