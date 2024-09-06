const int maxn=1e5+10;
struct Persistent_Trie
{
    int ch[maxn][2],tot,sum[maxn];
    void clear()
    {
        tot=0;
        return;
    }
    void cpy(int from,int to)
    {
        ch[to][0]=ch[from][0];
        ch[to][1]=ch[from][1];
        sum[to]=sum[from];
        return;
    }
    void insert(int &root,int old,int num,int nowbit)
    {
        root=++tot;
        cpy(old,root);
        sum[root]++;
        if(nowbit==-1)return;
        if(num&(1<<nowbit))
        {
            insert(ch[root][1],ch[root][1],num,nowbit-1);
        }
        else
        {
            insert(ch[root][0],ch[root][0],num,nowbit-1);
        }
    }
    int query(int s,int t,int x)
    {
        int ans=0;
        for(int i=30;i>=0;--i)
        {
            if(sum[ch[t][!(x&(1<<i))]]-sum[ch[s][!(x&(1<<i))]])
            {
                t=ch[t][!(x&(1<<i))];
                s=ch[s][!(x&(1<<i))];
                ans|=(1<<i);
            }
            else
            {
                t=ch[t][!!(x&(1<<i))];
                s=ch[s][!!(x&(1<<i))];
            }
        }
        return ans;
    }
};