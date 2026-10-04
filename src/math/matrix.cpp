// 0base方阵；Matrix a(n,mod); a.a[i][j]存0..mod-1；a.pow(k)或ksm(a,k)。
#include <bits/stdc++.h>
using namespace std;

struct Matrix {
    int n,mod;
    vector<vector<int>> a;
    explicit Matrix(int n=0,int mod=1000000007): n(n),mod(mod),a(n,vector<int>(n)) { assert(mod>0); }
    static Matrix identity(int n,int mod=1000000007) {
        Matrix r(n,mod); for(int i=0;i<n;i++) r.a[i][i]=1%mod; return r;
    }
    Matrix operator*(const Matrix& b) const {
        assert(n==b.n&&mod==b.mod); Matrix c(n,mod);
        for(int i=0;i<n;i++) for(int k=0;k<n;k++) for(int j=0;j<n;j++)
            c.a[i][j]=(c.a[i][j]+1LL*a[i][k]*b.a[k][j])%mod;
        return c;
    }
    Matrix pow(long long k) const {
        assert(k>=0); Matrix x=*this,r=identity(n,mod);
        for(;k;k>>=1,x=x*x) if(k&1) r=r*x;
        return r;
    }
    // 行列式需要质数模数；在工作副本上消元，不修改原矩阵。
    int det() const {
        auto work=a;
        long long ans=1%mod;
        auto inverse=[&](int x) {
            long long value=x,result=1;
            for(int k=mod-2;k;k>>=1,value=value*value%mod) if(k&1) result=result*value%mod;
            return result;
        };
        for(int col=0;col<n;col++) {
            int row=col; while(row<n&&!work[row][col]) row++;
            if(row==n) return 0;
            if(row!=col) swap(work[row],work[col]),ans=(mod-ans)%mod;
            ans=ans*work[col][col]%mod;
            long long inv=inverse(work[col][col]);
            for(int i=col+1;i<n;i++) {
                long long factor=work[i][col]*inv%mod;
                for(int j=col;j<n;j++) work[i][j]=(work[i][j]-factor*work[col][j]%mod+mod)%mod;
            }
        }
        return ans;
    }
};
Matrix ksm(const Matrix& x,long long k) { return x.pow(k); }
