#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;
vector<int> ve[maxn], ve2[maxn];
vector<int> sta;  // 存第一次dfs1()的结果，即标记点的先后顺序，优先级小的点先进
int vis[maxn];    // vis[i]标记第一次dfs1()点i是否访问过
int col
    [maxn];  // col[i]标记点i属于第几个强连通分量，同时记录dfs2()过程中点i是否访问过
int cnt;     // cnt表示强连通分量的个数
void dfs1(int x) {
    vis[x] = 1;
    for (auto it : ve[x])
        if (!vis[it]) dfs1(it);
    sta.push_back(x);  // 记录点的先后顺序，按照拓扑排序，优先级大的放在S的后面
}

void dfs2(int x) {
    if (col[x]) return;
    col[x] = cnt;
    for (auto it : ve[x])
        if (!col[it]) dfs2(it);
}
void Kosaraju(int n) {
    cnt = 0;
    sta.clear();
    memset(vis, 0, sizeof(vis));
    memset(col, 0, sizeof(col));
    for (int i = 1; i <= n; i++)  // 搜索所有点
        dfs1(i);
    for (int i = n - 1; i >= 0; i--) {
        if (!col[sta[i]]) {
            cnt++;
            dfs2(sta[i]);
        }
    }
}
