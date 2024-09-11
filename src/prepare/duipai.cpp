int t=10000,j=0;
while(t) 
{
    cout<<"test:"<<++j<<"\n";
    t--;
    system("testin.exe > data.txt");
    system("abiaocheng.exe < data.txt > biaoda.txt");
    system("nedtest.exe < data.txt > aatest.txt");
    if(system("fc aatest.txt biaoda.txt")){
        cout<<"error"<<"\n";
        break;
    }
}
if(t==0) cout<<"no error"<<endl;
//system("pause");
return 0;