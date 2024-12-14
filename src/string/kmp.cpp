#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;
struct KMP {                 // 1base
    int len1, n, nxt[maxn];  // nxt表示以i为结尾的前缀与后缀相同的长度
    char s1[maxn], s[maxn];
    void build() {
        n = strlen(s + 1);
        nxt[1] = 0;
        int x = 2, now = 1;  // x是s2当前搜索到的位置，now是前缀位置
        while (x <= n) {
            if (s[x] == s[now]) {
                nxt[x] = now;
                now++;
                x++;
            } else {
                if (now > 1) {
                    now = nxt[now - 1] + 1;
                } else {
                    nxt[x] = 0;
                    now = 1;
                    x++;
                }
            }
        }
    }
    void find() {  // s1 1base
        int now = 1, tar = 1;
        len1 = strlen(s1 + 1);
        while (tar <= len1) {
            if (s1[tar] == s[now]) {
                tar++;
                now++;
            } else {
                if (now > 1) {
                    now = nxt[now - 1] + 1;
                } else
                    tar++;
            }
            if (now == n + 1) {
                printf("%d\n", tar - now + 1);
            }
        }
    }
};
KMP sol;
int main() {
    scanf("%s%s", sol.s1 + 1, sol.s + 1);
    sol.build();
    sol.find();
    for (int i = 1; i <= sol.n; i++) cout << sol.nxt[i] << " ";
    return 0;
}