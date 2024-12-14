#include <bits/stdc++.h>
using namespace std;
struct PairLCS {
    vector<vector<int>> ih, iv;
    int n = 0, m = 0;
    PairLCS(string s, string t) : n(s.size()), m(t.size()) {
        ih = iv = vector<vector<int>>(n + 1, vector<int>(m + 1));
        iota(ih[0].begin(), ih[0].end(), 0);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s[i - 1] == t[j - 1]) {
                    ih[i][j] = iv[i][j - 1];
                    iv[i][j] = ih[i - 1][j];
                } else {
                    ih[i][j] = std::max(ih[i - 1][j], iv[i][j - 1]);
                    iv[i][j] = std::min(ih[i - 1][j], iv[i][j - 1]);
                }
            }
        }
    }
    int query(int a, int b, int c) const {
        int res = 0;
        for (int i = b + 1; i <= c; i++) res += ih[a][i] <= b;
        return res;
    }  // s[0,a) t[b,c)
};

int cas;

void solution() {
    int q;
    std::string s, t;
    std::cin >> q >> s >> t;

    // int n = s.size(), m = t.size();
    PairLCS solver(s, t);

    for (int _ = 0; _ < q; _++) {
        int a, b, c;
        std::cin >> a >> b >> c;
        std::cout << solver.query(a, b, c) << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T = 1;
    // std::cin >> T;
    for (cas = 1; cas <= T; cas++) solution();

    return 0;
}