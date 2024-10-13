= 结论

== 异或
$ a xor b>=abs(a-b)>=gcd(a,b) $

== 绝对值等式/不等式

$ min(a, b) = a + b - max(a, b) $

$ max(abs(p_i - p_j),abs(q_i - q_j)) = 1 / 2 (abs(p_i + q_i - p_j - q_j) + abs(p_i - q_i - p_j + q_j)) $

== 数论

任意的 $2n+1$ 个整数必定有 $n$ 个数的和是 $n$ 的倍数


$ ceil(m/n) = floor((m-1)/n) +1 $

对于函数 $g(x)=sum_(i=1)^L floor(x/i) $，对于任意的 $B >= sqrt(x)$ ，都有

$ g(x)=sum_(i=1)^(min(L,B)) floor(x/i) + sum_(i=1)^(B)max(0,min(floor(x/i) ,L)-B) $

== Prufer序列

二分完全图生成树数量 $ n_1^(n_2-1) n_2^(n_1-1)$

$n$ 个节点，$k$ 个树，生成树数量 $n^(k-2) product_(1)^(k)a_i$

完全 $k$ 分图生成树个数是 $n^(k-2) product (n-a_i)^(a_i-1)$

== Kummer 定理

$V(x)$ 表示最大的 $2$ 的几次幂整除 $x$， $binom(i+j,j) $的 $V(x)=i+j$ 在二进制下的进位次数

== 卡特兰三角

前缀和的前缀和的通项

$ T(n,k)=sum_(j=0)^(k)T(n-1,j) $

$ T(n,k)=binom(n+k,n) times (n-k+1) / (n+1) $

== 二项式反演

$ f(n)=sum_(i=0)^(n)binom(n,i)g(i) <=> g(n)=sum_(i=0)^(n)(-1)^(n-i)binom(n,i)f(i) $

$ f(k)=sum_(i=k)^(n)binom(i,k)g(i) <=> g(k)=sum_(i=k)^(n)(-1)^(i-k)binom(i,k)f(i) $

#pagebreak(weak: true)

== 矩阵树定理（所有生成树的权值和）

=== 无向图情况
设 $G$ 是一个有 $n$ 个顶点的无向图。定义度数矩阵 $D(G)$ 为


$ D_(i i)(G) = deg(i), D_(i j) = 0, i != j $
设 $ e(i,j)$ 为点 $i$ 与点 $j$ 相连的边数，并定义邻接矩阵 $A$ 为


$ A_(i j)(G)=A_(j i)(G)=e(i,j), i != j $
定义 Laplace 矩阵（亦称 Kirchhoff 矩阵）$L$ 为 $L(G) = D(G) - A(G)$，生成树权值和就是去掉一行一列之后的行列式

=== 有向图情况
将上述的 $deg(i)$ 改成 $deg^(o u t)(i) \/ deg^(i n)(i)$，并且删掉的一行一列就是根节点的对应的行列 那么分别就能得到 指向根节点的树/根节点指出去的树
== 区间划分

给出一个序列（有正有负），给出上下界要求把序列划分成 $k$ 个区间，使得所有的区间和在上下界内。

这个 $k$ 一定是个区间。

== 竞赛图

每次取等号是就是一个强联通分量独立出来，比如上一个取等号的位置是 $i$，当前是 $j$，那么 $[i+1,j]$ 就是一个强联通分量

竞赛图的强连通分量存在哈密顿回路，并且竞赛图存在哈密顿路

求一条竞赛图的哈密顿回路 ，类似归并排序的办法做

== Runs理论
位置不同的本原平方串（即最小整周期恰为 $l/2$ 的串）是 $O(n log n)$的

指数定义一个 $"run"(l,r,p)$ 的指数是 $frac(r-l+1,p)$，即 Period_p 在 $s[l,r]$ 中的出现次数。记作 $e(l,r,p)$。

一个串的所有串的指数和是 $O(n)$ 的。

因为一个平方子串一定会出现在某个 $"run"(l, r, p)$ 中，且长度一定是 $2p$ 的倍数，所以可以枚举所有 $"runs"$ ，枚举平方子串的长度 $2 k p$ ，再枚举左端点 $L in [l, l + p )$，就可以覆盖所有的平方子串，这样枚举的平方子串都可以对应到不同的本原平方子串 $[L + 2(k - 1)p, L + 2 k p - 1]$，然后一个串的本原平方子串个数是 $O(n log n)$ 的，所以上述方式枚举平方子串的复杂度是 $O(n log n)$ 的。还

一个串的本质不同的平方子串的个数是 $O(n)$ 的

#pagebreak(weak: true)

= 网络流

== 二分图最小点覆盖

定理内容：二分图最小点覆盖的点的数量*等于*二分图最大匹配的边的数量。

构造方法 ++ 简单证明：

首先求出二分图中的最大匹配，建议使用 Dinic.

从每一个非匹配的 *左部点* 出发，沿着非匹配边正向进行遍历，沿着匹配边反向进行遍历到的点进行标记。选取左部点中没有被标记过的点，右部点中被标记过的点，则这些点可以形成该二分图的最小点覆盖。

== 二分图最大独立集

最大独立集、最小顶点覆盖互为补集。

考虑最小顶点覆盖的补集中的一个点，与其相邻的点必须都在最小顶点覆盖中，才能够覆盖所有相邻的边。这句话的意思是，最小顶点覆盖的补集中的点两两不相邻。

同时考虑最大独立集的补集中的一个点，与该点相邻的点中一定有最大独立集中的点，为了覆盖这之间的边，该点必须属于最小定点覆盖。

== DAG求反链和构造反链(最小可重链链覆盖DAG)
反链大小就是最小可重链覆盖DAG的链数量

最小可重链覆盖和不可重的区别就是 是否求传递闭包

第一步：转化为最小可重链覆盖

0. 求出DAG的传递闭包
1. 对于DAG里面的边进行二分图的经典连边。
2. 求出最大独立集

第二步：通过最大独立集构造最长反链方案

考虑以下方法：对于每个顶点 $x$，如果 $x_l$ 和 $x_r$ 都在最大独立集中，那么将顶点 $x$ 加入到反链中。

由于最小顶点覆盖的大小为 $m$，所以最大独立集的大小为 $2n - m$。同时，设构造出的反链的大小为 $t$，则最大独立集的大小 $S$ 为 $t + sum( (x_l in S) and (x_r in S) )$。注意到因为后面这部分不会超过 $n$，所以可以推导出 $t >= n - m$。

换句话说，$t$ 至少为 $n - m$。实际上，根据Dilworth定理，$t$ 恰好等于 $n - m$，这样我们构建出了最长的反链方案。

== 最大权闭合子图

新建一个源点 $S$ 和汇点 $T$，从源点 $S$ 向 $w_i>0$ 的点连一条边权为 $w_i$ 的边，从所有 $w_i<0$ 的点向汇点 $T$ 连一条边权为 $-w_i$ 的边，原图中点与点之间的边不变，流量设为 $inf$

对新图求一遍最小割，最大权 $=sum_{w_i>0}w_i$ 减去最小割
