//注意Sum和cnt的区别
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5; // 数据范围
int n, m;
struct Persistent_SegmentTree
{
    int sum[(maxn << 5) + 10], root[maxn + 10], lch[(maxn << 5) + 10],
        rch[(maxn << 5) + 10], cnt[(maxn<<5)+10];
    int tot = 0;
    void init()
    {
        tot = 0;
    }
    int a[maxn + 10];
    void update(int &rot, int pr, int L, int R, int k)
    { // 插入操作
        rot = ++tot;
        lch[rot] = lch[pr];
        rch[rot] = rch[pr];
        sum[rot] = sum[pr] + k;
        cnt[rot] = cnt[pr] + 1;
        if (L == R)
            return;
        int mid = (L + R) >> 1;
        if (k <= mid)
            update(lch[rot], lch[pr],  L, mid,k);
        else
            update(rch[rot], rch[pr],  mid + 1, R,k);
    }
    int getcnt(int s, int t, int L, int R, int l, int r) // s,t为root[l],root[r]的根节点 中所有大小在[l,r]之间数字出现次数
    {
        if (l <= L && R <= r)
            return cnt[t] - cnt[s];
        int res = 0;
        int mid = (L + R) >> 1;
        if (l <= mid)
            res += getcnt(lch[s], lch[t], L, mid, l, r);
        if (r > mid)
            res += getcnt(rch[s], rch[t], mid + 1, R, l, r);
        return res;
    }

    int getsum(int s, int t, int L, int R, int l, int r) // s,t为root[l],root[r]的根节点 中所有大小在[l,r]之间数字的和
    {
        if (l <= L && R <= r)
            return sum[t] - sum[s];
        int res = 0;
        int mid = (L + R) >> 1;
        if (l <= mid)
            res += getsum(lch[s], lch[t], L, mid, l, r);
        if (r > mid)
            res += getsum(rch[s], rch[t], mid + 1, R, l, r);
        return res;
    }
    int get_Kth_min_Sum(int s,int t,int l,int r,int k,int &nowsum,int &ans){//return 第k小的值
        int ss = nowsum+cnt[t]-cnt[s];
        if (ss<k) {
            nowsum = ss;
            ans+=sum[t]-sum[s];
            return -1;
        }
        if (l == r){
            ans+=(k-nowsum)*l;
            return l;
        }
        int mid=(l+r)/2;
        int pos = get_Kth_min_Sum(lch[s],lch[t],l,mid,k,nowsum,ans);
        if (pos != -1)return pos;
        return get_Kth_min_Sum(rch[s],rch[t],mid+1,r,k,nowsum,ans);
    }
    int get_Kth_max_Sum(int s,int t,int l,int r,int k,int &nowsum,int &ans){//return 第k大的值
        int ss = nowsum+cnt[t]-cnt[s];
        if (ss<k) {
            nowsum = ss;
            ans+=sum[t]-sum[s];
            return -1;
        }
        if (l == r){
            ans+=(k-nowsum)*l;
            return l;
        }
        int mid=(l+r)/2;
        int pos = get_Kth_max_Sum(rch[s],rch[t],mid+1,r,k,nowsum,ans);
        if (pos != -1)return pos;
        return get_Kth_max_Sum(lch[s],lch[t],l,mid,k,nowsum,ans);
    }
    int get_upper(int s,int t,int l,int r,int x){//第一个大于等于x的数
        if (r < x)return -1;
        if (x <= l) {
            int ss = cnt[t]-cnt[s];
            if (ss==0) {
                return -1;
            }
            if (l == r)return l;
        }
        int mid=(l+r)/2;
        int pos = get_upper(lch[s],lch[t],l,mid,x);
        if (pos != -1)return pos;
        return get_upper(rch[s],rch[t],mid+1,r,x);
    }
    int get_lower(int s,int t,int l,int r,int x){//第一个小于等于x的数
        if(l > x)return -1;
        if(x>=r){
            int ss=cnt[t]-cnt[s];
            if(ss==0){
                return -1;
            }
            if(l==r)return r;
        }
        int mid=(l+r)/2;
        int pos=get_lower(rch[s],rch[t],mid+1,r,x);
        if(pos!=-1)return pos;
        return get_lower(lch[s],lch[t],l,mid,x);
    }
};
Persistent_SegmentTree tri;
int main()
{
    int n,q;
    cin >> n >> q;

    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        tri.update(tri.root[i], tri.root[i - 1], 1, n, x);
        assert(1<=x&&x<=n);
    }
    while (q--)
    {
        int ops;cin>>ops;
        int l,r,k,L,R;
        if(ops==1){
            cin>>l>>r>>L>>R;
            cout<<tri.getsum(tri.root[l-1],tri.root[r],1,n,L,R)<<"\n";
        }
        if(ops==2){// get kth max no output -1
            cin>>l>>r>>k;
            int nowsum=0,ans=0;
            cout<<tri.get_Kth_max_Sum(tri.root[l-1],tri.root[r],1,n,k,nowsum,ans)<<"\n";
        }
        if(ops==3){// get kth max sum siz<k return allsum
            cin>>l>>r>>k;
            int nowsum=0,ans=0;
            tri.get_Kth_max_Sum(tri.root[l-1],tri.root[r],1,n,k,nowsum,ans);
            cout<<ans<<"\n";
        }
        if(ops==4){// get kth min no output -1
            cin>>l>>r>>k;
            int nowsum=0,ans=0;
            cout<<tri.get_Kth_min_Sum(tri.root[l-1],tri.root[r],1,n,k,nowsum,ans)<<"\n";
        }
        if(ops==5){// get kth min sum siz<k return allsum
            cin>>l>>r>>k;
            int nowsum=0,ans=0;
            tri.get_Kth_min_Sum(tri.root[l-1],tri.root[r],1,n,k,nowsum,ans);
            cout<<ans<<"\n";
        }
        if(ops==6){// get the min element >= k no return -1
            cin>>l>>r>>k;
            cout<<tri.get_upper(tri.root[l-1],tri.root[r],1,n,k)<<"\n";
        }
        if(ops==7){// get the max element <= k no return -1
            cin>>l>>r>>k;
            cout<<tri.get_lower(tri.root[l-1],tri.root[r],1,n,k)<<"\n";
        }
    }
}