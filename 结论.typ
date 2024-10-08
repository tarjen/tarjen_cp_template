= 结论

== 异或

​$ a xor b+a xor c >= xor c $

​$ a xor b>=abs(a-b)>=gcd(a,b) $
== 绝对值等式/不等式

$ min(a, b) = a + b − max(a, b) $

$ max(abs(p_i − p_j),abs(q_i − q_j)) = 1 /2 (abs(p_i + q_i − p_j − q_j) + abs(p_i − q_i − p_j + q_j)) $

== 数论

任意的 $2n+1$ 个整数必定有 $n$ 个数的和是 $n$ 的倍数


$ ceil(m/n) = floor((m-1)/n) +1 $

对于函数 $g(x)=sum_(i=1)^L floor(x/i) $，对于任意的$B >= sqrt(x)$ ，都有

$ g(x)=sum_(i=1)^(min(L,B)) floor(x/i) + sum_(i=1)^(B)max(0,min(floor(x/i) ,L)-B) $

== Prufer序列

二分完全图生成树数量 $ n_1^(n_2-1) n_2^(n_1-1)$

n个节点,k个树,生成树数量$n^(k-2) product_(1)^(k)a_i$    

完全k分图生成树个数是 $n^(k-2) product (n-a_i)^(a_i-1)$

== 区间划分

给出一个序列（有正有负），给出上下界要求把序列划分成k个区间，使得所有的区间和在上下界内。

这个k一定是个区间。

== Kummer 定理

$V(x)$表示最大的2的几次幂整除x，$binom(i+j,j)$的 $V(x)=i+j$ 在2进制下的进位次数

== 卡特兰三角

前缀和的前缀和的通项

$ T(n,k)=sum_(j=0)^(k)T(n-1,j) $

$ T(n,k)=binom(n+k,n)*(n-k+1)/(n+1) $

