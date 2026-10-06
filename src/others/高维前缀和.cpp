// 用法：
// n=2，f={1,2,3,4}；执行下方 SOS DP 后 f={1,3,4,10}。
// f 长度为 1<<n；结果 f[mask] 是原数组所有 submask 的和。
// mask 与位号均 0base；直接在已有数组上原地计算。
for (int j = 0; j < n; j++)
    for (int i = 0; i < 1 << n; i++)
        if (i >> j & 1) f[i] += f[i ^ (1 << j)];