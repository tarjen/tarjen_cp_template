// 用givest 定源点汇点
// addedge一次加了正反两条边
// init 慎用
// S必须是0
// 输出方案注意是head开头
#include <bits/stdc++.h>
using namespace std;
const int N=2510,M=2510*10; 
class Maxflow{
private:
	int nedge=1,p[2*M],nex[2*M],head[N],c[2*M],cur[2*M];
    int dist[2*N];
    int S,T;
	void Addedge(int a,int b,int v){
		p[++nedge]=b;nex[nedge]=head[a];head[a]=nedge;
		c[nedge]=v;
	}
    bool bfs(){
		queue<int>q;
		for(int i=S;i<=T;i++)dist[i]=-1;
		dist[S]=0;q.push(S);
		while(!q.empty()){
			int now=q.front();q.pop();
			for(int k=head[now];k;k=nex[k])if(dist[p[k]]==-1&&c[k]>0){
				dist[p[k]]=dist[now]+1;
				q.push(p[k]);
			}
		}
		return dist[T]>-1;
	}
	int dfs(int x,int low){
		if(x==T)return low;
		if(low==0)return 0;
		int used=0;
		for(int &k=cur[x];k;k=nex[k])if(dist[p[k]]==dist[x]+1&&c[k]>0){
			int a=dfs(p[k],min(c[k],low-used));
			c[k]-=a;c[k^1]+=a;used+=a;
			if(low==used)break;
		}
		if(used==0)dist[x]=-1;
		return used;
	}
public:
	void init(int s,int t){
		for(int i=S;i<=T;i++)head[i]=0;
		S=s,T=t;
		nedge=1;
	}
    void addedge(int a,int b,int v){
        Addedge(a,b,v);
        Addedge(b,a,0);
	}
	int dinic(){
		int flow=0;
		while(bfs()){
			for(int i=S;i<=T;i++)cur[i]=head[i];
			flow+=dfs(S,1e9);
		}
		return flow;
	}
};