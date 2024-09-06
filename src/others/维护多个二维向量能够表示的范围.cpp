int gcd(int x,int y){
    if(y==0)return x;
    else return gcd(y,x%y);
}
struct vec{
    int a00,a01,a11;
    void clear(){
        a00=a01=a11=0;
    }
    void insert(int x,int y){
        while(x!=0){
            int t=a00/x;
            a00-=x*t;
            a01-=y*t;
            swap(a00,x);
            swap(a01,y);
        }
        a11=gcd(a11,abs(y));
        if(a11!=0)a01%=a11;
    }
    bool query(int x,int y){
        if(x!=0){
            if(a00==0||x%a00!=0)return false;
            int t=x/a00;
            y-=a01*t;
        }
        if(y==0){
            return true;
        }
        else return a11!=0&&y%a11==0;
    }
};