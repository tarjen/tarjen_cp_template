int lim = N / 64 + 3;
struct Bitset {
  ull v[N / 64 + 5];
  void init() {
    memset(v, 0, sizeof(v));
    return;
  }
  bool getBit(int pos) const { return (v[pos >> 6] >> (pos & 63)) & 1; }
  void setBit(int pos, bool val) {
    if (val) {
      v[pos >> 6] |= (1ull << (pos & 63));
    } else {
      v[pos >> 6] &= ~(1ull << (pos & 63));
    }
  }
  int count() {
    int res = 0;
    for (int i = 0; i <= lim; i++) res += __builtin_popcountll(v[i]);
    return res;
  }
  Bitset operator<<(const int t) const {
    Bitset ret;
    ret.init();
    ull last = 0;
    int high = t >> 6, low = t & 63;
    for (int i = 0; i + high <= lim; i++) {
      ret.v[i + high] = last | (v[i] << low);
      if (low && i < lim)
        last = v[i] >> (64 - low);
      else
        last = 0;
    }
    return ret;
  }
  Bitset operator>>(const int t) const {
    Bitset ret;
    ret.init();
    ull last = 0;
    int high = t >> 6, low = t & 63;
    for (int i = lim; i >= high; i--) {
      ret.v[i - high] = last | (v[i] >> low);
      if (low && i > 0)
        last = v[i] << (64 - low);
      else
        last = 0;
    }
    return ret;
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
};
