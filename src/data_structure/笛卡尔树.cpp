const int maxn=2e5+10;
vector<int> ve[maxn];
int a[maxn];
int n;
int build(){
    int top=0;
    vector<int> Stack(n+1,0);
    for(int i=0;i<=n;i++){
        ve[i].clear();
        ve[i].resize(2,-1);
    }
	Stack[++top]=1;
	for(int i=2;i<=n;i++){
		while(top&&a[Stack[top]]>=a[i])top--;
		if(!top)ve[i][0]=Stack[top+1];
		else ve[i][0]=ve[Stack[top]][1],ve[Stack[top]][1]=i;
		Stack[++top]=i;
	}
    return Stack[1]; 
}