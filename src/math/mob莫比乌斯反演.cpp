// MobiusSieve sieve(n); mul为莫比乌斯函数，phi为欧拉函数，pr质数列表保留1base。
#include <bits/stdc++.h>
using namespace std;
struct MobiusSieve {
    int n,tot=0;
    vector<int> pr,mul,phi;
    vector<char> vis;
    explicit MobiusSieve(int n): n(n),pr(1,0),mul(n+1),phi(n+1),vis(n+1) {
    if(n==0) return;
    mul[1]=phi[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(!vis[i])
        {
            mul[i]=-1;
            pr.push_back(i); ++tot;
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
};
