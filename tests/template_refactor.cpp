#include <bits/stdc++.h>
using namespace std;
using ll = long long;
namespace bit {
#include "../src/data_structure/树状数组单点修改区间查询tree.cpp"
}
namespace rangebit {
#include "../src/data_structure/树状数组.cpp"
}
namespace bit2 {
#include "../src/data_structure/二维树状数组.cpp"
}
namespace weighted {
#include "../src/graph/带权并查集dsu.cpp"
}
namespace relation {
#include "../src/others/可以判断不同或相同的并查集.cpp"
}
namespace seg {
#include "../src/data_structure/SegmentTree.cpp"
}
namespace pointseg {
#include "../src/data_structure/SegmentTree单点.cpp"
}
namespace sumseg {
#include "../src/data_structure/线段树区间加区间求和getsum.cpp"
}
namespace minseg {
#include "../src/data_structure/线段树区间加区间getmin.cpp"
}
namespace assignseg {
#include "../src/data_structure/线段树区间赋值区间getmin.cpp"
}
namespace historyseg {
#include "../src/data_structure/线段树区间加区间历史最小值.cpp"
}
namespace binarytrie {
#include "../src/data_structure/01trie.cpp"
}
namespace trie {
#include "../src/string/字典树trie.cpp"
}
namespace flow {
#include "../src/graph/maxflow网络流最大流.cpp"
}
namespace flow2 {
#include "../src/graph/maxflow只算值版本.cpp"
}
namespace costflow {
#include "../src/graph/最小费用最大流.cpp"
}
namespace lichao {
#include "../src/data_structure/李超树.cpp"
}
namespace buildings {
#include "../src/data_structure/楼房重建.cpp"
}
namespace kmp {
#include "../src/string/kmp.cpp"
}
namespace exkmp {
#include "../src/string/exkmp.cpp"
}
namespace manacher {
#include "../src/string/manacher.cpp"
}
namespace ac {
#include "../src/string/AC自动机.cpp"
}
namespace sam {
#include "../src/string/后缀自动机SAM.cpp"
}
namespace pam {
#include "../src/string/回文自动机PAM.cpp"
}
namespace suffix {
#include "../src/string/倍增sa.cpp"
}
namespace dc3 {
#include "../src/string/dc3.cpp"
}
namespace lca {
#include "../src/data_structure/最近公共祖先LCA.cpp"
}
namespace rmqlca {
#include "../src/data_structure/lca(o1).cpp"
}
namespace hld {
#include "../src/data_structure/树链剖分.cpp"
}
namespace tarjan {
#include "../src/graph/tarjan缩点.cpp"
}
namespace kosaraju {
#include "../src/graph/kosaraju.cpp"
}
namespace bcc {
#include "../src/graph/点双边双.cpp"
}
namespace matching {
#include "../src/graph/二分图匹配.cpp"
}
namespace km {
#include "../src/graph/二分图最优匹配.cpp"
}
namespace unicyclic {
#include "../src/graph/基环树.cpp"
}
namespace dominator {
#include "../src/graph/支配树.cpp"
}

uint64_t checks=0;
#define CHECK(expr) do { ++checks; if(!(expr)) { cerr<<"FAIL line "<<__LINE__<<": "<<#expr<<"\n"; exit(1); } } while(0)
mt19937 rng(20261004);
int rnd(int lo,int hi) { return lo+(int)(rng()%(hi-lo+1)); }
string random_string(int n) { string s; while(n--) s+='a'+rnd(0,2); return s; }
bool palindrome(const string& s) { return equal(s.begin(),s.end(),s.rbegin()); }
ll sum(const vector<ll>& a,int l,int r) { return accumulate(a.begin()+l,a.begin()+r+1,0LL); }
ll minimum(const vector<ll>& a,int l,int r) { return *min_element(a.begin()+l,a.begin()+r+1); }

void test_arrays() {
    for(int trial=0;trial<200;trial++) {
        int n=rnd(1,25); vector<ll> a(n+1),b(n+1),h(n+1),p(n+1);
        for(int i=1;i<=n;i++) a[i]=rnd(-50,50);
        b=h=p=a;
        bit::Treearray bit(n),untouched(n);
        rangebit::RangeTreearray rb(a);
        seg::SegmentTree st(a); sumseg::SegmentTree ss(a); minseg::SegmentTree ms(a);
        assignseg::SegmentTree as(a); historyseg::SegmentTree hs(a); pointseg::SegmentTree ps(a);
        for(int i=1;i<=n;i++) bit.update(i,a[i]);
        for(int q=0;q<200;q++) {
            int l=rnd(1,n),r=rnd(l,n),x=rnd(1,n); ll w=rnd(-100,100);
            if(q%3) {
                st.update(l,r,w); ss.update(l,r,w); ms.update(l,r,w); rb.update(l,r,w); hs.update(l,r,w);
                as.update(l,r,w); ps.update(x,w);
                for(int i=l;i<=r;i++) a[i]+=w,bit.update(i,w),b[i]=w,h[i]=min(h[i],a[i]);
                p[x]=w;
            } else {
                CHECK(bit.query(l,r)==sum(a,l,r)); CHECK(rb.query(l,r)==sum(a,l,r));
                CHECK(st.query(l,r)==sum(a,l,r)); CHECK(ss.query(l,r)==sum(a,l,r));
                CHECK(ms.query(l,r)==minimum(a,l,r)); CHECK(as.query(l,r)==minimum(b,l,r));
                CHECK(hs.query(l,r)==minimum(h,l,r)); CHECK(ps.query(l,r)==sum(p,l,r));
                CHECK(untouched.query(l,r)==0);
            }
        }
        vector<ll> nonnegative(n+1);
        seg::SegmentTree search(n); pointseg::SegmentTree pointsearch(n);
        for(int i=1;i<=n;i++) nonnegative[i]=rnd(0,10),search.update(i,i,nonnegative[i]),pointsearch.update(i,nonnegative[i]);
        for(int q=0;q<50;q++) {
            int l=rnd(1,n),r=rnd(l,n),left=-1,right=-1; ll need=rnd(1,100),acc=0;
            for(int i=l;i<=n;i++) if((acc+=nonnegative[i])>=need) { right=i; break; }
            acc=0;
            for(int i=r;i>=1;i--) if((acc+=nonnegative[i])>=need) { left=i; break; }
            CHECK(search.min_right(l,need)==right); CHECK(pointsearch.min_right(l,need)==right);
            CHECK(search.max_left(r,need)==left); CHECK(pointsearch.max_left(r,need)==left);
        }
    }
    assignseg::SegmentTree sentinel(2); sentinel.update(1,2,LLONG_MAX); CHECK(sentinel.query(1,2)==LLONG_MAX);
    sumseg::SegmentTree large(2); large.update(1,2,3000000000LL); CHECK(large.query(1,2)==6000000000LL);
    historyseg::SegmentTree largehistory(vector<ll>{0,4000000000LL}); CHECK(largehistory.query(1,1)==4000000000LL);
    bit::Treearray reset(5); reset.update(4,5); reset.set_n(2); CHECK(reset.getsum(2)==0);
    seg::SegmentTree empty(0); CHECK(empty.query(1,0)==0);
    for(int trial=0;trial<100;trial++) {
        int n=rnd(1,8),m=rnd(1,8); bit2::Treearray2D t(n,m),other(n,m);
        vector<vector<ll>> a(n+1,vector<ll>(m+1));
        for(int q=0;q<100;q++) {
            int x=rnd(1,n),y=rnd(1,m),xx=rnd(x,n),yy=rnd(y,m); ll w=rnd(-100000,100000);
            if(q%2) {
                t.update(x,y,xx,yy,w);
                for(int i=x;i<=xx;i++) for(int j=y;j<=yy;j++) a[i][j]+=w;
            } else {
                ll ans=0; for(int i=x;i<=xx;i++) for(int j=y;j<=yy;j++) ans+=a[i][j];
                CHECK(t.query(x,y,xx,yy)==ans); CHECK(other.query(x,y,xx,yy)==0);
            }
        }
    }
    cout<<"arrays OK\n";
}

void test_dsu() {
    for(int trial=0;trial<100;trial++) {
        int n=8; weighted::WeightedDSU d(n),other(n); relation::RelationDSU rel(n);
        vector<vector<pair<int,int>>> g(n+1),rg(n+1);
        auto path=[&](const auto& graph,int s,int t,bool parity) -> optional<int> {
            vector<int> vis(n+1),value(n+1); vector<int> todo{s}; vis[s]=1;
            for(int i=0;i<(int)todo.size();i++) {
                int u=todo[i]; if(u==t) return value[u];
                for(auto [v,w]:graph[u]) if(!vis[v]) vis[v]=1,value[v]=parity?(value[u]^w):value[u]+w,todo.push_back(v);
            }
            return {};
        };
        for(int q=0;q<100;q++) {
            int u=rnd(1,n),v=rnd(1,n),w=rnd(-20,20),par=rnd(0,1);
            auto expect=path(g,u,v,false); bool ok=!expect||*expect==w;
            CHECK(d.unit(u,v,w)==ok);
            if(!expect) g[u].push_back({v,w}),g[v].push_back({u,-w});
            d.getf(u); d.getf(v); if(expect) CHECK(d.dis[u]-d.dis[v]==*expect);
            auto rp=path(rg,u,v,true); bool rok=!rp||*rp==par;
            CHECK(rel.merge(u,par?-v:v)==rok);
            if(!rp) rg[u].push_back({v,par}),rg[v].push_back({u,par});
            CHECK(other.getf(u)==u); CHECK(other.dis[u]==0);
        }
    }
    cout<<"DSU OK\n";
}

void test_tries() {
    trie::Trie t,other; binarytrie::Trie bt;
    map<string,int> words; map<int,int> numbers;
    for(int i=0;i<2000;i++) {
        string s=random_string(rnd(0,15)); t.insert(s); words[s]++;
        int x=rnd(0,100000); bt.insert(x); numbers[x]++;
    }
    for(auto [s,count]:words) {
        int u=0; for(char c:s) u=t.tree[u][c-'a']; CHECK(t.e[u]==count);
    }
    for(auto [x,count]:numbers) {
        int u=0; for(int i=30;i>=0;i--) u=bt.tree[u][x>>i&1]; CHECK(bt.e[u]==count);
    }
    CHECK(other.tot==0); CHECK(other.e[0]==0);
    cout<<"tries / node pool growth OK\n";
}

void test_geometry_trees() {
    for(int trial=0;trial<100;trial++) {
        lichao::SegmentTree t(-10,10),other(-10,10);
        vector<tuple<int,int,lichao::Line>> lines;
        for(int id=1;id<=100;id++) {
            int l=rnd(-10,10),r=rnd(l,10); lichao::Line line{double(rnd(-20,20)),double(rnd(-100,100)),id};
            t.update(l,r,line); lines.push_back({l,r,line});
            for(int x=-10;x<=10;x++) {
                lichao::Line best=lichao::inf;
                for(auto [a,b,ln]:lines) if(a<=x&&x<=b&&lichao::linecmp(ln,best,x)) best=ln;
                CHECK(t.query(x).id==best.id); CHECK(other.query(x).id==0);
            }
        }
        int n=rnd(1,30); buildings::SegmentTree b(n),zero(n); vector<ll> heights(n+1);
        for(int q=0;q<100;q++) {
            int x=rnd(1,n); heights[x]=rnd(0,1000); b.update_height(x,heights[x]);
            int ans=0,best=0;
            for(int i=1;i<=n;i++) if(heights[i]*max(1,best)>heights[best]*i) ans++,best=i;
            CHECK(b.query()==ans); CHECK(zero.query()==0);
        }
    }
    cout<<"Li Chao / buildings OK\n";
}

void test_strings() {
    for(int trial=0;trial<400;trial++) {
        string s=random_string(rnd(0,30)),t=random_string(rnd(0,12));
        kmp::KMP k(t); exkmp::EXKMP ex(s,t); manacher::Manacher m(s);
        vector<int> expected;
        for(int i=0;i+(int)t.size()<=(int)s.size();i++) if(s.substr(i,t.size())==t) expected.push_back(i+1);
        CHECK(k.find(s)==expected);
        for(int i=1;i<=(int)t.size();i++) {
            int z=0; while(i-1+z<(int)t.size()&&t[z]==t[i-1+z]) z++; CHECK(ex.next[i]==z);
            int pi=0; for(int len=1;len<i;len++) if(t.substr(0,len)==t.substr(i-len,len)) pi=len;
            CHECK(k.nxt[i]==pi);
        }
        for(int i=1;i<=(int)s.size();i++) {
            int z=0; while(z<(int)t.size()&&i-1+z<(int)s.size()&&s[i-1+z]==t[z]) z++;
            CHECK(ex.extend[i]==z);
        }
        int longest=0; map<string,int> substrings; set<string> palindromes;
        for(int l=0;l<(int)s.size();l++) for(int r=l;r<(int)s.size();r++) {
            string sub=s.substr(l,r-l+1); substrings[sub]++;
            bool ispal=palindrome(sub); CHECK(m.is_palindrome(l,r)==ispal);
            if(ispal) longest=max(longest,r-l+1),palindromes.insert(sub);
        }
        CHECK(m.manacher()==longest);
        sam::SAM automaton(s),empty; CHECK(empty.tot==1); CHECK(automaton.n==(int)s.size());
        ll distinct=0;
        for(int u=2;u<=automaton.tot;u++) distinct+=automaton.ep[u].len-automaton.ep[automaton.ep[u].fa].len;
        CHECK(distinct==(ll)substrings.size());
        for(auto [sub,count]:substrings) {
            int u=1; for(char c:sub) u=automaton.ep[u].tr[c-'a']; CHECK(automaton.siz[u]==count);
        }
        automaton.build(t); CHECK(automaton.n==(int)t.size());
        pam::PAM pa(s),online;
        CHECK(pa.cnt-1==(int)palindromes.size());
        for(int i=0;i<(int)s.size();i++) {
            int u=online.insert(s[i]),suffix_count=0,max_len=0;
            for(int l=0;l<=i;l++) if(palindrome(s.substr(l,i-l+1))) suffix_count++,max_len=max(max_len,i-l+1);
            CHECK(online.b[u].num==suffix_count); CHECK(online.b[u].len==max_len);
        }
        ac::AC ac,other; vector<string> patterns;
        for(int i=0;i<15;i++) patterns.push_back(random_string(rnd(1,6))),ac.insert(patterns.back());
        ac.build(); ac.build(); other.build();
        for(const string& text:vector<string>{s,t,s}) {
            int count=0; for(const string& p:patterns) count+=text.find(p)!=string::npos;
            CHECK(ac.query(text)==count); CHECK(other.query(text)==0);
        }
        suffix::Suffix sa(s); dc3::Suffix dc(s);
        vector<int> order(s.size()); iota(order.begin(),order.end(),0);
        sort(order.begin(),order.end(),[&](int a,int b){return s.substr(a)<s.substr(b);});
        for(int i=0;i<(int)s.size();i++) {
            CHECK(sa.sa[i+1]==order[i]+1); CHECK(dc.sa[i+1]==order[i]);
            CHECK(sa.rk[order[i]+1]==i+1); CHECK(dc.rk[order[i]]==i+1);
            int lcp=0;
            if(i) while(order[i]+lcp<(int)s.size()&&order[i-1]+lcp<(int)s.size()&&s[order[i]+lcp]==s[order[i-1]+lcp]) lcp++;
            CHECK(sa.ht[i+1]==lcp); CHECK(dc.ht[i+1]==lcp);
        }
        for(int i=1;i<=(int)s.size();i++) for(int j=1;j<=(int)s.size();j++) {
            int lc=0; while(i-1+lc<(int)s.size()&&j-1+lc<(int)s.size()&&s[i-1+lc]==s[j-1+lc]) lc++;
            CHECK(sa.lcp(i,j)==lc);
            int r=rnd(i,s.size()),rr=rnd(j,s.size()); string a=s.substr(i-1,r-i+1),b=s.substr(j-1,rr-j+1);
            CHECK(sa.query(i,r,j,rr)==(a<b?-1:a>b?1:0));
        }
    }
    string bytes; for(int i=0;i<256;i++) bytes+=(char)i;
    suffix::Suffix sa(bytes); dc3::Suffix dc(bytes); CHECK(sa.sa[1]==1); CHECK(dc.sa[1]==0);
    manacher::Manacher specials(string("@#@\0",4)); CHECK(specials.manacher()==3);
    cout<<"strings OK\n";
}

vector<int> reachable(const vector<vector<int>>& g,int root,int removed=0) {
    vector<int> vis(g.size()); if(root==removed) return vis;
    vector<int> todo{root}; vis[root]=1;
    for(int i=0;i<(int)todo.size();i++) for(int v:g[todo[i]]) if(v!=removed&&!vis[v]) vis[v]=1,todo.push_back(v);
    return vis;
}
void test_trees() {
    for(int trial=0;trial<150;trial++) {
        int n=rnd(1,30),root=rnd(1,n),mod=trial%2?97:2000000000;
        vector<vector<int>> g(n+1); vector<int> values(n+1);
        for(int v=2;v<=n;v++) { int p=rnd(1,v-1); g[p].push_back(v); g[v].push_back(p); }
        lca::LCA a(g,root); rmqlca::LCA b(n); for(int u=1;u<=n;u++) for(int v:g[u]) if(u<v) b.addedge(u,v);
        b.build(root); b.build(root);
        vector<int> parent(n+1),depth(n+1),order{root};
        for(int i=0;i<(int)order.size();i++) for(int v:g[order[i]]) if(v!=parent[order[i]]) parent[v]=order[i],depth[v]=depth[order[i]]+1,order.push_back(v);
        auto path=[&](int u,int v) {
            vector<int> result;
            while(u!=v) { if(depth[u]<depth[v]) swap(u,v); result.push_back(u); u=parent[u]; }
            result.push_back(u); return result;
        };
        for(int i=1;i<=n;i++) values[i]=rnd(0,1000);
        hld::HLD h(g,values,root,mod),independent(g,vector<int>(n+1),root,mod);
        for(int q=0;q<150;q++) {
            int u=rnd(1,n),v=rnd(1,n),x=u,y=v; ll w=rnd(-100000,100000);
            while(x!=y) { if(depth[x]<depth[y]) swap(x,y); x=parent[x]; }
            CHECK(a.lca(u,v)==x); CHECK(b.lca(u,v)==x);
            vector<int> nodes;
            if(q%2) nodes=path(u,v);
            else for(int z=1;z<=n;z++) { int zz=z; while(zz&&zz!=u) zz=parent[zz]; if(zz==u) nodes.push_back(z); }
            if(q%3) {
                if(q%2) h.chain_add(u,v,w); else h.subtree_add(u,w);
                for(int z:nodes) values[z]=((ll)values[z]+w%mod+mod)%mod;
            } else {
                ll expected=0; for(int z:nodes) expected=(expected+values[z])%mod;
                CHECK((q%2?h.chain_sum(u,v):h.subtree_sum(u))==expected);
                CHECK(independent.chain_sum(u,v)==0);
            }
        }
    }
    // 长链验证栈深及动态倍增层数。
    int n=100000; vector<vector<int>> chain(n+1); vector<int> values(n+1,1);
    for(int i=1;i<n;i++) chain[i].push_back(i+1),chain[i+1].push_back(i);
    lca::LCA a(chain); CHECK(a.lca(n,n/2)==n/2);
    rmqlca::LCA b(n); for(int i=1;i<n;i++) b.addedge(i,i+1); b.build(); CHECK(b.lca(n,n/2)==n/2);
    hld::HLD h(chain,values,1,998244353); CHECK(h.chain_sum(1,n)==n);
    cout<<"trees / 100000 vertex chain OK\n";
}

void test_scc_dominator() {
    for(int trial=0;trial<300;trial++) {
        int n=rnd(1,9); vector<vector<int>> g(n+1);
        for(int u=1;u<=n;u++) for(int v=1;v<=n;v++) if(rnd(0,3)==0) g[u].push_back(v);
        tarjan::SCC a(g); kosaraju::SCC b(g); a.build(); b.build();
        vector<vector<int>> reach(n+1); for(int u=1;u<=n;u++) reach[u]=reachable(g,u);
        for(int u=1;u<=n;u++) for(int v=1;v<=n;v++) {
            bool same=reach[u][v]&&reach[v][u]; CHECK((a.col[u]==a.col[v])==same); CHECK((b.col[u]==b.col[v])==same);
        }
        int root=rnd(1,n); dominator::DominatorTree dt(g,root); CHECK(dt.solve(root)==accumulate(reach[root].begin(),reach[root].end(),0));
        vector<vector<int>> dominates(n+1,vector<int>(n+1));
        for(int d=1;d<=n;d++) {
            auto removed=reachable(g,root,d);
            for(int v=1;v<=n;v++) dominates[d][v]=reach[root][v]&&!removed[v];
        }
        for(int v=1;v<=n;v++) {
            int expected=0;
            if(v!=root&&reach[root][v]) for(int d=1;d<=n;d++) if(d!=v&&dominates[d][v]) {
                bool closest=true;
                for(int x=1;x<=n;x++) if(x!=v&&x!=d&&dominates[x][v]&&!dominates[x][d]) closest=false;
                if(closest) expected=d;
            }
            CHECK(dt.up[v]==expected);
        }
    }
    vector<vector<int>> chain(100001); for(int i=1;i<100000;i++) chain[i].push_back(i+1);
    tarjan::SCC a(chain); kosaraju::SCC b(chain); CHECK(a.num==100000); CHECK(b.cnt==100000);
    cout<<"SCC / dominator OK\n";
}

void test_bcc() {
    for(int trial=0;trial<300;trial++) {
        int n=rnd(1,9); bcc::BCC b(n); vector<pair<int,int>> edges;
        for(int u=1;u<=n;u++) for(int v=u+1;v<=n;v++) if(rnd(0,3)==0) {
            edges.push_back({u,v}); b.link(u,v);
            if(rnd(0,3)==0) edges.push_back({u,v}),b.link(u,v);
        }
        b.build(); b.build();
        auto graph=[&](int removed_edge) {
            vector<vector<int>> g(n+1);
            for(int id=0;id<(int)edges.size();id++) if(id!=removed_edge) { auto [u,v]=edges[id]; g[u].push_back(v); g[v].push_back(u); }
            return g;
        };
        auto g=graph(-1);
        auto components=[&](int removed) {
            int count=0; vector<int> vis(n+1);
            for(int u=1;u<=n;u++) if(u!=removed&&!vis[u]) {
                count++; auto r=reachable(g,u,removed); for(int v=1;v<=n;v++) vis[v]|=r[v];
            }
            return count;
        };
        int baseline=components(0);
        for(int u=1;u<=n;u++) CHECK(bool(b.iscut[u])==(components(u)>baseline));
        for(int id=0;id<(int)edges.size();id++) {
            auto [u,v]=edges[id]; CHECK(bool(b.bridge[id])==!reachable(graph(id),u)[v]);
        }
        vector<vector<int>> eb(n+1);
        for(int id=0;id<(int)edges.size();id++) if(!b.bridge[id]) { auto [u,v]=edges[id]; eb[u].push_back(v); eb[v].push_back(u); }
        for(int u=1;u<=n;u++) for(int v=u+1;v<=n;v++) {
            CHECK((b.bccno[u]==b.bccno[v])==bool(reachable(eb,u)[v]));
            bool common=false; for(int c:b.vbccno[u]) common|=b.vbccno[v].count(c)>0;
            bool expected=reachable(g,u)[v];
            for(int removed=1;removed<=n;removed++) if(removed!=u&&removed!=v) expected&=reachable(g,u,removed)[v];
            CHECK(common==expected);
        }
        CHECK(accumulate(b.bcc_edge.begin(),b.bcc_edge.end(),0)==(int)edges.size());
    }
    cout<<"BCC / parallel edges / disconnected graphs OK\n";
}

void test_matching() {
    for(int trial=0;trial<200;trial++) {
        int n=rnd(0,6),m=rnd(0,6); matching::Matching mat(n,m); vector<vector<int>> g(n+1);
        for(int u=1;u<=n;u++) for(int v=1;v<=m;v++) if(rnd(0,1)) mat.add(u,v),g[u].push_back(v);
        function<int(int,int)> brute=[&](int u,int used) {
            if(u>n) return 0;
            int ans=brute(u+1,used);
            for(int v:g[u]) if(!(used>>v&1)) ans=max(ans,1+brute(u+1,used|(1<<v)));
            return ans;
        };
        CHECK(mat.maxmatch()==brute(1,0)); CHECK(mat.maxmatch()==brute(1,0));
        vector<vector<ll>> weights(n+1,vector<ll>(n+1));
        for(int u=1;u<=n;u++) for(int v=1;v<=n;v++) weights[u][v]=rnd(-1000,1000);
        km::KM k(weights); vector<int> p(n); iota(p.begin(),p.end(),1); ll best=LLONG_MIN;
        do { ll val=0; for(int u=1;u<=n;u++) val+=weights[u][p[u-1]]; best=max(best,val); } while(next_permutation(p.begin(),p.end()));
        CHECK(k.maxmatch()==best); CHECK(k.maxmatch()==best);
    }
    cout<<"matching / KM OK\n";
}

void test_flows() {
    for(int trial=0;trial<250;trial++) {
        int n=rnd(2,7),s=0,t=n-1; flow::Maxflow a(n,s,t); flow2::dinic b(n,s,t);
        vector<tuple<int,int,int>> edges;
        for(int u=0;u<n;u++) for(int v=0;v<n;v++) if(rnd(0,3)==0) {
            int cap=rnd(0,4); a.addedge(u,v,cap); b.addedge(u,v,cap); edges.push_back({u,v,cap});
        }
        ll cut=LLONG_MAX;
        for(int mask=0;mask<(1<<n);mask++) if((mask>>s&1)&&!(mask>>t&1)) {
            ll val=0; for(auto [u,v,w]:edges) if((mask>>u&1)&&!(mask>>v&1)) val+=w;
            cut=min(cut,val);
        }
        CHECK(a.dinic()==cut); CHECK(b.maxflow()==cut); CHECK(a.dinic()==0); CHECK(b.maxflow()==0);
    }
    // DAG允许负费用边；穷举每条边的流量，检查最大流及其中最小费用。
    for(int trial=0;trial<150;trial++) {
        int n=4; costflow::SSP a(n,0,n-1); vector<tuple<int,int,int,int>> edges;
        for(int u=0;u<n;u++) for(int v=u+1;v<n;v++) if(rnd(0,1)) {
            int w=rnd(0,2),c=rnd(-5,5); a.add(u,v,w,c); edges.push_back({u,v,w,c});
        }
        pair<ll,ll> best{0,0}; vector<int> balance(n);
        function<void(int,ll)> brute=[&](int id,ll cost) {
            if(id==(int)edges.size()) {
                for(int i=1;i<n-1;i++) if(balance[i]) return;
                if(balance[0]<0||balance[0]!=-balance[n-1]) return;
                if(balance[0]>best.first||(balance[0]==best.first&&cost<best.second)) best={balance[0],cost};
                return;
            }
            auto [u,v,cap,c]=edges[id];
            for(int f=0;f<=cap;f++) { balance[u]+=f; balance[v]-=f; brute(id+1,cost+f*c); balance[u]-=f; balance[v]+=f; }
        };
        brute(0,0); CHECK(a.min_cost()==best); CHECK((a.min_cost()==pair<ll,ll>{0,0}));
    }
    flow::Maxflow large(2,0,1); large.addedge(0,1,3000000000LL); CHECK(large.dinic()==3000000000LL);
    cout<<"maxflow / min cost flow OK\n";
}

void test_unicyclic() {
    for(int trial=0;trial<150;trial++) {
        int n=rnd(3,30),cycle=rnd(3,n); unicyclic::Graph g(n);
        for(int i=1;i<=cycle;i++) g.addedge(i,i==cycle?1:i+1);
        for(int i=cycle+1;i<=n;i++) g.addedge(i,rnd(1,i-1));
        g.Get(); g.Get(); CHECK(g.len==cycle);
        for(int s=1;s<=n;s++) {
            vector<int> d(n+1,-1),todo{s}; d[s]=0;
            for(int i=0;i<(int)todo.size();i++) for(int v:g.ve[todo[i]]) if(d[v]==-1) d[v]=d[todo[i]]+1,todo.push_back(v);
            for(int t=1;t<=n;t++) CHECK(g.dis(s,t)==d[t]);
        }
    }
    cout<<"unicyclic graph OK\n";
}

int main() {
    test_arrays(); test_dsu(); test_tries(); test_geometry_trees(); test_strings();
    test_trees(); test_scc_dominator(); test_bcc(); test_matching(); test_flows(); test_unicyclic();
    cout<<"PASS: 36 templates, "<<checks<<" checks, seed 20261004\n";
}
