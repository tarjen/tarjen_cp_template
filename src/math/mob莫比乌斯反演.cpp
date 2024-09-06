#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int pr[maxn],tot,mul[maxn],phi[maxn];
bool vis[maxn];
void init(int n)
{
    mul[1]=phi[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(!vis[i])
        {
            mul[i]=-1;
            pr[++tot]=i;
            phi[i]=i-1;
        }
        for(int j=1;j<=tot && (long long)pr[j]*i<=n;j++)
        {
            int num=pr[j]*i;
            vis[num]=1;
            mul[num]=-mul[i];
            phi[num]=phi[i]*phi[pr[j]];
            if(i%pr[j]==0)
            {
                phi[num]=pr[j]*phi[i];
                mul[num]=0;
                break;
            }
        }
    }
}