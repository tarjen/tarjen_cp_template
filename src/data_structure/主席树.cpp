// Persistent_SegmentTree tr(n)或tr(lo,hi); append(x); 查询位置为1base，版本0为空。
//注意Sum和cnt的区别
#include <bits/stdc++.h>
using namespace std;
struct Persistent_SegmentTree
{
    int lo,hi,tot=0;
    vector<long long> sum{0};
    vector<int> root{0},lch{0},rch{0},cnt{0};
    Persistent_SegmentTree(int lo,int hi): lo(lo),hi(hi) { assert(0<=lo&&lo<=hi); }
    explicit Persistent_SegmentTree(int n): Persistent_SegmentTree(1,n) {}
    int newnode(int old) {
        int ls=lch[old],rs=rch[old],count=cnt[old]; long long value=sum[old];
        lch.push_back(ls); rch.push_back(rs); cnt.push_back(count); sum.push_back(value);
        return ++tot;
    }
    int insert(int pr,int L,int R,int k) {
        int now=newnode(pr); sum[now]+=k; cnt[now]++;
        if(L==R) return now;
        int mid=L+(int)(((long long)R-L)/2);
        if(k<=mid) lch[now]=insert(lch[pr],L,mid,k);
        else rch[now]=insert(rch[pr],mid+1,R,k);
        return now;
    }
    int append(int value) {
        assert(lo<=value&&value<=hi);
        int now=insert(root.back(),lo,hi,value); root.push_back(now); return (int)root.size()-1;
    }
    int getcnt(int s, int t, int L, int R, int l, int r) // s,t为root[l],root[r]的根节点 中所有大小在[l,r]之间数字出现次数
    {
        if(r<L||R<l||l>r) return 0;
        if (l <= L && R <= r)
            return cnt[t] - cnt[s];
        int res = 0;
        int mid = L+(int)(((long long)R-L)/2);
        if (l <= mid)
            res += getcnt(lch[s], lch[t], L, mid, l, r);
        if (r > mid)
            res += getcnt(rch[s], rch[t], mid + 1, R, l, r);
        return res;
    }

    long long getsum(int s, int t, int L, int R, int l, int r) // s,t为root[l],root[r]的根节点 中所有大小在[l,r]之间数字的和
    {
        if(r<L||R<l||l>r) return 0;
        if (l <= L && R <= r)
            return sum[t] - sum[s];
        long long res = 0;
        int mid = L+(int)(((long long)R-L)/2);
        if (l <= mid)
            res += getsum(lch[s], lch[t], L, mid, l, r);
        if (r > mid)
            res += getsum(rch[s], rch[t], mid + 1, R, l, r);
        return res;
    }
    int get_Kth_min_Sum(int s,int t,int l,int r,int k,int &nowsum,long long &ans){//return 第k小的值
        int ss = nowsum+cnt[t]-cnt[s];
        if (ss<k) {
            nowsum = ss;
            ans+=sum[t]-sum[s];
            return -1;
        }
        if (l == r){
            ans+=1LL*(k-nowsum)*l;
            return l;
        }
        int mid=l+(int)(((long long)r-l)/2);
        int pos = get_Kth_min_Sum(lch[s],lch[t],l,mid,k,nowsum,ans);
        if (pos != -1)return pos;
        return get_Kth_min_Sum(rch[s],rch[t],mid+1,r,k,nowsum,ans);
    }
    int get_Kth_max_Sum(int s,int t,int l,int r,int k,int &nowsum,long long &ans){//return 第k大的值
        int ss = nowsum+cnt[t]-cnt[s];
        if (ss<k) {
            nowsum = ss;
            ans+=sum[t]-sum[s];
            return -1;
        }
        if (l == r){
            ans+=1LL*(k-nowsum)*l;
            return l;
        }
        int mid=l+(int)(((long long)r-l)/2);
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
        int mid=l+(int)(((long long)r-l)/2);
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
        int mid=l+(int)(((long long)r-l)/2);
        int pos=get_lower(rch[s],rch[t],mid+1,r,x);
        if(pos!=-1)return pos;
        return get_lower(lch[s],lch[t],l,mid,x);
    }

    int getcnt(int l,int r,int low,int high) {
        return getcnt(root[l-1],root[r],lo,hi,low,high);
    }
    long long getsum(int l,int r,int low,int high) { return getsum(root[l-1],root[r],lo,hi,low,high); }
    // 返回{第k小/大值,前min(k,区间大小)项的和}；不存在第k项时值为-1。
    pair<int,long long> kth_min(int l,int r,int k) {
        assert(k>=1); int used=0; long long value=0;
        int key=get_Kth_min_Sum(root[l-1],root[r],lo,hi,k,used,value); return {key,value};
    }
    pair<int,long long> kth_max(int l,int r,int k) {
        assert(k>=1); int used=0; long long value=0;
        int key=get_Kth_max_Sum(root[l-1],root[r],lo,hi,k,used,value); return {key,value};
    }
    int get_upper(int l,int r,int x) { return get_upper(root[l-1],root[r],lo,hi,x); }
    int get_lower(int l,int r,int x) { return get_lower(root[l-1],root[r],lo,hi,x); }
};
