int exgcd(int a, int b, int &x, int &y){//求ax+by=gcd(a,b)  !(a==0&&b==0)
    if(b==0){
        x=1;
        y=0;
        return a;
    }
    int d=exgcd(b,a%b,x,y);
    int t=x;
    x=y;
    y=t-(a/b)*y;
    return d;
}