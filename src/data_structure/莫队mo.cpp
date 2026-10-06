// 用法：
// vector<int> a = {1, 2, 3};
// Mo tr(a.size());  // 查询位置 0base，闭区间。
// tr.add_query(0, 1);
// tr.add_query(1, 2);
// ll sum = 0;
// auto ans = tr.solve([&] { sum = 0; }, [&](int i) { sum += a[i]; },
//                     [&](int i) { sum -= a[i]; }, [&] { return sum; });
// ans 按添加查询的顺序保存，本例为 {3,5}；这里只演示区间和。
// 四个回调依次为初始化、加入位置、删除位置、读取当前答案。
#include <bits/stdc++.h>
using namespace std;

struct Mo {
    struct Query {
        int l, r, id;
    };
    int n, block;
    vector<Query> q;
    explicit Mo(int n) : n(n), block(1) {}
    int add_query(int l, int r) {
        assert(0 <= l && l <= r && r < n);
        int id = q.size();
        q.push_back({l, r, id});
        return id;
    }
    // 回调接收0base位置；begin负责本次工作状态初始化，answer返回当前答案。
    template <class Begin, class Add, class Del, class Answer>
    auto solve(Begin begin, Add add, Del del, Answer answer) {
        using T = decay_t<decltype(answer())>;
        begin();
        vector<T> result(q.size());
        if (q.empty()) return result;
        block = max(1, (int)(n / sqrt((double)q.size())));
        auto sorted = q;
        sort(sorted.begin(), sorted.end(), [&](Query a, Query b) {
            int x = a.l / block, y = b.l / block;
            return x != y ? x < y : (x & 1 ? a.r > b.r : a.r < b.r);
        });
        int l = 0, r = -1;
        for (auto query : sorted) {
            // 先扩展后收缩，回调不会删除尚未加入的元素。
            while (l > query.l) add(--l);
            while (r < query.r) add(++r);
            while (l < query.l) del(l++);
            while (r > query.r) del(r--);
            result[query.id] = answer();
        }
        return result;
    }
};
