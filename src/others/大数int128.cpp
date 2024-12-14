#include <bits/stdc++.h>
using namespace std;
inline __int128 read() {
    __int128 x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
inline void write(__int128 x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

istream& operator>>(istream& in, __int128& num) {
    string s;
    in >> s;
    num = 0;
    for (auto it : s) num = num * 10 + it - '0';
    return in;
}

ostream& operator<<(ostream& out, __int128 num) {
    string s;
    do {
        s.push_back(char(num % 10 + '0'));
        num /= 10;
    } while (num > 0);
    reverse(s.begin(), s.end());
    out << s;
    return out;
}