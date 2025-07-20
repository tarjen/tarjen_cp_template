int main() {
    while (m--) {
        int x, y;
        cin >> x >> y;
        int w;
        cin >> w;
        a[x][y] = min(a[x][y], w);
        a[y][x] = min(a[y][x], w);
        b[x][y] = min(b[x][y], w);
        b[y][x] = min(b[y][x], w);
    }
    int ans = inf;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            for (int k = j + 1; k < i; k++) {
                ans = min(ans, a[i][j] + a[i][k] + b[j][k]);
            }
        }
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= n; k++)
                b[j][k] = min(b[j][i] + b[i][k], b[j][k]);
        }
    }
}