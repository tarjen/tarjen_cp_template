// 0base；普通数据下标[0,n-1]；其余数值、位编号按算法含义使用。
const int maxn = 2e5 + 10;
vector<int> ve[maxn];
int a[maxn];
int n;
int build() {
    if (!n) return -1;
    int top = 0;
    vector<int> Stack(n + 1, 0);
    for (int i = 0; i < n; i++) {
        ve[i].clear();
        ve[i].resize(2, -1);
    }
    Stack[++top] = 0;
    for (int i = 1; i < n; i++) {
        while (top && a[Stack[top]] >= a[i]) top--;
        if (!top)
            ve[i][0] = Stack[top + 1];
        else
            ve[i][0] = ve[Stack[top]][1], ve[Stack[top]][1] = i;
        Stack[++top] = i;
    }
    return Stack[1];
}
