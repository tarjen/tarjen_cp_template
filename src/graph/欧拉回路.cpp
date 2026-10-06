// 用法：
// 先用 add(u,v) 添加无向边，再 dfs(start)，逆序 st 得到欧拉路径。
// 顶点从 1 开始；需自行保证非零度点连通及度数满足欧拉条件。
// 当前片段 st 是 vector，但写了 st.push(u)，应先修成 st.push_back(u)。
// head/cut/tot/st 是全局状态；处理多组图时须自行重置。
#include <bits/stdc++.h>
using namespace std;
const int M = 2333, N = 666;
struct edge {
    int nxt, to;
} e[M << 1];
int head[N], tot = 1;
int cut[M << 1];
void add(int u, int v) {
    e[++tot] = (edge){head[u], v}, head[u] = tot;
    e[++tot] = (edge){head[v], u}, head[v] = tot;
}
vector<int> st;
void dfs(int u)  // 欧拉回路
{
    for (int i = head[u]; i != 0; i = e[i].nxt) {
        if (cut[i]) continue;
        int v = e[i].to;
        cut[i] = cut[i ^ 1] = 1;
        dfs(v);
    }
    st.push(u);
}
int main() { return 0; }
