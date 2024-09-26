#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e5+10;
int mod;
void add(int &x,int y){if((x+=y)>=mod)x-=mod;}
struct Node{
    int l,r,res,tag;  
};
struct SegmentTree{
    Node a[maxn*4];
    void tag_init(int i){
        a[i].tag=0;
    }
    void tag_union(int fa,int i){
        add(a[i].tag,a[fa].tag);
    }
    void tag_cal(int i){
        add(a[i].res,(ll)a[i].tag*(a[i].r-a[i].l+1)%mod);
    }
    void pushdown(int i){
        tag_cal(i);
        if(a[i].l!=a[i].r){
            tag_union(i,i*2);
            tag_union(i,i*2+1);
        }
        tag_init(i);
    }
    void pushup(int i){
        if(a[i].l==a[i].r)return;
        pushdown(i*2);
        pushdown(i*2+1);
        a[i].res=(a[i*2].res+a[i*2+1].res)%mod;
    }
    void build(int i,int l,int r){
        a[i].l=l,a[i].r=r;tag_init(i);a[i].res=0;
        if(l>=r)return;
        int mid=(l+r)/2;
        build(i*2,l,mid);
        build(i*2+1,mid+1,r);
    }
    void update(int i,int l,int r,int w){
        pushdown(i);
        if(a[i].r<l||a[i].l>r||l>r)return;
        if(a[i].l>=l&&a[i].r<=r){
            a[i].tag=w;
            return;
        }
        update(i*2,l,r,w);
        update(i*2+1,l,r,w);
        pushup(i);
    }
    int query(int i,int l,int r){
        pushdown(i);
        if(a[i].r<l||a[i].l>r||l>r)return 0;
        if(a[i].l>=l&&a[i].r<=r){
            return a[i].res;
        }
        return (query(i*2,l,r)+query(i*2+1,l,r))%mod;
    }
};
SegmentTree tri;
vector<int> ve[maxn];
int L[maxn],R[maxn],tot,root=1;
int siz[maxn],top[maxn],dep[maxn],fa[maxn],dfn[maxn];
void dfs_sz(int x,int h){
    if(x!=root)ve[x].erase(find(ve[x].begin(),ve[x].end(),h));
    siz[x] = 1;
    dep[x]=dep[h]+1;
    fa[x]=h;
    for(auto &it:ve[x]) {
        dfs_sz(it,x);
        siz[x] += siz[it];
        if(siz[it] > siz[ve[x][0]]) {
            swap(it, ve[x][0]);
        }
    }
}
void dfs_hld(int x) {
    L[x] =++tot;
    dfn[tot]=x;
    for(auto it: ve[x]) {
        top[it] = (it == ve[x][0] ? top[x] : it);
        dfs_hld(it);
    }
    R[x] =tot;
}
void chain_add(int x, int y, int w) {// chain add w
    while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		tri.update(1, L[top[x]], L[x], w);
        x = fa[top[x]];
	}
	if(L[x] > L[y]) swap(x, y);
	tri.update(1, L[x], L[y], w);
}
int chain_sum(int x, int y) {// query the length of chain
	int sum=0;
    while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		add(sum,tri.query(1, L[top[x]], L[x]));
        x = fa[top[x]];
	}
	if(L[x] > L[y]) swap(x, y);
	add(sum,tri.query(1, L[x], L[y]));
    return sum;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,q;cin>>n>>q>>root>>mod;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++)cin>>a[i],a[i]%=mod;
    for(int i=1;i<n;i++){
        int x,y;cin>>x>>y;
        ve[x].push_back(y);
        ve[y].push_back(x);
    }
    top[root]=root;
    tri.build(1,1,n);dfs_sz(root,0);dfs_hld(root);
    for(int i=1;i<=n;i++){
        tri.update(1,L[i],L[i],a[i]);
    }
    while(q--){
        int op;cin>>op;
        if(op==1){
            int x,y,w;cin>>x>>y>>w;
            chain_add(x,y,w);
        }
        if(op==2){
            int x,y;cin>>x>>y;
            cout<<chain_sum(x,y)<<"\n";
        }
        if(op==3){//update the subtree of root x +=y
            int x,y;cin>>x>>y;
            tri.update(1,L[x],R[x],y);
        }
        if(op==4){
            int x;cin>>x;
            cout<<tri.query(1,L[x],R[x])<<"\n";
        }
    }

}                                                   