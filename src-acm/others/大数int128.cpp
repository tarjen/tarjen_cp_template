// 用法：
// __int128 a, b; cin >> a >> b; cout << a + b << '\n';
// 支持正负数和前导 +；输入须合法且在 [-2^127,2^127-1] 范围内。
// 不要将 __int128 隐式转为 long long 后输出。
#include <bits/stdc++.h>
using namespace std;

istream& operator>>(istream& in, __int128& num) {
    string s;
    if (!(in >> s)) return in;
    bool neg = s[0] == '-';
    int i = s[0] == '-' || s[0] == '+';
    num = 0;
    for (; i < (int)s.size(); i++) num = num * 10 - (s[i] - '0');
    if (!neg) num = -num;
    return in;
}

ostream& operator<<(ostream& out, __int128 num) {
    string s;
    bool neg = num < 0;
    do {
        int d = num % 10;
        s.push_back(char('0' + (d < 0 ? -d : d)));
        num /= 10;
    } while (num);
    if (neg) s.push_back('-');
    reverse(s.begin(), s.end());
    out << s;
    return out;
}
