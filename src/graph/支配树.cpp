// 1base有向图；DominatorTree dt(n); add_edge(); solve(root); up为直接支配点，根和不可达点为0。
#include <bits/stdc++.h>
using namespace std;
struct DominatorTree {
    int n,cs=0;
    vector<vector<int>> E,RE,rdom;
    vector<int> S,RS,par,val,sdom,rp,dom,up;
    explicit DominatorTree(int n): n(n),E(n+1),RE(n+1),rdom(n+1),S(n+1),RS(n+1),
        par(n+1),val(n+1),sdom(n+1),rp(n+1),dom(n+1),up(n+1) {}
    DominatorTree(const vector<vector<int>>& graph,int root): DominatorTree((int)graph.size()-1) { E=graph; solve(root); }
    void reset_work() {
        cs=0;
        for(int i=0;i<=n;i++) {
            S[i]=RS[i]=par[i]=val[i]=sdom[i]=rp[i]=dom[i]=up[i]=0;
            RE[i].clear(); rdom[i].clear();
        }
    }
	void add_edge(int x, int y) { E[x].push_back(y); }
	void Union(int x, int y) { par[x] = y; }
	int Find(int x, int c = 0) {
		if(par[x] == x) return c ? -1 : x;
		int p = Find(par[x], 1);
		if(p == -1) return c ? par[x] : val[x];
		if(sdom[val[x]] > sdom[val[par[x]]]) val[x] = val[par[x]];
		par[x] = p;
		return c ? p : val[x];
	}
	void dfs(int x) {
		RS[ S[x] = ++cs ] = x;
		par[cs] = sdom[cs] = val[cs] = cs;
		for(int e : E[x]) {
			if(S[e] == 0) dfs(e), rp[S[e]] = S[x];
			RE[S[e]].push_back(S[x]);
		}
	}
	int solve(int s) {//s是起点
		reset_work();
		dfs(s);
		for(int i=cs;i;i--) {
			for(int e : RE[i]) sdom[i] = min(sdom[i], sdom[Find(e)]);
			if(i > 1) rdom[sdom[i]].push_back(i);
			for(int e : rdom[i]) {
				int p = Find(e);
				if(sdom[p] == i) dom[e] = i;
				else dom[e] = p;
			}
			if(i > 1) Union(i, rp[i]);
		}
		for(int i=2;i<=cs;i++) if(sdom[i] != dom[i]) dom[i] = dom[dom[i]];
		for(int i=2;i<=cs;i++) up[RS[i]] = RS[dom[i]];
		return cs;
	}
};
