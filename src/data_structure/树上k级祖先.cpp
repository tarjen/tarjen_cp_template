#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5+10;
int n,m,u,v,cnt,f[20][maxn],w[maxn],h[maxn];
int top[maxn],dep[maxn],id[maxn],U[maxn],D[maxn];
vector<int>ve[maxn];
void dfs1(int x){
	for(int i=1;i<=19;++i)f[i][x]=f[i-1][f[i-1][x]];
	for(auto it:ve[x]){
		dep[it]=h[it]=dep[x]+1;
		dfs1(it);
		h[x]=max(h[x],h[it]);
		if(h[it]>h[w[x]])w[x]=it;
	}
}
void dfs2(int x,int p){
	id[x]=++cnt;
	D[cnt]=x;
	U[cnt]=p;
	if(w[x]){top[w[x]]=top[x];dfs2(w[x],f[0][p]);}
	for(auto it:ve[x])
		if(it!=w[x]){
			top[it]=it;
			dfs2(it,it);
		}
}
int rt;
int ask(int x,int k){
	if(!k)return x;
	x=f[__lg(k)][x];k-=(1<<__lg(k));
	k-=dep[x]-dep[top[x]];x=top[x];
	if(k>=0) return U[id[x]+k];
	return D[id[x]-k];
}
int main(){
	for(int i=1;i<=n;++i){
        cin>>f[0][i];
		if(!f[0][i])rt=i;
		else ve[f[0][i]].push_back(i);
	}
	dep[rt]=1;dfs1(rt);
	top[rt]=rt;dfs2(rt,rt);
	return 0;
}