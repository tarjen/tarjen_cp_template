const int maxn=1e5+10;
vector<int>ve[maxn];
int dep[maxn],f[21][maxn];
void dfs(int x,int fa)
{
	dep[x]=dep[fa]+1;
	for(int i=0;i<=19;i++)
		f[i+1][x]=f[i][f[i][x]];
    for(auto it:ve[x])
	{
		if(it==fa) continue;
		f[0][it]=x;
		dfs(it,x);
	}
}
int lca(int x,int y)
{
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=20;i>=0;i--)
	{
		if(dep[f[i][x]]>=dep[y]) x=f[i][x];
		if(x==y) return x;
	}
	for(int i=20;i>=0;i--)
		if(f[i][x]!=f[i][y])
			x=f[i][x],y=f[i][y];
	return f[0][x];
}