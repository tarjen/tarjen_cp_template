#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 1e3;
struct EXKMP {  // S里找T

    char S[maxn], T[maxn];
    int next[maxn], extend[maxn];
    void Get_Next() {
        int lenT = strlen(T + 1), p = 1, pos;
        next[1] = lenT;  // 对于 next[1] 要特殊考虑
        while (p + 1 <= lenT && T[p] == T[p + 1]) ++p;
        next[pos = 2] = p - 1;  // next[2] 是为了初始化

        for (int i = 3; i <= lenT; i++) {  // 注意此时 k + 1 = i
            int len = next[i - pos + 1];
            if (len + i < p + 1)
                next[i] = len;  // 对应上面第一种情况
            else {
                int j = max(p - i + 1,
                            0);  // 找到前面对于 子串 最靠后已经匹配的位置
                while (i + j <= lenT && T[j + 1] == T[i + j])
                    ++j;                          // 第二种需要暴力匹配
                p = i + (next[pos = i] = j) - 1;  // 记得更新 p, pos
            }
        }
    }
    void ExKMP() {
        int lenS = strlen(S + 1), lenT = strlen(T + 1), p = 1, pos;
        Get_Next();
        while (p <= lenT && S[p] == T[p]) ++p;
        p = extend[pos = 1] = p - 1;  // 初始化 extend[1]

        for (int i = 2; i <= lenS; i++) {
            int len = next[i - pos + 1];
            if (len + i < p + 1)
                extend[i] = len;
            else {
                int j = max(p - i + 1, 0);
                while (i + j <= lenS && j <= lenT && T[j + 1] == S[i + j]) ++j;
                p = i + (extend[pos = i] = j) - 1;
            }
        }  // 和上面基本一模一样啦
    }
} sol;
int main() {
    scanf("%s", sol.S + 1);
    scanf("%s", sol.T + 1);

    sol.ExKMP();
    int len = strlen(sol.S + 1);
    for (int i = 1; i <= len; i++)
        printf("%d%c", sol.extend[i], i == len ? '\n' : ' ');

    return 0;
}