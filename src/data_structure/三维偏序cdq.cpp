// Dominance3D cdq(points);
// cnt[k]为被恰好k个其他点三坐标均<=的点数；输入0base，重复点分别计数。
#include <bits/stdc++.h>
using namespace std;
struct Treearray {
    vector<int> c;
    int n = 0;
    void set_n(int _n) {
        n = _n;
        c.assign(n + 1, 0);
    }
    int lowbit(int x) { return x & (-x); }
    void update(int i, int k) {  // 在i位置加上k
        while (i <= n) {
            c[i] += k;
            i += lowbit(i);
        }
    }
    int getsum(int i) {  // 求A[1 - i]的和
        int res = 0;
        while (i > 0) {
            res += c[i];
            i -= lowbit(i);
        }
        return res;
    }
};
struct Dominance3D {
    Treearray tri;
    vector<int> a, b, c, ans, id, cnt, t;
    explicit Dominance3D(vector<tuple<int, int, int>> v) : cnt(v.size()) {
        int n = v.size();
        if (!n) return;
        vector<int> zs;
        for (auto [x, y, z] : v) zs.push_back(z);
        sort(zs.begin(), zs.end());
        zs.erase(unique(zs.begin(), zs.end()), zs.end());
        tri.set_n(zs.size());
        sort(v.begin(), v.end());
        a.assign(n + 1, 0);
        b = a;
        c = a;
        ans = a;
        id = a;
        t = a;
        int groups = 0;
        for (int i = 0; i < n; i++) {
            int j = i;
            while (j + 1 < n && v[j + 1] == v[i]) j++;
            ++groups;
            a[groups] = get<0>(v[i]);
            b[groups] = get<1>(v[i]);
            c[groups] = lower_bound(zs.begin(), zs.end(), get<2>(v[i])) -
                        zs.begin() + 1;
            t[groups] = j - i + 1;
            id[groups] = groups;
            i = j;
        }
        subdiv(1, groups);
        for (int i = 1; i <= groups; i++) cnt[ans[i] + t[i] - 1] += t[i];
    }
    void subdiv(int l, int r) {
        if (l == r) return;
        int mid = (l + r) / 2;
        subdiv(l, mid);
        subdiv(mid + 1, r);
        sort(id.begin() + l, id.begin() + mid + 1, [&](int x, int y) {
            if (b[x] == b[y]) return c[x] < c[y];
            return b[x] < b[y];
        });
        sort(id.begin() + mid + 1, id.begin() + r + 1, [&](int x, int y) {
            if (b[x] == b[y]) return c[x] < c[y];
            return b[x] < b[y];
        });

        // for(int i=l;i<=r;i++)cout<<id[i]<<" \n"[i==r];
        assert(tri.getsum(tri.n) == 0);
        for (int i = l, j = mid + 1; i <= mid || j <= r;) {
            if (j != r + 1 && (i == mid + 1 || b[id[i]] > b[id[j]])) {
                // cout<<"id="<<id[j]<<" +"<<tri.getsum(c[id[j]])<<"\n";
                ans[id[j]] += tri.getsum(c[id[j]]);
                j++;
            } else {
                tri.update(c[id[i]], t[id[i]]);
                i++;
            }
        }
        for (int i = l; i <= mid; i++) tri.update(c[id[i]], -t[id[i]]);
    }
};
