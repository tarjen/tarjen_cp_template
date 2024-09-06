#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <unordered_map>

using namespace std;

typedef long long LL;

const int INF = 0x3f3f3f3f;

int a, b, p;
unordered_map<int, int> hs;

int exgcd(int a, int b, int &x, int &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

int BSGS(int a, int b, int p) {
    if (1 % p == b % p) return 0;
    int k = sqrt(p) + 1;
    hs.clear();
    for (int y = 0, r = b % p; y < k; y++) {
        hs[r] = y;
        r = (LL)r * a % p;
    }
    int ak = 1;
    for (int i = 1; i <= k; i++) ak = (LL)ak * a % p;
    for (int x = 1, l = ak; x <= k; x++) {
        if (hs.count(l)) return k * x - hs[l];
        l = (LL)l * ak % p;
    }
    return -INF;
}

int exBSGS(int a, int b, int p) {
    b = (b % p + p) % p;
    if (1 % p == b % p) return 0;
    int x, y;
    int d = exgcd(a, p, x, y);
    if (d > 1) {
        if (b % d) return -INF;
        exgcd(a / d, p / d, x, y);
        return exBSGS(a, (LL)b / d * x % (p / d), p / d) + 1;
    }
    return BSGS(a, b, p);
}

int main() {
    while (~scanf("%d%d%d", &a, &p, &b), a || b || p) {
        int res = exBSGS(a, b, p);
        if (res < 0) puts("No Solution");
        else printf("%d\n", res);
    }
    return 0;
}