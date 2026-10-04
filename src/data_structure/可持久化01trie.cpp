// 非负31位整数；Persistent_Trie tr; append(x); max_xor(l,r,x)查询1base闭区间；版本0为空。
#include <bits/stdc++.h>
using namespace std;

struct Persistent_Trie {
    struct Node { array<int,2> ch{}; int sum=0; };
    int bits;
    vector<Node> a{Node()};
    vector<int> root{0};
    explicit Persistent_Trie(int bits=31): bits(bits) { assert(1<=bits&&bits<=31); }
    int insert(int old,int num,int bit) {
        Node copy=a[old]; copy.sum++;
        int now=a.size(); a.push_back(copy);
        if(bit<0) return now;
        int c=(num>>bit)&1;
        a[now].ch[c]=insert(a[old].ch[c],num,bit-1);
        return now;
    }
    int insert(int old,int num) { assert(num>=0); return insert(old,num,bits-1); }
    int append(int num) { int p=insert(root.back(),num); root.push_back(p); return (int)root.size()-1; }
    // s,t是两个根编号；t版本必须包含s版本，且差集非空。
    int query(int s,int t,int x) const {
        assert(a[t].sum>a[s].sum);
        int ans=0;
        for(int bit=bits-1;bit>=0;bit--) {
            int c=(x>>bit)&1,want=c^1;
            if(a[a[t].ch[want]].sum>a[a[s].ch[want]].sum) c=want,ans|=1<<bit;
            s=a[s].ch[c]; t=a[t].ch[c];
        }
        return ans;
    }
    int max_xor(int l,int r,int x) const { return query(root[l-1],root[r],x); }
};
