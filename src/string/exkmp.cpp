// EXKMP ex(text,pattern); next/extend为1base，输入普通string。
#include <bits/stdc++.h>
using namespace std;

struct EXKMP {
    string S,T;
    vector<int> next,extend;
    EXKMP(const string& text,const string& pattern): S(" "+text),T(" "+pattern),
        next(pattern.size()+1),extend(text.size()+1) {
        Get_Next(); ExKMP();
    }
    void Get_Next() {
        int m=T.size()-1;
        if(!m) return;
        next[1]=m;
        for(int i=2,l=0,r=0;i<=m;i++) {
            if(i<=r) next[i]=min(r-i+1,next[i-l+1]);
            while(i+next[i]<=m&&T[1+next[i]]==T[i+next[i]]) next[i]++;
            if(i+next[i]-1>r) l=i,r=i+next[i]-1;
        }
    }
    void ExKMP() {
        fill(extend.begin(),extend.end(),0);
        int n=S.size()-1,m=T.size()-1;
        for(int i=1,l=0,r=0;i<=n;i++) {
            if(i<=r) extend[i]=min(r-i+1,next[i-l+1]);
            while(extend[i]<m&&i+extend[i]<=n&&T[1+extend[i]]==S[i+extend[i]]) extend[i]++;
            if(i+extend[i]-1>r) l=i,r=i+extend[i]-1;
        }
    }
};
