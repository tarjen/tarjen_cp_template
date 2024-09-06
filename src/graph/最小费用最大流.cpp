#include <bits/stdc++.h>
using namespace std;
const int N=1e4,M=1e6;
struct SSP {
    int cnt = 1, hd[N], nxt[M << 1], to[M << 1], limit[M << 1], cst[M << 1];
    void init(){
        memset(hd,0,sizeof(hd));
        cnt=1;
    }
    // w limit c cost
    void add(int u, int v, int w, int c) {
        nxt[++cnt] = hd[u], hd[u] = cnt, to[cnt] = v, limit[cnt] = w, cst[cnt] = c;
        nxt[++cnt] = hd[v], hd[v] = cnt, to[cnt] = u, limit[cnt] = 0, cst[cnt] = -c;
    }
 
    int fr[N], fl[N], in[N], dis[N];
 
    pair<int, int> min_cost(int s, int t) {
        int flow = 0, cost = 0;
        while (true) { // SPFA
            queue<int> q;
            memset(dis, 0x3f, sizeof(dis));
            memset(in, 0, sizeof(in));
            fl[s] = 1e9, dis[s] = 0, q.push(s);
            while (!q.empty()) {
                int cur = q.front();
                q.pop(), in[cur] = 0;
                for (int i = hd[cur]; i; i = nxt[i]) {
                    int it = to[i], d = dis[cur] + cst[i];
                    if (limit[i] && d < dis[it]) {
                        fl[it] = min(limit[i], fl[cur]), fr[it] = i, dis[it] = d;
                        if (!in[it]) in[it] = 1, q.push(it);
                    }
                }
            }
            if (dis[t] > 1e9) return {flow, cost};//改成>0就是可行流
            flow += fl[t], cost += dis[t] * fl[t];
            for (int u = t; u != s; u = to[fr[u] ^ 1]) limit[fr[u]] -= fl[t], limit[fr[u] ^ 1] += fl[t];
        }
    }
} Sol;