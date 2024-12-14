#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;
bool v[maxn];
int n, pr;
vector<int> p;
void init() {
    v[1] = true;
    for (int i = 2; i < maxn; i++) {
        if (!v[i]) p.push_back(i);
        for (int j = 0; j < p.size() && i * p[j] < maxn; ++j) {
            v[i * p[j]] = true;
            if (i % p[j] == 0) break;
        }
    }
}
