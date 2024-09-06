// 这里是 上凸 取min
// 上凸取max 二分的时候改变一下mid的变化方向
// 下凸取min 改变mid算贡献的符号
//min max 指的是求的是最大值 还是最小值
int solve(int mid){
    k=mid;
    function<void(int,int)> dfs = [&](int x,int h){
        info dp2[3];memset(dp2,0,sizeof(dp2));
        for(auto [it,w]:ve[x])if(it!=h){
            dfs(it,x);
            gmax(dp2[0],dp[x][0]+dp[it][0]);
            gmax(dp2[2],dp[x][0]+dp[it][1]);
            gmax(dp2[2],dp[x][2]+dp[it][0]);
            dp[x][0]=dp2[0];
            dp[x][1]=dp2[1];
            dp[x][2]=dp2[2];
        }
        dp[x][0]=dp2[2];
        dp[x][1]=dp2[0]+info{a[x]+k,1};
    };
    dfs(1,0);
    return dp[1][0].second;
}
signed main()
{
    int l=-sum-1000000000000ll,r=sum+1000000000000ll;
    int ans=1e18;
    while(l<=r){
        int mid=(l+r)/2ll;
        if(solve(mid)>=m){
            ans=dp[1][0].first-m*mid;
            r=mid-1;
        }
        else l=mid+1;
    }
    if(ans!=(int)1e18)cout<<ans<<"\n";
    else cout<<"Impossible\n";
    return 0;
}