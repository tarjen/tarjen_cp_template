// 1base；Mo mo(n); add_query(l,r); solve(begin,add,del,answer)；保留通用移动框架，统计规则由回调提供。
#include <bits/stdc++.h>
using namespace std;

struct Mo {
    struct Query { int l,r,id; };
    int n,block;
    vector<Query> q;
    explicit Mo(int n): n(n),block(1) {}
    int add_query(int l,int r) { assert(1<=l&&l<=r&&r<=n); int id=q.size(); q.push_back({l,r,id}); return id; }
    // 回调接收1base位置；begin负责本次工作状态初始化，answer返回当前答案。
    template<class Begin,class Add,class Del,class Answer>
    auto solve(Begin begin,Add add,Del del,Answer answer) {
        using T=decay_t<decltype(answer())>;
        begin(); vector<T> result(q.size()); if(q.empty()) return result;
        block=max(1,(int)(n/sqrt((double)q.size())));
        auto sorted=q;
        sort(sorted.begin(),sorted.end(),[&](Query a,Query b) {
            int x=(a.l-1)/block,y=(b.l-1)/block;
            return x!=y?x<y:(x&1?a.r>b.r:a.r<b.r);
        });
        int l=1,r=0;
        for(auto query:sorted) {
            // 先扩展后收缩，回调不会删除尚未加入的元素。
            while(l>query.l) add(--l);
            while(r<query.r) add(++r);
            while(l<query.l) del(l++);
            while(r>query.r) del(r--);
            result[query.id]=answer();
        }
        return result;
    }
};
