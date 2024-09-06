#define int long long
int mul(int a,int b,int mod){//O(1)取模快速乘，不会爆long long
	return (a*b-(int)((long double)a/mod*b)*mod+mod)%mod;
}
int exgcd(int a, int b, int& x, int& y){
	if(!b){
		x = 1, y = 0;
		return a;
	}
	int d = exgcd(b,a%b,y,x);
	y -= a/b*x;
	return d;
}
int solve(int n,vector<int>&mo,vector<int>&res){
	int a1,m1;
    a1=res[0],m1=mo[0];
	bool ok = 1;
	for(int i=1;i<n;i++){
		int a2,m2,k1,k2;
        m2=mo[i],a2=res[i];
		int d = exgcd(m1,m2,k1,k2);
		if((a2-a1)%d) ok = 0;
		else{
			k1=mul(k1,(a2-a1)/d,m2/d);//这个地方必须要用取模快速乘
			a1=a1+k1*m1;
			m1=abs(m1/d*m2);
		}
	}
	if(ok)return (a1%m1+m1)%m1;
    else return -1;
}