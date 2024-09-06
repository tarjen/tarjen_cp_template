// root 表示整棵线段树的根结点；cnt 表示当前结点个数
const int maxn=1e5+10;
int n, cnt, root;
int sum[maxn*20], ls[maxn*20], rs[maxn*20];

// 用法：update(root, 1, n, x, f); 其中 x 为待修改节点的编号
void update(int& p, int L, int R, int x, int f) {  // 引用传参
    if (!p) p = ++cnt;  // 当结点为空时，创建一个新的结点
    if (L == R) {
        sum[p] += f;
        return;
    }
    int m = L + ((R - L) >> 1);
    if (x <= m)
        update(ls[p], L, m, x, f);
    else
        update(rs[p], m + 1, R, x, f);
    sum[p] = sum[ls[p]] + sum[rs[p]];  // pushup
}
// 用法：query(root, 1, n, l, r);
int query(int p, int L, int R, int l, int r) {
    if (!p) return 0;  // 如果结点为空，返回 0
    if (L >= l && R <= r) return sum[p];
    int m = L + ((R - L) >> 1), ans = 0;
    if (l <= m) ans += query(ls[p], L, m, l, r);
    if (r > m) ans += query(rs[p], m + 1, R, l, r);
    return ans;
}
int merge(int a, int b, int l, int r) {
    if (!a) return b;
    if (!b) return a;
    if (l == r) {
        sum[a]+=sum[b];
        return a;
    }
    int mid = (l + r) >> 1;
    ls[a] = merge(ls[a], ls[b], l, mid);
    rs[a] = merge(rs[a], rs[b], mid + 1, r);
    sum[a]=sum[ls[a]]+sum[rs[a]];
    return a;
}
void split(int &p, int &q, int L, int R, int l, int r) {//p 原树 q新树
    if (R < l || r < L) return;
    if (!p) return;
    if (l <= L && R <= r) {
        q = p;
        p = 0;
        return;
    }
    if (!q) q = ++cnt;
    int m = L + R >> 1;
    if (l <= m) split(ls[p], ls[q], L, m, l, r);
    if (m < r) split(rs[p], rs[q], m + 1, R, l, r);
    sum[p]=sum[ls[p]]+sum[rs[p]];
    sum[q]=sum[ls[q]]+sum[rs[q]];
}
int query1(int& Sum,int Up, int rt, int l, int r) {//min_x of f(x)+x>Up 
    // cout<<"Sum="<<Sum<<" Up="<<Up<<" rt="<<rt<<" l="<<l<<" r="<<r<<"\n";
    if(!rt){
        if(r+Sum<=Up)return -1;
        else return r-(r+Sum-Up)+1;
    }
    if (true) {
        int ss = Sum+sum[rt];
        if (ss+r<=Up) {
            Sum = ss;
            return -1;
        }
        if (l == r)return l;
    }
    int mid = (l + r) / 2;
    int pos = query1(Sum,Up,ls[rt], l, mid);
    if (pos != -1)return pos;
    return query1(Sum,Up,rs[rt], mid + 1, r);
}