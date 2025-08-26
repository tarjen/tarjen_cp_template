std::vector<int> primes;
bool not_prime[MAXN];
int phi[MAXN], mu[MAXN], minp[MAXN];// 欧拉函数, 莫比乌斯函数, 最小质因子
int dcnt[MAXN], apper[MAXN];  // 约数个数,最小质因子出现次数
int dsum[MAXN], minp_sum[MAXN]; // 所有因数的和,最小质因子p的 p^0+p^1+...+p^k
void get_phi(int n) {
  phi[1] = 1; mu[1] = 1; dcnt[1] = 1; dsum[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (!not_prime[i]) {
      primes.push_back(i);
      phi[i] = i - 1;  mu[i] = -1; 
      minp[i] = i;     apper[i] = 1;
      dcnt[i] = 2;     minp_sum[i] = i + 1;
      dsum[i] = i + 1;
    }
    for (int p : primes) {
      if (i * p > n) break;
      not_prime[i * p] = true;
      if (i % p == 0) {
        phi[i * p] = phi[i] * p;
        mu[i * p] = 0;
        apper[i * p] = apper[i] + 1;
        dcnt[i * p] = dcnt[i] / (apper[i * p]) * (apper[i * p] + 1);
        minp_sum[i * p] = p * minp_sum[i] + 1;
        dsum[i * p] = dsum[i] / (minp_sum[i]) * (p * minp_sum[i] + 1);
        break;
      }
      // p是i*p的新的最小质因子
      minp[i * p] = p;
      phi[i*p] = phi[i]*phi[p]; mu[i * p] = -mu[i];
      apper[i * p] = 1;         dcnt[i * p] = dcnt[i] * 2;
      minp_sum[i * p] = p + 1;  dsum[i * p] = dsum[i] * (p + 1);
    }
  }
}
