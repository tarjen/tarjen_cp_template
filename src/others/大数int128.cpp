// 用法：
// __int128 a = read(), b = read();  // 从标准输入读取两个有符号整数。
// write(a + b);
// putchar(10);
// read/write 使用 getchar/putchar；cin/cout 流运算符也支持正负数。
// 输入须为合法十进制整数，范围 [-2^127,2^127-1]；支持前导 + 和 -。
// 关闭流同步后，同一方向的输入或输出不要混用 C 与 C++ 接口。
// 不要将 __int128 隐式转为 long long 后输出。
#include <bits/stdc++.h>
using namespace std;
inline __int128 read() {
    __int128 x = 0;
    bool neg = false;
    int ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == EOF) return 0;
        if (ch == '-') neg = true;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 - (ch - '0');  // 按负数累积，最小负数也不会溢出。
        ch = getchar();
    }
    return neg ? x : -x;
}
inline void write(__int128 x) {
    if (x < 0) putchar('-');
    char s[40];
    int n = 0;
    do {
        int d = x % 10;  // 仅对一位数取绝对值，避免对最小负数取反。
        s[n++] = char('0' + (d < 0 ? -d : d));
        x /= 10;
    } while (x);
    while (n) putchar(s[--n]);
}

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
// 两个整数相加的调用示例。
int main() {
    __int128 a = read();
    __int128 b = read();
    write(a + b);
    return 0;
}
