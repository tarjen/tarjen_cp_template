    vector<vector<int>> e1(n);
    int cnt = n;
    
    int now = 0;
    vector<int> dfn(n, -1), low(n);
    vector<int> stk;
    function<void(int)> tarjan = [&](int u) {
        stk.push_back(u);
        dfn[u] = low[u] = now++;
        for (auto v : ve[u]) {
            if (dfn[v] == -1) {
                tarjan(v);
                low[u] = min(low[u], low[v]);
                if (low[v] == dfn[u]) {
                    e1.push_back({});
                    int x;
                    do {
                        x = stk.back();
                        stk.pop_back();
                        e1[cnt].push_back(x);
                    } while (x != v);
                    e1[u].push_back(cnt);
                    ++cnt;
                }
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }
    };
    tarjan(0);