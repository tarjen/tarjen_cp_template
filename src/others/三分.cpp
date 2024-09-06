double f(double x){
    //something
}
const double eps=1e-8;
double sanfen(double l, double r){
    double mid,midr,ans;
    while (fabs(r-l)>eps) {
        mid=(l+r)/2;
        midr=(mid+r)/2;
        if(f(mid) < f(midr)) l=mid; else r=midr;   //求最大值
    } 
    ans=f(l);
    return ans;
}