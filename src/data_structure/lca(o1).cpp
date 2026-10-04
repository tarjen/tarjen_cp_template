// 1base连通树；LCA t(n); addedge(u,v); build(root); lca(u,v)为O(1)。
#include <bits/stdc++.h>
using namespace std;

struct LCA {
    int n;
    vector<vector<pair<int,int>>> ve;
    vector<int> dep,dfn,sp;
    vector<vector<pair<int,int>>> dp;
    explicit LCA(int n): n(n),ve(n+1),dep(n+1),dfn(n+1) {}
    LCA(const vector<vector<pair<int,int>>>& graph,int root=1): LCA((int)graph.size()-1) { ve=graph; build(root); }
    void addedge(int u,int v,int w=1) { ve[u].push_back({v,w}); ve[v].push_back({u,w}); }
    void build(int root=1) {
        sp.clear(); fill(dep.begin(),dep.end(),0); fill(dfn.begin(),dfn.end(),0);
        if(!n) { dp.clear(); return; }
        struct Frame { int u,fa,next; };
        vector<Frame> stack{{root,0,0}};
        dfn[root]=0; sp.push_back(root);
        while(!stack.empty()) {
            auto& frame=stack.back(); int u=frame.u;
            if(frame.next==(int)ve[u].size()) {
                stack.pop_back(); if(!stack.empty()) sp.push_back(stack.back().u);
            } else {
                int v=ve[u][frame.next++].first;
                if(v==frame.fa) continue;
                dep[v]=dep[u]+1; dfn[v]=sp.size(); sp.push_back(v);
                stack.push_back({v,u,0});
            }
        }
        initrmq();
    }
    void initrmq() {
        int m=sp.size(); dp.assign(__lg(m)+1,vector<pair<int,int>>(m));
        for(int i=0;i<m;i++) dp[0][i]={dfn[sp[i]],sp[i]};
        for(int k=1;k<(int)dp.size();k++)
            for(int i=0;i+(1<<k)<=m;i++) dp[k][i]=min(dp[k-1][i],dp[k-1][i+(1<<(k-1))]);
    }
    int lca(int u,int v) const {
        int l=dfn[u],r=dfn[v]; if(l>r) swap(l,r);
        int k=__lg(r-l+1); return min(dp[k][l],dp[k][r-(1<<k)+1]).second;
    }
};
