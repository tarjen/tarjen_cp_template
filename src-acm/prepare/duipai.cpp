// 手抄版：沿用原算法与类封装；//? 标记为按需抄写。
#include <bits/stdc++.h>
using namespace std;
int main() {
    int T = 0;
    while (T <= 100000) {
        cout << "T=" << ++T << "\n";
        system("testin.exe > data.txt");
        system("abiaocheng.exe < data.txt > biaoda.txt");
        system("nedtest.exe < data.txt > aatest.txt");
        if (system("fc aatest.txt biaoda.txt")) {
            cout << "WA\n";
            return 0;
        }
    }
}
