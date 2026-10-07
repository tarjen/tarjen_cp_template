// 用法：
// DynamicSegmentTree tr(1, 1000000000);  // 数值域闭区间，初值 0。
// tr.update(5, 3);
// tr.update(8, 2);  // 单点加。
// ll sum = tr.query(1, 10);  // 区间和为 5。
// int part = tr.split(5, 5);  // 从 tr.root 中取出 [5,5]，返回独立根编号。
// tr.root = tr.merge(tr.root, part);  // 同一节点池内合并，消耗旧根。
// 多根查询用 query_root(root,l,r)；不同对象的根不能交叉使用。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct DynamicSegmentTree {
    struct Node {
        int ls = 0, rs = 0;
        ll sum = 0;
    };
    int lo, hi, root = 0;
    vector<Node> a{Node()};
    DynamicSegmentTree(int lo, int hi) : lo(lo), hi(hi) { assert(lo <= hi); }
    explicit DynamicSegmentTree(int n) : DynamicSegmentTree(1, n) {}
    int newnode() {
        a.emplace_back();
        return (int)a.size() - 1;
    }
    // 多棵树须属于同一对象的节点池；返回根编号，递归期间不保存vector元素引用。
    int update(int p, int L, int R, int x, ll delta) {
        if (!p) p = newnode();
        if (L == R) {
            a[p].sum += delta;
            return p;
        }
        int mid = L + (int)(((ll)R - L) / 2);
        if (x <= mid)
            a[p].ls = update(a[p].ls, L, mid, x, delta);
        else
            a[p].rs = update(a[p].rs, mid + 1, R, x, delta);
        a[p].sum = a[a[p].ls].sum + a[a[p].rs].sum;
        return p;
    }
    void update(int x, ll delta) {
        assert(lo <= x && x <= hi);
        root = update(root, lo, hi, x, delta);
    }
    int update_root(int p, int x, ll delta) {
        assert(lo <= x && x <= hi);
        return update(p, lo, hi, x, delta);
    }
    ll query(int p, int L, int R, int l, int r) const {
        if (!p || r < L || R < l || l > r) return 0;
        if (l <= L && R <= r) return a[p].sum;
        int mid = L + (int)(((ll)R - L) / 2);
        return query(a[p].ls, L, mid, l, r) + query(a[p].rs, mid + 1, R, l, r);
    }
    ll query(int l, int r) const { return query(root, lo, hi, l, r); }
    ll query_root(int p, int l, int r) const {
        return query(p, lo, hi, l, r);
    }
    // 合并会消耗两棵树；合并后的根不可再与旧根同时作为独立树使用。
    int merge(int p, int q, int L, int R) {
        if (!p || !q) return p | q;
        if (L == R) {
            a[p].sum += a[q].sum;
            return p;
        }
        int mid = L + (int)(((ll)R - L) / 2);
        a[p].ls = merge(a[p].ls, a[q].ls, L, mid);
        a[p].rs = merge(a[p].rs, a[q].rs, mid + 1, R);
        a[p].sum = a[a[p].ls].sum + a[a[p].rs].sum;
        return p;
    }
    int merge(int p, int q) { return merge(p, q, lo, hi); }
    // 将[l,r]分离到新树，返回{剩余根,分离根}。
    pair<int, int> split(int p, int L, int R, int l, int r) {
        if (!p || r < L || R < l || l > r) return {p, 0};
        if (l <= L && R <= r) return {0, p};
        int q = newnode(), mid = L + (int)(((ll)R - L) / 2);
        auto left = split(a[p].ls, L, mid, l, r);
        auto right = split(a[p].rs, mid + 1, R, l, r);
        a[p].ls = left.first;
        a[q].ls = left.second;
        a[p].rs = right.first;
        a[q].rs = right.second;
        a[p].sum = a[a[p].ls].sum + a[a[p].rs].sum;
        a[q].sum = a[a[q].ls].sum + a[a[q].rs].sum;
        return {p, q};
    }
    pair<int, int> split_root(int p, int l, int r) {
        return split(p, lo, hi, l, r);
    }
    int split(int l, int r) {
        auto result = split(root, lo, hi, l, r);
        root = result.first;
        return result.second;
    }
    // 原query1：非负计数下，找最小x使前缀和+x>up；不存在返回nullopt。
    optional<int> query1(ll& prefix, ll up, int p, int L,
                         int R) const {
        if (prefix + a[p].sum + R <= up) {
            prefix += a[p].sum;
            return {};
        }
        if (L == R) return L;
        int mid = L + (int)(((ll)R - L) / 2);
        auto result = query1(prefix, up, a[p].ls, L, mid);
        return result ? result : query1(prefix, up, a[p].rs, mid + 1, R);
    }
    optional<int> query1(ll up) const {
        ll prefix = 0;
        return query1(prefix, up, root, lo, hi);
    }
};
