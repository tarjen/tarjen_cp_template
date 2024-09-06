#include<bits/stdc++.h>
using namespace std;
const int M=2333,N=666;
struct edge
{
	int nxt,to;
}e[M<<1];
int head[N],tot=1;
int cut[M<<1];
void add(int u,int v)
{
	e[++tot]=(edge){head[u],v},head[u]=tot;
	e[++tot]=(edge){head[v],u},head[v]=tot;
}
vector<int> st;
void dfs(int u)//欧拉回路
{
    for(int i=head[u];i!=0;i=e[i].nxt)
    {
        if(cut[i]) continue;
        int v=e[i].to;
        cut[i]=cut[i^1]=1;
        dfs(v);
    }
    st.push(u);
}
int main()
{
	
    
	return 0;
}
