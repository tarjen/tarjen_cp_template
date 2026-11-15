// 两套 I/O 分开执行，避免关闭流同步后混用输入缓冲。
#include <bits/stdc++.h>
using namespace std;
#define main int128_example_main
#ifdef ACM_VARIANT
#include "../src-acm/others/大数int128.cpp"
#else
#include "../src/others/大数int128.cpp"
#endif
#undef main

int main(int argc, char** argv) {
    if (argc > 1 && string(argv[1]) == "stdio") {
        int n;
        if (scanf("%d", &n) != 1) return 1;
        while (n--) {
            write(read());
            putchar('\n');
        }
    } else {
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
}
