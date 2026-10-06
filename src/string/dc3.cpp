// 1base；Suffix sa(s); sa/rk/ht及后缀起点从1开始，sa[0]为空后缀。
#include <bits/stdc++.h>
using namespace std;
// s,rk下标从0开始，ht sa下标从1开始
#define F(x) ((x) / 3 + ((x) % 3 == 1 ? 0 : tb))
#define G(x) ((x) < tb ? (x) * 3 + 1 : ((x) - tb) * 3 + 2)
const int INF = 0x3f3f3f3f;
struct Suffix {
    string s;
    int n;
    explicit Suffix(const string& text) : s(text), n(text.size()) { init(); }
    vector<int> sa, rk, ht;
    vector<int> wa, wb, wv, wc;
    int c0(int* r, int a, int b) {
        return r[a] == r[b] && r[a + 1] == r[b + 1] && r[a + 2] == r[b + 2];
    }
    int c12(int k, int* r, int a, int b) {
        if (k == 2) {
            return r[a] < r[b] || (r[a] == r[b] && c12(1, r, a + 1, b + 1));
        } else {
            return r[a] < r[b] || (r[a] == r[b] && wv[a + 1] < wv[b + 1]);
        }
    }
    void sort(int* r, int* a, int* b, int n, int m) {
        int i;
        for (i = 0; i < n; i++) {
            wv[i] = r[a[i]];
        }
        for (i = 0; i < m; i++) {
            wc[i] = 0;
        }
        for (i = 0; i < n; i++) {
            wc[wv[i]]++;
        }
        for (i = 1; i < m; i++) {
            wc[i] += wc[i - 1];
        }
        for (i = n - 1; i >= 0; i--) {
            b[--wc[wv[i]]] = a[i];
        }
    }
    void dc3(int* r, int* sa, int n, int m) {
        int i, j, *rn = r + n, *san = sa + n, ta = 0, tb = (n + 1) / 3, tbc = 0,
                  p;
        r[n] = r[n + 1] = 0;
        for (i = 0; i < n; i++) {
            if (i % 3 != 0) {
                wa[tbc++] = i;
            }
        }
        sort(r + 2, wa.data(), wb.data(), tbc, m);
        sort(r + 1, wb.data(), wa.data(), tbc, m);
        sort(r, wa.data(), wb.data(), tbc, m);
        for (p = 1, rn[F(wb[0])] = 0, i = 1; i < tbc; i++) {
            rn[F(wb[i])] = c0(r, wb[i - 1], wb[i]) ? p - 1 : p++;
        }
        if (p < tbc) {
            dc3(rn, san, tbc, p);
        } else {
            for (i = 0; i < tbc; i++) {
                san[rn[i]] = i;
            }
        }
        for (i = 0; i < tbc; i++) {
            if (san[i] < tb) {
                wb[ta++] = san[i] * 3;
            }
        }
        if (n % 3 == 1) {
            wb[ta++] = n - 1;
        }
        sort(r, wb.data(), wa.data(), ta, m);
        for (i = 0; i < tbc; i++) {
            wv[wb[i] = G(san[i])] = i;
        }
        for (i = 0, j = 0, p = 0; i < ta && j < tbc; p++) {
            sa[p] = c12(wb[j] % 3, r, wa[i], wb[j]) ? wa[i++] : wb[j++];
        }
        for (; i < ta; p++) {
            sa[p] = wa[i++];
        }
        for (; j < tbc; p++) {
            sa[p] = wb[j++];
        }
    }
    void da(int* r, int* sa, int* height, int n, int m) {
        for (int i = 0; i < n; i++) {
            r[i] = (unsigned char)s[i] + 1;
        }
        for (int i = n; i < n * 3; i++) {
            r[i] = 0;
        }
        dc3(r, sa, n + 1, m);
        for (int i = 0; i <= n; i++) {
            r[sa[i]] = i;
        }
        int k = 0;
        for (int i = 0; i < n; i++) {
            if (k) {
                k--;
            }
            int j = sa[r[i] - 1];
            while (i + k < n && j + k < n && s[i + k] == s[j + k]) {
                k++;
            }
            height[r[i]] = k;
        }
    }
    void init() {
        n = s.size();
        sa.assign(3 * (n + 3), 0);
        rk.assign(3 * (n + 3), 0);
        ht.assign(n + 1, 0);
        wa.assign(n + 3, 0);
        wb.assign(n + 3, 0);
        wv.assign(n + 3, 0);
        wc.assign(max(n + 3, 300), 0);
        if (n)
            da(rk.data(), sa.data(), ht.data(), n, 300);
        else
            sa[0] = 0;
        // DC3内部从0计算；公开数组统一1base，空后缀位置为n+1。
        for (int i = 0; i <= n; i++) sa[i]++;
        for (int i = n; i >= 1; i--) rk[i] = rk[i - 1];
        rk[0] = 0;
    }
    void writ() {
        int n = s.size();
        cout << s << "\n";
        for (int i = 1; i <= n; i++) cout << sa[i] << " ";
        cout << "\n";
        for (int i = 1; i <= n; i++) cout << ht[i] << " ";
        cout << "\n";
        for (int i = 1; i <= n; i++) cout << rk[i] << " ";
        cout << "\n";
    }
};

#undef F
#undef G
