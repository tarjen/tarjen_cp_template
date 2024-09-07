#import "template.typ": *

// Take a look at the file `template.typ` in the file panel
// to customize this template and discover how it works.
#show: project.with(
  title: "Antiamuny Code Library",
  authors: (
    "tarjen",
  ),
  logo: "logo.png",
)

// auto pagebreak after each section
#show heading.where(level: 1): it => {
  pagebreak(weak: true)
  it
}
= 第零章

- 安装 `typst`:
  - Linux, macOS, WSL

    ```bash
    curl -fsSL https://typst.community/typst-install/install.sh | sh
    ```
  - Windows

    ```ps1
    irm https://typst.community/typst-install/install.ps1 | iex
    ```

- 安装 VSCode 插件 `tinymist`:
  - 打开 VSCode
  - 搜索 `tinymist` 安装插件

= 赛前准备
== 测样例脚本(python版)
#import_code("src/prepare/test.py")

== 测样例脚本(bash版)

== 对拍(cpp版本)
#import_code("src/prepare/duipai.cpp")

== 对拍(bat版本)
#import_code("src/prepare/duipai.bat")

= 杂项
== rand
#import_code("src/others/rand.cpp")
== time
#import_code("src/others/time.cpp")
== 子集枚举
#import_code("src/others/子集枚举.cpp")
== 高维前缀和
#import_code("src/others/高维前缀和.cpp")
== 三分
#import_code("src/others/三分.cpp")
== bitset
#import_code("src/others/bitset.cpp")
== bitset手写
#import_code("src/others/bitset手写.cpp")
== lcslen(n2w)
#import_code("src/others/lcslen(n2w).cpp")
== wqs二分
#import_code("src/others/wqs二分.cpp")
== 判断异或方程组是否有解
#import_code("src/others/判断异或方程组是否有解.cpp")
== 可以判断不同或相同的并查集
#import_code("src/others/可以判断不同或相同的并查集.cpp")
== 大数int128
#import_code("src/others/大数int128.cpp")
== 树哈希
#import_code("src/others/树哈希.cpp")
== 求s所有前缀对于t的所有子串的lcs长度
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


= 图论
== johnson全源最短路
#import_code("src/graph/johnson全源最短路.cpp")
== kosaraju
#import_code("src/graph/kosaraju.cpp")
== K短路
#import_code("src/graph/K短路.cpp")
== lca(o1)
#import_code("src/graph/lca(o1).cpp")
== maxflow只算值版本
#import_code("src/graph/maxflow只算值版本.cpp")
== maxflow网络流最大流
#import_code("src/graph/maxflow网络流最大流.cpp")
== tarjan缩点
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
#import_code("src/math/ntt.cpp")
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

= 计算几何
