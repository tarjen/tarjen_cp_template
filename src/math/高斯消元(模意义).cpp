#define int long long
const int eps = 0;
const int maxn = 220;
const int mod = 1e6 + 3;
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
int a[maxn][maxn],
    x[maxn];  // 方程左边的矩阵和方程右边的值，求解之后x存的就是结果
int Gauss(int equ, int var) {  // equ 方程数 var 未知数个数  return 1表示有解
    int i, j, k, col, max_r;
    for (k = 0, col = 0; k < equ && col < var; k++, col++) {
        max_r = k;
        for (i = k + 1; i < equ; i++)
            if ((a[i][col]) > (a[max_r][col])) max_r = i;
        if ((a[max_r][col]) == 0) return 0;
        if (k != max_r) {
            for (j = col; j < var; j++) swap(a[k][j], a[max_r][j]);
            swap(x[k], x[max_r]);
        }
        x[k] = x[k] * ny(a[k][col]) % mod;
        for (j = col + 1; j < var; j++) a[k][j] = a[k][j] * ny(a[k][col]) % mod;
        a[k][col] = 1;
        for (i = 0; i < equ; i++)
            if (i != k) {
                del(x[i], x[k] * a[i][col] % mod);
                for (j = col + 1; j < var; j++)
                    del(a[i][j], a[k][j] * a[i][col] % mod);
                a[i][col] = 0;
            }
    }
    return 1;
}