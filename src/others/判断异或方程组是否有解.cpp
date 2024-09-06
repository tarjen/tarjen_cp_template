const int maxn=1e2+5;
//每个方程组一定是xi1^xi2^xi3...=1/0的形式
bitset<maxn>b[maxn];//1表示这个方程组存在Xi 比如x3^x5=1就应该是3 和5的地方上是1
//b[n+1]存方程右边等于0/1
int sum[maxn];
bool check(int x)
{
    for(int i=1;i<=n;i++)if(b[x][i])return true;
    return !b[x][n+1];
}
bool solve()
{
    for(int i=1,p=1;i<=n;i++,p++)
    {
        if(!b[p][i])
        {
            int pos=0;
            for(int j=p+1; j<=n; j++)
                if(b[j][i])
                {
                    pos=j;
                    break;
                }
            if(pos)swap(b[p],b[pos]);
        }
        int flag=b[p][i];
        for(int j=p+1; j<=n; j++) if(b[j][i]) b[j]^=b[p],flag=1;
        if(!flag) p--;
    }
    for(int i=1; i<=n; i++) if(!check(i)) return false;
    return true;
}