#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;
const int inf =2e9; 
int n, siz[maxn], dist[maxn], vis[maxn],maxx[maxn];
vector<pair<int, int>> ve[maxn];

void add_edge(int x, int y, int z)
{
    ve[x].emplace_back(y, z);
}

void calcsiz(int x, int fa, int sum, int &rt)
{
    siz[x] = 1;
    maxx[x] = 0;
    for (auto &[to, len] : ve[x])
        if (to != fa && !vis[to])
        {
            calcsiz(to, x, sum, rt);
            maxx[x] = max(maxx[x], siz[to]);
            siz[x] += siz[to];
        }
    maxx[x] = max(maxx[x], sum - siz[x]);
    if (maxx[x] < maxx[rt])
        rt = x;
}


void calcdist(int x, int fa)
{
    for (auto &[to, len] : ve[x])
        if (to != fa && !vis[to])
        {
            dist[to] = dist[x] + len, calcdist(to, x);
        }
}
void dfs(int x, int fa)
{
    vis[x] = true;
    for (auto &[to, len] : ve[x])
        if (to != fa && !vis[to])
        {
            dist[to] = len;
            calcdist(to, x);
        }


    for (auto &[to, len] : ve[x])
        if (to != fa && !vis[to])
        {
            int sum = siz[to];
            int rt = 0;
            calcsiz(to, x, sum, rt);
            calcsiz(rt, -1, sum, rt);
            dfs(rt, x);
        }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n ;
    for (int i = 1; i < n; i++)
    {
        int a, b,c;
        cin >> a >> b>>c, add_edge(a, b, c), add_edge(b, a, c);
    }
    int rt = 0;
    maxx[rt] = inf;
    int sum = n;
    calcsiz(1, -1, sum, rt);
    calcsiz(rt, -1, sum, rt);
    dfs(rt, -1);
    return 0;
}
