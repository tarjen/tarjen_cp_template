// 用户要求：补充字典序最小欧拉路径的使用方法；沿用无向图 Hierholzer。
// 用法：init(); add(u,v); ...; sort_edges(n); dfs(start);
// reverse(st.begin(),st.end());  // st 为最终顶点序列，长度应等于边数+1。
// 顶点 1base，n<N、边数<M；支持重边、自环；dfs 会消耗 head/cut。
// 无向欧拉回路要求所有度数为偶数；欧拉路径允许恰有两个奇度点。
// 非零度点须连通；先检查度数和合法起点，再用 st.size()==边数+1 检查覆盖。
// 字典序最小按“顶点序列”比较：
// 1. 有两个奇度点时，从编号较小的奇度点开始；全偶时从最小非零度点开始。
//    若题目指定 start，则必须遵守指定起点，并检查它是否满足度数条件。
// 2. sort_edges(n) 让每个点按邻点编号升序取边；边编号不变，保留 i^1 配对。
// 3. dfs 在回溯时 push_back，最后整体 reverse；不能把入栈顺序直接当答案。
// 例如边 {1,2},{1,3},{3,4},{4,1}，最小路径为 1,3,4,1,2。
// 无边时可选一个合法起点，答案只有该点；多组数据先 init() 再重新加边。
// 不要求字典序时可省去 sort_edges；当前弧遍历 O(m)，排序 O(sum(deg*log deg))。
#include <bits/stdc++.h>
using namespace std;
const int M = 2333, N = 666;
struct edge {
    int nxt, to;
} e[M << 1];
int head[N], tot = 1;
int cut[M << 1];
int deg[N];
vector<int> st;
void init() {
    memset(head, 0, sizeof head);
    memset(cut, 0, sizeof cut);
    memset(deg, 0, sizeof deg);
    tot = 1;
    st.clear();
}
void add(int u, int v) {
    assert(1 <= u && u < N && 1 <= v && v < N && tot + 2 < (M << 1));
    e[++tot] = (edge){head[u], v}, head[u] = tot;
    e[++tot] = (edge){head[v], u}, head[v] = tot;
    ++deg[u], ++deg[v];
}
void sort_edges(int n) {
    assert(0 <= n && n < N);
    for (int u = 1; u <= n; u++) {
        vector<int> ids;
        for (int i = head[u]; i; i = e[i].nxt) ids.push_back(i);
        sort(ids.begin(), ids.end(), [](int a, int b) {
            return make_pair(e[a].to, a) < make_pair(e[b].to, b);
        });
        head[u] = ids.empty() ? 0 : ids[0];
        for (int j = 0; j < (int)ids.size(); j++)
            e[ids[j]].nxt = j + 1 < (int)ids.size() ? ids[j + 1] : 0;
    }
}
void dfs(int u)  // 欧拉回路
{
    while (head[u]) {
        int i = head[u];
        head[u] = e[i].nxt;  // 当前弧：每条半边只扫描一次。
        if (cut[i]) continue;
        int v = e[i].to;
        cut[i] = cut[i ^ 1] = 1;
        dfs(v);
    }
    st.push_back(u);
}
int main() { return 0; }
