const int N = 3000;
typedef unsigned long long ull;

int lim = N / 64 + 3;
struct Bitset {
    ull v[N / 64 + 5];
    void init() {
        memset(v, 0, sizeof(v));
        return;
    }
    void add(int x) {
        v[x >> 6] |= (1ull << (x & 63));
        return;
    }
    void shift1() {
        int lst = 0;
        for (int i = 0; i <= lim; i++) {
            int cur = v[i] >> 63;
            v[i] <<= 1;
            v[i] |= lst;
            lst = cur;
        }
        return;
    }
    int count() {
        int res = 0;
        for (int i = 0; i <= lim; i++) res += __builtin_popcountll(v[i]);
        return res;
    }
    Bitset operator|(const Bitset &x) const {
        Bitset res;
        for (int i = 0; i <= lim; i++) res.v[i] = v[i] | x.v[i];
        return res;
    }
    Bitset operator&(const Bitset &x) const {
        Bitset res;
        for (int i = 0; i <= lim; i++) res.v[i] = v[i] & x.v[i];
        return res;
    }
    Bitset operator^(const Bitset &x) const {
        Bitset res;
        for (int i = 0; i <= lim; i++) res.v[i] = v[i] ^ x.v[i];
        return res;
    }
    Bitset operator-(const Bitset &x) const {
        Bitset res;
        ull lst = 0;
        for (int i = 0; i <= lim; i++) {
            ull cur = (v[i] < x.v[i] + lst);
            res.v[i] = v[i] - x.v[i] - lst;
            lst = cur;
        }
        return res;
    }
}