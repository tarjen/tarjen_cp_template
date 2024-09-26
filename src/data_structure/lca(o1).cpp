#define int long long 
const int maxn=1e5+10;//注意开两倍大小的空间 在dp上
vector<pair<int,int>>ve[maxn];
int dep[maxn];
pair<int,int>dp[21][maxn*3];
int red[maxn],d[maxn];
int Dep[maxn];
int dfn[maxn];
void dfs(int x,int fa,int l,int dis)
{
    if(red[x])dis=0;
    d[x]=dis;
	dep[x]=dep[fa]+1;
	Dep[x]=Dep[fa]+l;
    for(auto [it,len]:ve[x])
	{
		if(it==fa) continue;
		dfs(it,x,len,dis+len);
	}
}
vector<int> sp;
void dfs2(int u, int fa)
{

    dfn[u] = sp.size();
    sp.push_back(u);
    for (auto& e : ve[u])if(e.first!=fa)
    {
        int& v = e.first;
        dfs2(v, u);
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