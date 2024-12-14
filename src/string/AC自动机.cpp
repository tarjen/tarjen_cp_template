#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;
int n;
char c[maxn];
struct AC {
    int trie[maxn][26], tot;
    int e[maxn], fail[maxn], old[maxn];
    void init() {
        memset(trie, 0, sizeof(trie));
        memset(e, 0, sizeof(e));
        memset(fail, 0, sizeof(fail));
        memset(old, 0, sizeof(old));
        tot = 0;
    }
    void insert(char *t) {
        int x = 0;
        for (int i = 1; t[i]; i++) {
            if (!trie[x][t[i] - 'a']) {
                trie[x][t[i] - 'a'] = ++tot;
            }
            x = trie[x][t[i] - 'a'];
        }
        e[x]++;
    }
    queue<int> qu;
    void build() {
        for (int i = 0; i < 26; i++) {
            if (trie[0][i]) qu.push(trie[0][i]);
        }
        while (!qu.empty()) {
            int x = qu.front();
            qu.pop();
            for (int i = 0; i < 26; i++) {
                if (trie[x][i]) {
                    fail[trie[x][i]] = trie[fail[x]][i];
                    qu.push(trie[x][i]);
                } else
                    trie[x][i] = trie[fail[x]][i];
                old[trie[x][i]] = e[fail[trie[x][i]]] ? fail[trie[x][i]]
                                                      : old[fail[trie[x][i]]];
            }
        }
    }
    int query(
        char *
            t) {  // 这里是统计有多少模板串出现在了文本串之中，所以统计到了就要变成-1
        int x = 0, res = 0;
        for (int i = 1; t[i]; i++) {
            x = trie[x][t[i] - 'a'];
            for (int j = x; j && e[j] != -1; j = old[j]) {
                res += e[j];
                e[j] = -1;
            }
        }
        return res;
    }
};
AC ac;
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%s", c + 1);
        ac.insert(c);
    }
    ac.build();
    scanf("%s", c + 1);

    cout << ac.query(c) << endl;
    return 0;
}