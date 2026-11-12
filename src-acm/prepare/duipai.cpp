// 手抄版：保留说明与用法，适度压行；//? 为按需代码，调用可选接口前需恢复对应函数组。
#include <bits/stdc++.h>
using namespace std;
int main() {
    int T = 0;
    while (T <= 100000) {
        cout << "T=" << ++T << "\n";
        system("testin.exe > data.txt"); system("abiaocheng.exe < data.txt > biaoda.txt");
        system("nedtest.exe < data.txt > aatest.txt");
        if (system("fc aatest.txt biaoda.txt")) {
            cout << "WA\n";
            return 0;
        }
    }
}
