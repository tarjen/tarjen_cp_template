#include <bits/stdc++.h>
using namespace std;
int const N = 1510 * 4, M = 75010;
int e[M], ne[M], h[N], idx;
int n, m, k, match[N], backup[N], st[N];
void add(int a, int b) { e[idx] = b, ne[idx] = h[a], h[a] = idx++; }
int find(int x) {
    for (int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if (!st[j]) {
            st[j] = 1;
            if (!match[j] || find(match[j])) {
                match[j] = x;
                return 1;
            }
        }
    }
    return 0;
}
int main() {
    cin >> n >> m >> k;
    memset(h, -1, sizeof h);
    for (int i = 1, a, b; i <= k; ++i) {
        scanf("%d%d", &a, &b);
        add(a, b + n);
    }
    int maxMatch = 0;
    for (int i = 1; i <= n; ++i) {
        memset(st, 0, sizeof st);
        if (find(i)) maxMatch++;
    }
    cout << maxMatch << endl;
    return 0;
}
