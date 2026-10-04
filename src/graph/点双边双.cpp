// 1base无向图；BCC b(n); link(u,v); build(); bcc为点双，ebcc为边双，均1base；孤立点单独成分量。
#include <bits/stdc++.h>
using namespace std;

struct BCC {
    int n,dfs_clock=0,bcc_cnt=0,ebcc_cnt=0;
    vector<pair<int,int>> edges;
    vector<vector<pair<int,int>>> ve;
    vector<int> dfn,low,iscut,bcc_edge,bccno;
    vector<char> bridge;
    vector<vector<int>> bcc,ebcc;
    vector<set<int>> vbccno;
    explicit BCC(int n): n(n),ve(n+1) {}
    // 支持重边，不接受自环；边编号从0开始。
    int link(int u,int v) {
        assert(u!=v);
        int id=edges.size(); edges.push_back({u,v});
        ve[u].push_back({v,id}); ve[v].push_back({u,id}); return id;
    }
    void build() {
        dfs_clock=bcc_cnt=ebcc_cnt=0;
        dfn.assign(n+1,0); low.assign(n+1,0); iscut.assign(n+1,0); bccno.assign(n+1,0);
        bridge.assign(edges.size(),0); vbccno.assign(n+1,{});
        bcc.assign(1,{}); bcc_edge.assign(1,0); ebcc.assign(1,{});
        vector<int> edge_stack;
        struct Frame { int u,parent_edge,next,child; };
        vector<Frame> stack;
        auto component=[&](vector<int> nodes,int edge_count) {
            sort(nodes.begin(),nodes.end()); nodes.erase(unique(nodes.begin(),nodes.end()),nodes.end());
            bcc.push_back(nodes); bcc_edge.push_back(edge_count); ++bcc_cnt;
            for(int v:nodes) vbccno[v].insert(bcc_cnt);
        };
        for(int root=1;root<=n;root++) if(!dfn[root]) {
            if(ve[root].empty()) { dfn[root]=low[root]=++dfs_clock; component({root},0); continue; }
            dfn[root]=low[root]=++dfs_clock; stack.push_back({root,-1,0,0});
            while(!stack.empty()) {
                auto& f=stack.back(); int u=f.u;
                if(f.next<(int)ve[u].size()) {
                    auto [v,id]=ve[u][f.next++];
                    if(id==f.parent_edge) continue;
                    if(!dfn[v]) {
                        f.child++; edge_stack.push_back(id);
                        dfn[v]=low[v]=++dfs_clock; stack.push_back({v,id,0,0});
                    } else if(dfn[v]<dfn[u]) low[u]=min(low[u],dfn[v]),edge_stack.push_back(id);
                } else {
                    int parent_edge=f.parent_edge,child=f.child; stack.pop_back();
                    if(parent_edge==-1) iscut[u]=child>1;
                    else {
                        int p=stack.back().u;
                        low[p]=min(low[p],low[u]);
                        bridge[parent_edge]=low[u]>dfn[p];
                        if(low[u]>=dfn[p]) {
                            iscut[p]=1; vector<int> nodes; int count=0;
                            while(true) {
                                int id=edge_stack.back(); edge_stack.pop_back(); count++;
                                nodes.push_back(edges[id].first); nodes.push_back(edges[id].second);
                                if(id==parent_edge) break;
                            }
                            component(nodes,count);
                        }
                    }
                }
            }
        }
        for(int root=1;root<=n;root++) if(!bccno[root]) {
            ++ebcc_cnt; ebcc.push_back({}); vector<int> todo{root}; bccno[root]=ebcc_cnt;
            while(!todo.empty()) {
                int u=todo.back(); todo.pop_back(); ebcc.back().push_back(u);
                for(auto [v,id]:ve[u]) if(!bridge[id]&&!bccno[v]) bccno[v]=ebcc_cnt,todo.push_back(v);
            }
        }
    }
};
