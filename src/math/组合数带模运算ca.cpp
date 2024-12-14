#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 100010;
const int mod = 1e9 + 7;
int ksm(int x, int k) {
    int res = 1;
    while (k) {
        if (k & 1) res = res * x % mod;
        x = x * x % mod;
        k /= 2;
    }
    return res;
}
int ny(int x) { return ksm(x, mod - 2); }
void add(int &x, int y) {
    if ((x += y) >= mod) x -= mod;
}
void del(int &x, int y) {
    if ((x -= y) < 0) x += mod;
}
int inv[maxn], fac[maxn];
int C(int n, int m) {
    return n == 0 ? 1 : fac[n] * inv[n - m] % mod * inv[m] % mod;
}
int A(int n, int m) { return n == 0 ? 1 : fac[n] * inv[n - m] % mod; }
void init() {
    inv[0] = fac[0] = 1;
    inv[1] = 1;
    for (int i = 1; i < maxn; i++) {
        fac[i] = fac[i - 1] * i % mod;
    }
    inv[1] = 1;
    for (int i = 2; i < maxn; i++) {
        inv[i] = (int)(mod - mod / i) * inv[mod % i] % mod;
    }
    inv[0] = 1;
    for (int i = 1; i < maxn; i++) {
        inv[i] = inv[i - 1] * inv[i] % mod;
    }
}
signed main() {
    init();
    if (mod == (int)(1e9 + 7)) assert(C(2000, 1000) == 72475738);
    if (mod == 9982444353) assert(C(2000, 1000) == 472799582);
}