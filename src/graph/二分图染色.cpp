#include <bits/stdc++.h>
using namespace std;
const int maxn=1010;
int n,m;
vector<int>ve[maxn];
int col[maxn][maxn],ans[maxn*2];
void dfs(int x,int y,int c1,int c2)
{
    if(col[y][c1]){
        dfs(y,col[y][c1],c2,c1);
        col[x][c1]=y;
        col[y][c1]=x;
    }
    else {
        col[x][c1]=y;
        col[y][c1]=x;
        col[y][c2]=0;
    }
}
map<pair<int,int>,int>ma;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m;
    int anss=0;
    for(int i=1;i<=m;i++){
        int x,y;
        cin>>x>>y;
        ve[x].push_back(y);
        ma[{x,y}]=i;
        int c1=1,c2=1;
        while(col[x][c1])c1++;
        while(col[y][c2])c2++;
        anss=max({c1,c2,anss});
        if(c1>c2){
            swap(x,y);swap(c1,c2);
        }
        if(c1==c2){
            col[x][c1]=y;
            col[y][c1]=x;
        }
        else{
            dfs(x,y,c1,c2);
        }
    }
    cout<<anss<<"\n";
    for(int i=1;i<=n;i++){
        for(int j=1;j<=anss;j++)if(col[i][j])ans[ma[{i,col[i][j]}]]=j;
    }
    for(int i=1;i<=m;i++)cout<<ans[i]<<"\n";
    return 0;
}