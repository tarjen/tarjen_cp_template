#include <bits/stdc++.h>
using namespace std;
const int N = 2e6;
struct SAM {
    struct Node {
        int tr[26];
        int len, fa;
        Node() {
            memset(tr, 0, sizeof(tr));
            len = fa = 0;
        }
    } ep[N << 1];
    int last, tot, n;
    char base;
    vector<int> edg[N << 1];
    int siz[N << 1];
    void init(int _n) {
        last = tot = 1;
        base = 'a';
        for (int i = 0; i <= 2 * _n; i++) {
            ep[i] = Node();
            edg[i].clear();
            siz[i] = 0;
        }
    }
    void insert(char x) {
        int c = x - base;
        int p = last;
        int np = last = ++tot;
        siz[np] = 1;
        ep[np].len = ep[p].len + 1;
        for (; p && !ep[p].tr[c]; p = ep[p].fa) ep[p].tr[c] = np;
        if (!p)
            ep[np].fa = 1;
        else {
            int q = ep[p].tr[c];
            if (ep[q].len == ep[p].len + 1)
                ep[np].fa = q;
            else {
                int nq = ++tot;
                ep[nq] = ep[q];
                ep[nq].len = ep[p].len + 1;
                ep[q].fa = ep[np].fa = nq;
                for (; p && ep[p].tr[c] == q; p = ep[p].fa) ep[p].tr[c] = nq;
            }
        }
    }
    void construct() {
        for (int i = 2; i <= tot; i++) {
            edg[ep[i].fa].push_back(i);
        }
    }
    void dfs(int u) {
        for (auto v : edg[u]) {
            dfs(v);
            siz[u] += siz[v];
        }
    }
    void build(string& s) {
        n = s.size();
        init(n);
        for (int i = 0; i < n; i++) {
            insert(s[i]);
        }
        construct();
        dfs(1);
    }

} sam;
