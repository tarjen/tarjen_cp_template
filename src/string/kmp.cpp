// KMP k(pattern); k.find(text); nxt及返回位置为1base，输入普通string。
#include <bits/stdc++.h>
using namespace std;

struct KMP {
    int n;
    string s;
    vector<int> nxt;
    explicit KMP(const string& pattern): n(pattern.size()),s(" "+pattern),nxt(n+1) {
        for(int i=2,j=0;i<=n;i++) {
            while(j&&s[i]!=s[j+1]) j=nxt[j];
            if(s[i]==s[j+1]) j++;
            nxt[i]=j;
        }
    }
    // 返回匹配起点（1base），包含重叠匹配；空模式匹配所有n+1个边界。
    vector<int> find(const string& text) const {
        vector<int> ans;
        if(!n) { ans.resize(text.size()+1); iota(ans.begin(),ans.end(),1); return ans; }
        for(int i=0,j=0;i<(int)text.size();i++) {
            while(j&&text[i]!=s[j+1]) j=nxt[j];
            if(text[i]==s[j+1]) j++;
            if(j==n) { ans.push_back(i-n+2); j=nxt[j]; }
        }
        return ans;
    }
};
