#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;  // 2*strlen
struct Suffix {
    int ht[N], rk[N], sa[N], y[N], c[N];
    int n, m;
    char s[N];
    int st[20][N];
    void init() {
        n = strlen(s + 1);
        m = 300;
        for (int i = 0; i <= m; i++) c[i] = 0;
        for (int i = 0; i <= 2 * n; i++) y[i] = 0;
        for (int i = 1; i <= n; i++) c[rk[i] = s[i]]++;
        for (int i = 1; i <= m; i++) c[i] += c[i - 1];
        for (int i = n; i >= 1; i--) sa[c[rk[i]]--] = i;
        for (int k = 1; k <= n; k <<= 1) {
            int p = 0;
            for (int i = n - k + 1; i <= n; i++) y[++p] = i;
            for (int i = 1; i <= n; i++) {
                if (sa[i] > k) {
                    y[++p] = sa[i] - k;
                }
            }
            for (int i = 0; i <= m; i++) c[i] = 0;
            for (int i = 1; i <= n; i++) c[rk[i]]++;
            for (int i = 1; i <= m; i++) c[i] += c[i - 1];
            for (int i = n; i >= 1; i--) sa[c[rk[y[i]]]--] = y[i];
            for (int i = 0; i <= n; i++) swap(rk[i], y[i]);
            rk[sa[1]] = p = 1;
            for (int i = 2; i <= n; i++) {
                rk[sa[i]] = (y[sa[i]] == y[sa[i - 1]] &&
                                     y[sa[i] + k] == y[sa[i - 1] + k]
                                 ? p
                                 : ++p);
            }
            if (p >= n) break;
            m = p;
        }
        for (int i = 1, k = 0; i <= n; i++) {
            if (k) k--;
            int j = sa[rk[i] - 1];
            while (s[i + k] == s[j + k]) k++;
            ht[rk[i]] = k;
        }
        for (int i = 1; i <= n; i++) st[0][i] = ht[i];
        for (int j = 1; j < 20; j++) {
            for (int i = 1; i + (1 << j) - 1 <= n; i++)
                st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
        }
    }
    int get(int l, int r) {
        int g = __lg(r - l + 1);
        return min(st[g][l], st[g][r - (1 << g) + 1]);
    }
    int lcp(int x, int y) {
        x = rk[x], y = rk[y];
        if (x == y) return n - x + 1;
        if (x > y) swap(x, y);
        return get(x + 1, y);
    }
    int query(int l1, int r1, int l2, int r2) {
        int len = lcp(l1, l2);
        len = min({len, r1 - l1 + 1, r2 - l2 + 1});
        if (len == min(r1 - l1 + 1, r2 - l2 + 1)) {
            if (r1 - l1 > r2 - l2) return 1;
            if (r1 - l1 < r2 - l2) return -1;
            if (r1 - l1 == r2 - l2) return 0;
        }
        char p = s[l1 + len], q = s[l2 + len];
        if (p > q) return 1;
        if (p == q) return 0;
        return -1;
    }
    void writ() {
        printf("%s\n", s + 1);
        for (int i = 1; i <= n; i++) cout << sa[i] << " ";
        ;
        cout << "\n";
        for (int i = 1; i <= n; i++) cout << ht[i] << " ";
        ;
        cout << "\n";
        for (int i = 1; i <= n; i++) cout << rk[i] << " ";
        ;
        cout << "\n";
    }
};
Suffix suf;