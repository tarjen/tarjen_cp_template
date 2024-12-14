// 带边权的虚树
// ve2是虚树,ve是原树
// 注意使用时mlen的意义需要修改 getlen和dfs预处理的时候都要修改
// 用的时候就addintoxs(x)丢进去，每次init就全部删除
// add是加原边，ADD不用管它
// solve 里面是必备的几步，不能去除
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 1e5 + 10;
const int inf = 1e18;
int n, m;
struct XS {
    struct kkk {
        int to, len;
    };
    int dep[maxn], f[maxn][21], id[maxn];
    int mlen[maxn][21], ans[maxn][21];
    int state[maxn];
    int sum[maxn], all;
    vector<kkk> ve[maxn], ve2[maxn];
    int now;  // 统计dfs序
    void dfs(int u, int fa) {
        id[u] = now++;
        dep[u] = dep[fa] + 1;
        for (int i = 0; i <= 19; i++) {
            f[u][i + 1] = f[f[u][i]][i];
            mlen[u][i + 1] = mlen[f[u][i]][i] + mlen[u][i];
        }
        for (auto v : ve[u]) {
            if (v.to == fa) continue;
            f[v.to][0] = u;
            mlen[v.to][0] = v.len;
            dfs(v.to, u);
        }
    }
    int lca(int x, int y) {
        if (dep[x] < dep[y]) swap(x, y);
        for (int i = 20; i >= 0; i--) {
            if (dep[f[x][i]] >= dep[y]) x = f[x][i];
            if (x == y) return x;
        }
        for (int i = 20; i >= 0; i--)
            if (f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
        return f[x][0];
    }
    int getlen(int x, int y) {
        if (x == y) return 0;
        if (dep[x] < dep[y]) swap(x, y);
        int res = 0;
        for (int i = 20; i >= 0; i--) {
            if (dep[f[x][i]] >= dep[y]) {
                res = res + mlen[x][i];
                x = f[x][i];
            }
            if (x == y) return res;
        }
        return inf;
    }
    void add(int x, int y, int len) {  // 加边
        ve[x].push_back({y, len});
        ve[y].push_back({x, len});
    }
    void ADD(int x, int y, int len) {  // 虚树加边
        ve2[x].push_back({y, len});
        ve2[y].push_back({x, len});
    }
    vector<int> vis;  // b vis这两个用来初始化
    bool b[maxn];
    vector<int> v1;  // 用来表示加入虚树的点
    int sta[maxn];
    void init()  // 删除虚树
    {
        for (auto it : vis) {
            ve2[it].clear();
            b[it] = false;
            sum[it] = 0;
        }
        vis.clear();
        v1.clear();
    }
    void makexs() {
        sort(v1.begin(), v1.end(), [&](int x, int y) { return id[x] < id[y]; });
        sta[0] = 0;
        int top = 1;
        sta[top] = 1;
        vis.push_back(1);
        for (auto it : v1) {
            int l = lca(it, sta[top]);
            if (l != sta[top]) {
                while (id[l] < id[sta[top - 1]]) {
                    int w = getlen(sta[top], sta[top - 1]);
                    ADD(sta[top - 1], sta[top], w);
                    vis.push_back(sta[top--]);
                }
                if (id[l] > id[sta[top - 1]]) {
                    int w = getlen(sta[top], l);
                    ADD(l, sta[top], w);
                    vis.push_back(sta[top]);
                    sta[top] = l;
                } else {
                    int w = getlen(sta[top], sta[top - 1]);
                    ADD(sta[top], sta[top - 1], w);
                    vis.push_back(sta[top--]);
                }
            }
            sta[++top] = it;
        }
        for (int i = 1; i < top; i++) {
            int w = getlen(sta[i], sta[i + 1]);
            ADD(sta[i], sta[i + 1], w);
            vis.push_back(sta[i + 1]);
        }
    }
    void addintoxs(int x) {
        if (x == 1) return;
        v1.push_back(x);
        b[x] = true;
    }
    void solve() {
        now = 0;
        dfs(1, 0);
        for (int i = 1; i <= n; i++) {
            makexs();
            init();
        }
    }
};
XS xs;