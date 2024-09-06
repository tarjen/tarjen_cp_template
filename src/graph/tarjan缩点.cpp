stack<int>s;
vector<int>ve[maxn];
int col[maxn],num,dfn[maxn],low[maxn],dfstime;
void tarjan(int u)
{
    s.push(u);
    dfn[u]=low[u]=++dfstime;
    for(auto v:ve[u])
    {
        if(!dfn[v])
        {
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(!col[v]) low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u]==low[u])
    {
        col[u]=++num;
        while(s.top()!=u)
        {
            col[s.top()]=num;
            s.pop();
        }
        s.pop();
    }
}