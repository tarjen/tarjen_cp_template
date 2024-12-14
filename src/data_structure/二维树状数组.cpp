const int maxn = 1010;
struct treearray {
    int mkp1[maxn][maxn], mkp2[maxn][maxn], mkp3[maxn][maxn], mkp4[maxn][maxn];
    inline int lowbit(int x) { return x & (-x); }
    inline void Update(int x, int y, int k) {
        for (int i = x; i <= n; i += lowbit(i)) {
            for (int j = y; j <= m; j += lowbit(j)) {
                mkp1[i][j] += k;
                mkp2[i][j] += k * x;
                mkp3[i][j] += k * y;
                mkp4[i][j] += k * x * y;
            }
        }
    }
    inline void update(int a, int b, int x, int y, int k) {
        Update(a, b, k);
        Update(a, y + 1, -k);
        Update(x + 1, b, -k);
        Update(x + 1, y + 1, k);
    }
    inline int Query(int x, int y) {
        int ans = 0;
        for (int i = x; i >= 1; i -= lowbit(i)) {
            for (int j = y; j >= 1; j -= lowbit(j)) {
                ans += (x + 1) * (y + 1) * mkp1[i][j] - (y + 1) * mkp2[i][j] -
                       (x + 1) * mkp3[i][j] + mkp4[i][j];
            }
        }
        return ans;
    }
    inline int query(int a, int b, int x, int y) {
        return Query(x, y) + Query(a - 1, b - 1) - Query(x, b - 1) -
               Query(a - 1, y);
    }
};
treearray tri;
int main() {}
