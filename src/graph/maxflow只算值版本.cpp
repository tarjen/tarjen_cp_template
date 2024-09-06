struct dinic{
    struct E{
        int to,cap,inv;
    };
    vector <E> g[N];
    int dis[N],now[N];
    void addedge(int u,int v,int w){
        g[u].push_back({v,w,(int)g[v].size()});
        g[v].push_back({u,0,(int)g[u].size()-1});
    }
    void bfs(int st){
        queue<int>q;
        memset(dis,0,sizeof dis);
        q.push(st);dis[st]=1;
        while(q.size()){
            int u=q.front();q.pop();
            for(auto &[v,w,inv]:g[u]){
                if(w&&!dis[v]){
                    dis[v]=dis[u]+1;
                    q.push(v);
                }
            }
        }
    }
    int dfs(int u,int t,int flow){
        if(u==t)return flow;
        for(int &i=now[u],sz=g[u].size(),d;i<sz;i++){
            auto &[v,w,inv]=g[u][i];
            if(w&&dis[v]>dis[u]){
                d=dfs(v,t,min(flow,w));
                if(d>0){
                    w-=d;
                    g[v][inv].cap+=d;
                    return d;
                }
            }
        }
        return 0;
    }
    int maxflow(int st,int ed){
        for(int flow=0,res;;){
            bfs(st);
            if(!dis[ed])return flow;
            memset(now,0,sizeof now);
            while((res=dfs(st,ed,inf))>0){
                flow+=res;
            }
        }
    }
};