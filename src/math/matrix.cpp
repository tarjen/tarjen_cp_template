#include <bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
typedef long long ll;
void add(int &x,int y){
    if((x+=y)>=mod)x-=mod;
}
void del(int &x,int y){
    if((x-=y)<0)x+=mod;
}
int ksm(int x,int k){
    int res=1;
    while(k){
        if(k&1)res=(ll)res*x%mod;
        x=(ll)x*x%mod;
        k/=2;
    }
    return res;
}
int ny(int x){
    return ksm(x,mod-2);
}
const int N=310;
struct Matrix{
    int n;
    int a[N][N];
    Matrix(){}
    Matrix(int _n){
        n=_n;
        memset(a,0,sizeof(a));
    }
    int det(){
        int ans=1;bool tr=0;
        for (int j=0;j<n;j++){
            for (int i=j;i<n;i++)
            if (a[i][j]){
                if (i!=j){
                    swap(a[i],a[j]);
                    tr=!tr;
                }
                break;
            }
            if (a[j][j]==0)return 0;
            ans=(ll)ans*a[j][j]%mod;
            int t=ny(a[j][j]);
            for (int k=j;k<n;k++)a[j][k]=(ll)t*a[j][k]%mod;
            for (int i=j+1;i<n;i++){
                t=0;del(t,a[i][j]);
                for (int k=j;k<n;k++)
                    add(a[i][k],(ll)t*a[j][k]%mod);
            }
        }
        return tr? (mod-ans)%mod : ans;
    }
};
Matrix operator*(Matrix a, Matrix b) {
    Matrix c(a.n);
    for(int i=0;i<c.n;i++){
        for(int j=0;j<c.n;j++){
            for(int k=0;k<c.n;k++)add(c.a[i][k],(ll)a.a[i][j]*b.a[j][k]%mod);
        }
    }
    return c;
}
Matrix ksm(Matrix x,int k){
    Matrix res;
    res.n=x.n;memset(res.a,0,sizeof(res.a));
    for(int i=0;i<res.n;i++)res.a[i][i]=1;
    while(k){
        if(k&1)res=res*x;
        x=x*x;
        k/=2;
    }
    return res;
}