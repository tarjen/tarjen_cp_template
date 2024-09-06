struct LinearBasis
{
    static const int maxbase = 35;
    bool flag = false;
    ll a[maxbase + 1];
    int tot;
    LinearBasis()
    {
        memset(a, 0, sizeof a);
        tot=0;
    }
    LinearBasis(ll *x, int n)
    {
        LinearBasis();
        build(x, n); 
    }
    void build(ll *x, int n)
    {
        for(int i = 1; i <= n; ++i)
            insert(x[i]);
    }
    void clear()
    {
        memset(a, 0, sizeof a);
    }
    bool insert(ll t)
    {
        //暴力插入一个数，维护的是一个上三角型的线性基矩阵，时间复杂度低，当待插入元素能插入时，返回true
        for(int i = maxbase; i >= 0; --i)
        {
            if(t & (1ll << i))
            {
                if(!a[i])
                {
                    a[i] = t;//这里表示插入成功
                    break;
                }
                t ^= a[i];
            }
        }
        if(t == 0)flag = true;
        return t;
    }
    bool query(ll t)
    {
        // 询问t是否可以被当前线性基表示，不插入
        if(t > queryMax())return false;
        if(t == 0)return true;
        for(int i = maxbase; i >= 0; --i)
        {
            if(t & (1ll << i))
            {
                if(!a[i])
                {
                    return false;
                }
                t ^= a[i];
            }
        }
        return true;
    }
    void Insert(ll t)
    {
        //插入一个线性基，利用高斯消元法维护一个对角矩阵
        for(int i = maxbase; i >= 0; --i)
        {
            if(t >> i & 1)
            {
                if(a[i])t ^= a[i];
                else
                {
                    a[i] = t;
                    for(int j = i - 1; j >= 0; --j)if(a[j] && (a[i] >> j & 1))a[i] ^= a[j];
                    for(int j = i + 1; j <= maxbase; ++j)if(a[j] >> i & 1)a[j] ^= a[i];
                    break;
                }
            }
        }
    }
    LinearBasis merge(const LinearBasis &l1, const LinearBasis &l2)
    {
        // 得到两个线性基的并
        LinearBasis ret = l1;
        for(int i = maxbase; i >= 0; --i)
            if(l2.a[i])
                ret.insert(l2.a[i]);
        return ret;
    }
    LinearBasis intersection(const LinearBasis &l1, const LinearBasis &l2)
    {
        //得到两个线性基的交
        LinearBasis all, ret, full;
        ret.clear();
        for(int i = maxbase; i >= 0; --i)
        {
            all.a[i] = l1.a[i];
            full.a[i] = 1ll << i;
        }
        for(int i = maxbase; i >= 0; --i)
        {
            if(l2.a[i])
            {
                ll v = l2.a[i], k = 0;
                bool flag = true;
                for(int j = maxbase; j >= 0; --j)
                {
                    if(v & (1ll << j))
                    {
                        if(all.a[j])
                        {
                            v ^= all.a[j];
                            k ^= full.a[j];
                        }
                        else
                        {
                            // l2's basis is not in l1's;
                            flag = false;
                            all.a[j] = v;
                            full.a[j] = k;
                            break;
                        }
                    }
                }
                if(flag)
                {
                    ll v = 0; // get intersection by k;
                    for(int j = maxbase; j >= 0; --j)
                    {
                        if(k & (1ll << j))
                        {
                            v ^= l1.a[j];
                        }
                    }
                    ret.insert(v);  
                }
            }
        }
        return ret;
    }
    //询问最值
    ll queryMax()
    {
        ll ret = 0;
        for(int i = maxbase; i >= 0; --i)
            if((ret ^ a[i]) > ret)
                ret ^= a[i];
        return ret;
    }
    ll queryMin()
    {
        for(int i = 0; i <= maxbase; ++i)
            if(a[i])
                return a[i];
        return 0;
    }
    ll Kth_Max(ll k)
    {
        ll res=0;
        for(int i=62;i>=0;i--)
            if (k&(1LL<<i)) res^=a[i];
        return res;
    }
};
