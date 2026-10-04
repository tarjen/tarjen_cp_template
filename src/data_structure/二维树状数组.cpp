// 1base；Treearray2D tr(n,m); update(x1,y1,x2,y2,k); query(x1,y1,x2,y2);
#include <bits/stdc++.h>
using namespace std;
struct treearray{
    int n,m;
    vector<vector<long long>> mkp1,mkp2,mkp3,mkp4;
    treearray(int n,int m): n(n),m(m),mkp1(n+1,vector<long long>(m+1)),
        mkp2(mkp1),mkp3(mkp1),mkp4(mkp1) {}
    inline int lowbit(int x)
    {
        return x&(-x);
    }
    inline void Update(int x,int y,long long k)
    {
        assert(x>=1&&y>=1);
        for(int i=x;i<=n;i+=lowbit(i))
        {
            for(int j=y;j<=m;j+=lowbit(j))
            {
                mkp1[i][j]+=k;
                mkp2[i][j]+=k*x;
                mkp3[i][j]+=k*y;
                mkp4[i][j]+=k*x*y;
            }
        }
    }
    inline void update(int a,int b,int x,int y,long long k)
    {
        Update(a,b,k);
        Update(a,y+1,-k);
        Update(x+1,b,-k);
        Update(x+1,y+1,k);
    }
    inline long long Query(int x,int y)
    {
        long long ans=0;
        for(int i=x;i>=1;i-=lowbit(i))
        {
            for(int j=y;j>=1;j-=lowbit(j))
            {
                ans+=1LL*(x+1)*(y+1)*mkp1[i][j]
                -(y+1)*mkp2[i][j]-(x+1)*mkp3[i][j]+mkp4[i][j];
            }
        }
        return ans;
    }
    inline long long query(int a,int b,int x,int y)
    {
        return Query(x,y)+Query(a-1,b-1)-Query(x,b-1)-Query(a-1,y);
    }
};
using Treearray2D = treearray;
