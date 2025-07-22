// 这里是 上凸 取min
// 上凸取max 二分的时候改变一下mid的变化方向
// 下凸取min 改变mid算贡献的符号
// min max 指的是求的是最大值 还是最小值
int l = -sum - 1000000000000ll, r = sum + 1000000000000ll;
int ans = 1e18;
while (l <= r) {
  int mid = (l + r) / 2ll;
  if (solve(mid) >= m) {
    ans = dp[1][0].first - m * mid;
    r = mid - 1;
  } else
    l = mid + 1;
}