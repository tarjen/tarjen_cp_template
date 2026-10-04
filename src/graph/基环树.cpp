// 1base连通无向简单基环树；Graph g(n); addedge(); Get(); dis(u,v); 每次Get内部初始化。
#include <bits/stdc++.h>
using namespace std;
/*
1 init
2 addedge
3 Get
*/
struct Graph{
    vector<vector<int>> ve;
    vector<int> base,id;
    vector<char> Incircle;
    vector<int> Circle;
    int len=0;
    vector<int> dep;
    vector<vector<int>> f;
    int lg;
    int n;
    explicit Graph(int n): ve(n+1),base(n+1),id(n+1,-1),Incircle(n+1),dep(n+1),
        f(n?__lg(n)+1:1,vector<int>(n+1)),lg(n?__lg(n)+1:1),n(n) { iota(base.begin(),base.end(),0); }
    explicit Graph(const vector<vector<int>>& graph): Graph((int)graph.size()-1) { ve=graph; Get(); }
    void addedge(int x,int y){
        ve[x].push_back(y);
        ve[y].push_back(x);
    }
    void dfs(int x,int fa)
    {
        base[x]=base[fa];
        dep[x]=dep[fa]+1;
        for(int i=0;i+1<lg;i++)
            f[i+1][x]=f[i][f[i][x]];
        for(auto it:ve[x])
        {
            if(it==fa) continue;
            f[0][it]=x;
            dfs(it,x);
        }
    }
    void Get(){
        Circle.clear(); len=0; fill(Incircle.begin(),Incircle.end(),0);
        fill(id.begin(),id.end(),-1); fill(dep.begin(),dep.end(),0);
        iota(base.begin(),base.end(),0);
        for(auto& row:f) fill(row.begin(),row.end(),0);
        vector<int> sta;
        vector<bool> vis(n+1,false);
        function<bool(int,int)> dfs2 = [&](int x,int h){
            vis[x]=true;
            sta.push_back(x);
            for(auto it:ve[x])if(it!=h){
                if(vis[it]){
                    Circle.push_back(it);
                    while(!sta.empty()&&sta.back()!=it){
                        Circle.push_back(sta.back());
                        sta.pop_back();
                    }
                    return true;
                }
                else{
                    if(dfs2(it,x))return true;
                }
            }
            sta.pop_back();
            return false;
        };
        dfs2(1,0);
        len=(int)Circle.size();
        for(auto it:Circle)Incircle[it]=true;
        for(auto it:Circle){
            for(auto it2:ve[it])if(!Incircle[it2]){
                f[0][it2]=it;
                dfs(it2,it);
            }
        }
        for(int i=0;i<len;i++)id[Circle[i]]=i;
    }
    int lca(int x,int y)
    {
        if(dep[x]<dep[y]) swap(x,y);
        for(int i=lg-1;i>=0;i--)
        {
            if(dep[f[i][x]]>=dep[y]) x=f[i][x];
            if(x==y) return x;
        }
        for(int i=lg-1;i>=0;i--)
            if(f[i][x]!=f[i][y])
                x=f[i][x],y=f[i][y];
        return f[0][x];
    }
    int dis(int x,int y){
        if(base[x]==base[y]){
            int l=lca(x,y);
            return dep[x]+dep[y]-2*dep[l];
        }
        else{
            int g=(id[base[x]]-id[base[y]]+len)%len;
            return dep[x]+dep[y]+min(g,len-g);
        }
    }
};
