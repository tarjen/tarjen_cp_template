#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
void add(int &x,int y){
    if((x+=y)>=mod)x-=mod;
}
void solve(){
    int ans3=0,ans4=0;
    int n,m;cin>>n>>m;
    vector<pair<int,int>> edges(m);
    vector<int>d(n+1),flg(n+1),id(n+1),rk(n+1),c(n+1);
    vector<vector<int>> ve(n+1),f(n+1),g(n+1);
    for(int i=0;i<m;i++){
        int u,v;cin>>u>>v;
        edges[i]=make_pair(u,v);
        ve[u].push_back(v);
        ve[v].push_back(u);
    }
    for(int i=1;i<=n;i++)
        d[id[i]=i]=(int)ve[i].size();
    for(auto [u,v]:edges){
        if(d[u]>d[v]||(d[u]==d[v]&&u>v))g[u].push_back(v);
        else g[v].push_back(u);
    }
    sort(id.begin()+1,id.end(),[&](int x,int y){
        return d[x]<d[y];
    });
    for(int i=1;i<=n;i++)rk[id[i]]=i;
    for(int u=1;u<=n;u++)for(auto v:ve[u])
        if(rk[v]>rk[u])f[u].push_back(v);
    for(int u=1,C=0;u<=n;u++){
        for(auto v:ve[u])for(auto w:f[v])if(rk[w]>rk[u])add(ans4,c[w]),++c[w];
        for(auto v:ve[u])for(auto w:f[v])if(rk[w]>rk[u])c[w]=0;
        ++C;
        for(auto v:g[u])flg[v]=C;
        for(auto v:g[u])
            for(auto w:g[v])add(ans3,(flg[w]==C));
    }
    cout<<ans3<<" "<<ans4<<endl;
}
/*
5 7
1 2
2 3
4 2
5 1
1 4
3 5
3 1

ans3=3 ans4=2
*/