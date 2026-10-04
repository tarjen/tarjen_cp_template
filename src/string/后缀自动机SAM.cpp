// 小写字母；SAM sam(s)完成构建和出现次数统计；ep/siz按状态编号访问。
#include <bits/stdc++.h>
using namespace std;
struct SAM {
    struct Node {
        int tr[26];
        int len, fa;
        Node() { memset(tr, 0, sizeof(tr)); len = fa = 0; }
    };
    vector<Node> ep;
    int last, tot, n;
    char base;
    vector<vector<int>> edg;
    vector<int> siz;
    explicit SAM(int max_length=0) { init(max_length); }
    explicit SAM(const string& s) { build(s); }
    void init(int length) {
        last=tot=1; n=0; base='a';
        ep.assign(2,Node()); siz.assign(2,0); edg.assign(2,{});
        ep.reserve(2*length+2); siz.reserve(2*length+2);
    }
    int newnode() { ep.emplace_back(); siz.push_back(0); return ++tot; }
    void insert(char x) {
        int c = x - base;
        assert(0<=c&&c<26); n++;
        int p = last;
        int np = last = newnode();
        siz[np] = 1;
        ep[np].len = ep[p].len + 1;
        for (; p && !ep[p].tr[c]; p = ep[p].fa)
            ep[p].tr[c] = np;
        if (!p) ep[np].fa = 1;
        else {
            int q = ep[p].tr[c];
            if (ep[q].len == ep[p].len + 1) ep[np].fa = q;
            else {
                int nq = newnode();
                ep[nq] = ep[q];
                ep[nq].len = ep[p].len + 1;
                ep[q].fa = ep[np].fa = nq;
                for (; p && ep[p].tr[c] == q; p = ep[p].fa)
                    ep[p].tr[c] = nq;
            }
        }
    }
    void construct() {
        edg.assign(tot+1,{});
        for (int i = 2; i <= tot; i++) {
            edg[ep[i].fa].push_back(i);
        }
    }
    void dfs(int u) {
        vector<int> order{u};
        for(int i=0;i<(int)order.size();i++)
            for(int v:edg[order[i]]) order.push_back(v);
        for(int i=(int)order.size()-1;i>0;i--) siz[ep[order[i]].fa]+=siz[order[i]];
    }
    void build(const string& s) {
        init(s.size());
        for (int i = 0; i < (int)s.size(); i++) {
            insert(s[i]);
        }
        construct();
        dfs(1);
    }

};
