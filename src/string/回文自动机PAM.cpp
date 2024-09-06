#include<bits/stdc++.h>
using namespace std; 
const int N=2e6+10; 
struct PAM_Trie
{
	int ch[26]; 
	int fail,len,num; 
}; 
struct PAM
{
	PAM_Trie b[N]; 
	int n,length,last,cnt; 
	char s[N]; 
	PAM()
	{
		b[0].len = 0; b[1].len = -1; 
		b[0].fail = 1; b[1].fail = 0; 
		last = 0; 
		cnt = 1; 
	}
	int get_fail(int x)
	{ 
		while(s[n-b[x].len-1]!=s[n])
		{
			x=b[x].fail; 
		}
		return x; 
	}
	void insert()
	{
		int p=get_fail(last); 
		if(!b[p].ch[s[n]-'a'])
		{
			b[++cnt].len=b[p].len+2; 
			int tmp=get_fail(b[p].fail); 
			b[cnt].fail=b[tmp].ch[s[n]-'a']; 
			b[cnt].num=b[b[cnt].fail].num+1; 
			b[p].ch[s[n]-'a']=cnt; 
		}
		last=b[p].ch[s[n]-'a']; 
		cout<<last<<"\n";
		//如果要统计出现次数 f[last]++;
	}
	void init()
	{
		length=strlen(s+1);
		for(n=1;n<=length;n++)
		{
			insert(); 
		}                                                               
	}
}pa; 
int main()
{
	scanf("%s",pa.s+1);
	pa.init(); 
	return 0; 
}