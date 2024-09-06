#include<bits/stdc++.h>
using namespace std;
const int maxn=110;
int n, m;
int a[maxn][maxn];
int lx[maxn], ly[maxn], link[maxn];
bool vx[maxn], vy[maxn];
int dfs(int x)
{
    if(x==-1)return 0;
    vx[x] = 1;
    for (int i = 1; i <= n; i++)
    {
        if (!vy[i] && lx[x] + ly[i] == a[x][i])
        {
            vy[i] = 1;
            if (link[i] == -1 || dfs(link[i]))
            {
                link[i] = x;
                return 1;
            }
        }
    }
    return 0;
}
bool deal()
{
    memset(ly, 0, sizeof(ly));
    memset(lx, 0xf7, sizeof(lx));
    memset(link, -1, sizeof(link));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            lx[i] = max(lx[i], a[i][j]);
    }
    for(int i = 1; i <= n; i++)       
    {
        while(1)
        {
            memset(vx, 0, sizeof(vx));
            memset(vy, 0, sizeof(vy));
            if (dfs(i)) break;
            int delta = 0x7f7f7f7f;
            for (int j= 1; j <= n; j++)
            {
                if (vx[j] == 1)
                    for(int k = 1; k <= n; k++)
                        if (vy[k] == 0) delta = min(delta, lx[j]+ ly[k]- a[j][k]);    
            }
            if (delta == 0x7f7f7f7f)  return 0;
            for (int j= 1; j <= n; j++)
                if (vx[j] == 1) lx[j] -= delta;
            for(int k = 1; k <= n; k++)
                if (vy[k] == 1) ly[k] += delta;
        }
    }
    return 1;
}
int main()
{
       if  (deal() == 1) {
           int ans = 0;
           for(int i = 1; i <= n; i++)
           {
               ans += a[link[i]][i];
           }
           cout << ans <<'\n';//取最小就把所有边权取负再跑
       }
    return 0;
}