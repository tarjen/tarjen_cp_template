#include <bits/stdc++.h>
using namespace std;
template <typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> p) {
    out << "(" << p.first << "," << p.second << ")";
    return out;
}
template <typename T1, typename T2, typename T3>
ostream& operator<<(ostream& out, tuple<T1, T2, T3> p) {
    out << "(" << get<0>(p) << "," << get<1>(p) << "," << get<2>(p) << ")";
    return out;
}
template <typename T>
ostream& operator<<(ostream& out, vector<T> v) {
    out << "[";
    if (!v.empty()) out << v[0];
    for (int i = 1; i < (int)v.size(); i++) out << "," << v[i];
    out << "]";
    return out;
}
template <typename T>
ostream& operator<<(ostream& out, set<T> s) {
    out << vector<T>(s.begin(), s.end());
    return out;
}
template <typename T>
ostream& operator<<(ostream& out, multiset<T> s) {
    out << vector<T>(s.begin(), s.end());
    return out;
}
template <typename T1, typename T2>
ostream& operator<<(ostream& out, map<T1, T2> s) {
    out << vector<pair<T1, T2>>(s.begin(), s.end());
    return out;
}

template <typename T1, typename T2>
istream& operator>>(istream& in, pair<T1, T2>& p) {
    in >> p.first >> p.second;
    return in;
}
template <typename T>
istream& operator>>(istream& in, vector<T>& v) {
    for (int i = 0; i < (int)v.size(); i++) in >> v[i];
    return in;
}

typedef long long ll;
const int mod = 998244353;
void add(int& x, int y) {
    if ((x += y) >= mod) x -= mod;
}
void del(int& x, int y) {
    if ((x -= y) < 0) x += mod;
}

template <typename T>
int gmax(T& x, T y) {
    if (y > x) {
        x = y;
        return 1;
    }
    return 0;
}

template <typename T>
int gmin(T& x, T y) {
    if (y < x) {
        x = y;
        return 1;
    }
    return 0;
}

int solve() {}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) cout << solve() << "\n";
    return 0;
}