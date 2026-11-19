// 验证有符号 __int128 流输入输出。
#include <bits/stdc++.h>
using namespace std;
#ifdef ACM_VARIANT
#include "../src-acm/others/大数int128.cpp"
#else
#include "../src/others/大数int128.cpp"
#endif

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    while (n--) {
        __int128 x;
        cin >> x;
        cout << x << '\n';
    }
    // 提取失败须保留原值，并保留流的失败状态。
    __int128 unchanged = -12;
    cin >> unchanged;
    assert(cin.fail() && unchanged == -12);
}
