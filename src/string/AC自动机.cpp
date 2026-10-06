// 小写字母；AC ac; insert(string) -> build() -> query(string);
// 不需要清空查询状态。
#include <bits/stdc++.h>
using namespace std;

struct AC {
    vector<array<int, 26>> trie;
    vector<int> e, fail, old;
    int tot = 0;
    bool built = false;
    explicit AC(int reserve_nodes = 0) : trie(1), e(1), fail(1), old(1) {
        trie.reserve(max(1, reserve_nodes));
    }
    int insert(const string& s) {
        assert(!built && !s.empty());
        int x = 0;
        for (char ch : s) {
            int c = ch - 'a';
            assert(0 <= c && c < 26);
            if (!trie[x][c]) {
                trie.push_back({});
                e.push_back(0);
                fail.push_back(0);
                old.push_back(0);
                trie[x][c] = ++tot;
            }
            x = trie[x][c];
        }
        e[x]++;
        return x;
    }
    void insert(const char* t) { insert(string(t + 1)); }
    void build() {
        if (built) return;
        queue<int> q;
        for (int c = 0; c < 26; c++)
            if (trie[0][c]) q.push(trie[0][c]);
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            old[x] = e[fail[x]] ? fail[x] : old[fail[x]];
            for (int c = 0; c < 26; c++) {
                int v = trie[x][c];
                if (v)
                    fail[v] = trie[fail[x]][c], q.push(v);
                else
                    trie[x][c] = trie[fail[x]][c];
            }
        }
        built = true;
    }
    // 统计出现过的模式串数量，重复插入的模式分别计数；每次查询独立。
    int query(const string& text) const {
        assert(built);
        vector<char> seen(tot + 1);
        int x = 0, res = 0;
        for (char ch : text) {
            int c = ch - 'a';
            assert(0 <= c && c < 26);
            x = trie[x][c];
            for (int j = x; j && !seen[j]; j = old[j])
                res += e[j], seen[j] = true;
        }
        return res;
    }
    int query(const char* t) const { return query(string(t + 1)); }
};
