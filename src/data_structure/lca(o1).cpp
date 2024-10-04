const int maxn=1e5+10;//注意开两倍大小的空间 在dp上
vector<pair<int,int>>ve[maxn];
int dep[maxn];
pair<int,int>dp[21][maxn*2];
int dfn[maxn];
vector<int> sp;
void dfs(int u, int fa)
{

    dfn[u] = sp.size();
    sp.push_back(u);
    for (auto& e : ve[u])if(e.first!=fa)
    {
        int& v = e.first;
        dfs(v, u);
        sp.push_back(u);
    }
}
void initrmq()
{
    int n = sp.size();
    for (int i = 0; i < n; i++) dp[0][i] = {dfn[sp[i]], sp[i]};
    for (int i = 1; (1 << i) <= n; i++)
        for (int j = 0; j + (1 << i) - 1 < n; j++)
            dp[i][j] = min(dp[i - 1][j], dp[i - 1][j + (1 << (i - 1))]);
}
int lca(int u, int v)
{
    int l = dfn[u], r = dfn[v];
    if (l > r) swap(l, r);
    int k = __lg(r-l+1);
    return min(dp[k][l], dp[k][r - (1 << k) + 1]).second;
}