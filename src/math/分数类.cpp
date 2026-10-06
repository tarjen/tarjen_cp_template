// 原实现：用分子 x、分母 y 表示分数，运算后约分。
// 用法：需提供标准库头文件、using namespace std; 和 using ll = long long;。
// lf a{1,2}, b{1,3}; auto c = a+b;  // 5/6。
// 分母须非零；保留原实现，交叉乘法和约分需注意整数范围。
struct lf{
    ll x=0,y=1;
    lf init(){
        if(y<0){
            y=-y,x=-x;
        }
        int g=abs(__gcd(x,y));
        return {x/g,y/g};
    }
    bool operator==(lf a) const {return x*a.y==y*a.x;}
    bool operator<(lf a) const {return x*a.y<y*a.x;}
    bool operator>(lf a) const {return !(*this<a || *this==a);}
    bool operator>=(lf a) const {return !(*this<a);}
    bool operator<=(lf a) const {return !(*this>a);}
    bool operator!=(lf a) const {return !(*this==a);}
    lf operator+( lf a) const {return lf{x*a.y+a.x*y,y*a.y}.init();}
    lf operator-( lf a) const {return lf{x*a.y-a.x*y,y*a.y}.init();}
    lf operator*( lf a) const {return lf{x*a.x,y*a.y}.init();}
    lf operator/( lf a) const {
        lf p{x*a.y,y*a.x};
        assert(a.x!=0);
        if(p.y<0){
            p.x=-p.x;
            p.y=-p.y;
        }
        return p.init();
    }
};