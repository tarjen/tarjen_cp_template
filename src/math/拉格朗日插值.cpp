#define int long long
const int N=1e6+10,mod=998244353;
int ksm(int a,int n,int m=mod){int s=1;while(n){if(n&1) s=s*a%m;a=a*a%m;n>>=1;}return s;}
int fac[N+5],facinv[N+5],inv[N+5];
struct LR{
	int Inv(int n){return ksm(n,mod-2);}
	void init(){	//预处理阶乘和阶乘逆元,逆元.
		fac[0]=inv[0]=inv[1]=1;
        for(int i=1;i<=N;i++) 
            fac[i]=fac[i-1]*i%mod;
		facinv[N]=Inv(fac[N]);
		for(int i=N-1;~i;i--) 
            facinv[i]=facinv[i+1]*(i+1)%mod;
		for(int i=2;i<N+5;i++)
			inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	}
	int cal(vector<int>&x,vector<int>&y,int k){	//离散点n个点[0,n-1] x[i],y[i] 插f(k)
        int n=x.size();
		int s=0;
        for(int i=0;i<n;i++)if(x[i]==k)return y[i];
		for(int i=0;i<n;i++){
			int p=y[i]%mod,q=1;
			for(int j=0;j<n;j++){
				if(i==j) continue;
				p=p*((k-x[j])%mod+mod)%mod;
				q=q*((x[i]-x[j])%mod+mod)%mod;
			}
			s=(s+p*Inv(q)%mod)%mod;
		}return (s%mod+mod)%mod;
	}
	int inpo(vector<int>&f,int x){	//给定 连续i属于[0,n] f(i) 拉插f(x)
        int n=f.size()-1;
        if(x>=0&&x<=n)return f[x];
		int p,s=0;
        vector<int>pre(n+1),suf(n+1);
        pre[0]=x-0;
        for(int i=1;i<=n;i++)pre[i]=pre[i-1]*(x-i)%mod;
        suf[n]=x-n;
        for(int i=n-1;i>=0;i--)suf[i]=suf[i+1]*(x-i)%mod;
		for(int i=0;i<=n;i++){
			p=facinv[n-i]%mod*facinv[i]%mod;
            if(i>0)p=p*pre[i-1]%mod;
            if(i<n)p=p*suf[i+1]%mod;
			if((n-i)&1)  s=(s-p*f[i]%mod+mod)%mod;
			else s=(s+p*f[i]%mod)%mod;
		}
		return (s%mod+mod)%mod;
	}
}sol;