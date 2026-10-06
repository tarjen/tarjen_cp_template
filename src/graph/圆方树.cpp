// 用法：
// 此板是函数内片段，先准备 n 与 0base 无向图 ve。
// vector<vector<int>> ve = {{1,2}, {0,2}, {0,1}};
// int n=3;
// 执行下面的代码后，原点 [0,n-1] 为圆点，新增 [n,cnt) 为方点。
// e1 为圆方树邻接表；当前从 tarjan(0) 开始，要求原图连通。
vector<vector<int>> e1(n);
int cnt = n;

int now = 0;
vector<int> dfn(n, -1), low(n);
vector<int> stk;
function<void(int)> tarjan = [&](int u) {
    stk.push_back(u);
    dfn[u] = low[u] = now++;
    for (auto v : ve[u]) {
        if (dfn[v] == -1) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
            if (low[v] == dfn[u]) {
                e1.push_back({});
                int x;
                do {
                    x = stk.back();
                    stk.pop_back();
                    e1[cnt].push_back(x);
                } while (x != v);
                e1[u].push_back(cnt);
                ++cnt;
            }
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
};
tarjan(0);