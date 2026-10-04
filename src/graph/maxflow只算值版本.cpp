// dinic mf(n); mf.addedge(u,v,cap); mf.maxflow(s,t);
#include <bits/stdc++.h>
using namespace std;

struct dinic {
    struct E { int to; long long cap; };
    int n,S,T;
    vector<E> edges;
    vector<vector<int>> g;
    vector<int> dis,now;
    explicit dinic(int n,int s=-1,int t=-1): n(n),S(s),T(t),g(n+1),dis(n+1),now(n+1) {}
    // 编号允许0..n；返回正向边编号，原容量减剩余容量即该边流量。
    int addedge(int u,int v,long long w) {
        int id=edges.size();
        g[u].push_back(id); edges.push_back({v,w});
        g[v].push_back(id+1); edges.push_back({u,0});
        return id;
    }
    bool bfs(int s,int t) {
        fill(dis.begin(),dis.end(),-1);
        queue<int> q; q.push(s); dis[s]=0;
        while(!q.empty()) {
            int u=q.front(); q.pop();
            for(int id:g[u]) if(edges[id].cap>0&&dis[edges[id].to]==-1) {
                dis[edges[id].to]=dis[u]+1; q.push(edges[id].to);
            }
        }
        return dis[t]!=-1;
    }
    long long dfs(int u,int t,long long f) {
        if(u==t) return f;
        for(int& i=now[u];i<(int)g[u].size();i++) {
            int id=g[u][i],v=edges[id].to;
            if(edges[id].cap>0&&dis[v]==dis[u]+1) {
                long long d=dfs(v,t,min(f,edges[id].cap));
                if(d) { edges[id].cap-=d; edges[id^1].cap+=d; return d; }
            }
        }
        return 0;
    }
    // 计算当前残量网络上新增的最大流；重复调用不会恢复原容量。
    long long maxflow(int s,int t) {
        assert(s!=t);
        long long flow=0,d;
        while(bfs(s,t)) {
            fill(now.begin(),now.end(),0);
            while((d=dfs(s,t,numeric_limits<long long>::max()/4))) flow+=d;
        }
        return flow;
    }
    long long maxflow() { return maxflow(S,T); }
};
