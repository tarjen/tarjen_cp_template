// 用法：
// 本板是完整程序；输入 n m，然后 m 行 u v w；节点 0base。
// 示例：3 3，边为 (0,1,2)、(1,2,3)、(2,0,4)。
// 输出 9；无环输出 No solution.；用于非负权无向图，n<=100。
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e2 + 10;
const int inf = 2e7 + 10;
int a[maxn][maxn], b[maxn][maxn];
int main() {
    int n;
    cin >> n;
    int m;
    cin >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) a[i][j] = b[i][j] = inf;
        a[i][i] = b[i][i] = 0;
    }
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
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            for (int k = j + 1; k < i; k++) {
                ans = min(ans, a[i][j] + a[i][k] + b[j][k]);
            }
        }
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++)
                b[j][k] = min(b[j][i] + b[i][k], b[j][k]);
        }
    }
    if (ans == inf)
        cout << "No solution.";
    else
        cout << ans;
    return 0;
}
