// 用法：
// int a[2] = {1,2}, b[2] = {3,4}, c[2];  // 长度为 2 的幂，0base。
// fwtxor(a, 2, 1); fwtxor(b, 2, 1); mul(a, b, c, 2);
// fwtxor(c, 2, (mod+1)/2);  // 异或卷积得到 {11,10}，模 998244353。
// OR/AND 用 fwtor/fwtand，正变换 opt=1，逆变换 opt=-1。
// 下方 main 给出了三种完整调用流程，输入系数应在 [0,mod-1]。
#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;
void add(int& x, int y) {
    if ((x += y) >= mod) x -= mod;
}
void del(int& x, int y) {
    if ((x -= y) < 0) x += mod;
}
void fwtor(int a[], int m, int opt)  //(1,-1)
{
    for (int len = 2; len <= m; len <<= 1)
        for (int p = len >> 1, i = 0; i < m; i += len)
            for (int j = i; j < i + p; j++)
                if (opt > 0)
                    add(a[j + p], a[j]);
                else
                    del(a[j + p], a[j]);
}
void fwtand(int a[], int m, int opt)  //(1,-1)
{
    for (int len = 2; len <= m; len <<= 1)
        for (int p = len >> 1, i = 0; i < m; i += len)
            for (int j = i; j < i + p; j++)
                if (opt > 0)
                    add(a[j], a[j + p]);
                else
                    del(a[j], a[j + p]);
}
void fwtxor(int a[], int m, int opt)  //(1,1/2)
{
    for (int len = 2; len <= m; len <<= 1)
        for (int p = len >> 1, i = 0; i < m; i += len)
            for (int j = i; j < i + p; j++) {
                add(a[j], a[j + p]);
                a[j + p] = (a[j] - 2ll * a[j + p] % mod + mod) % mod;
                a[j] = 1ll * a[j] * opt % mod;
                a[j + p] = 1ll * a[j + p] * opt % mod;
            }
}
int a[1 << 17], b[1 << 17], c[1 << 17];
void mul(int a[], int b[], int c[], int m) {
    for (int i = 0; i < m; i++) c[i] = 1ll * a[i] * b[i] % mod;
}
void print(int a[], int m) {
    for (int i = 0; i < m; i++) cout << a[i] << " \n"[i == m - 1];
}
int main() {
    int n;
    cin >> n;
    int m = 1 << n;
    for (int i = 0; i < m; i++) cin >> a[i];
    for (int i = 0; i < m; i++) cin >> b[i];

    fwtor(a, m, 1), fwtor(b, m, 1), mul(a, b, c, m);
    fwtor(a, m, -1), fwtor(b, m, -1), fwtor(c, m, -1), print(c, m);

    fwtand(a, m, 1), fwtand(b, m, 1), mul(a, b, c, m);
    fwtand(a, m, -1), fwtand(b, m, -1), fwtand(c, m, -1), print(c, m);

    fwtxor(a, m, 1), fwtxor(b, m, 1), mul(a, b, c, m);
    fwtxor(c, m, (mod + 1) / 2), print(c, m);
}