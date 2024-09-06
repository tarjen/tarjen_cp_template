const long long mod =1e18;
namespace polynomial {
    typedef complex<long double> cplx;
    const long double pi = acos((long double)-1.0);
    const int len = 15, mask = (1 << len) - 1;
    struct UnitRoot {
        static vector<cplx> w;
        static vector<cplx> get_root(int n) {
            n = 1 << 32 - __builtin_clz(n);
            if (n > w.size()) {
                w.resize(n);
                for (int i = 0; i < n; i++)
                    w[i] = cplx(cos(2 * i * pi / n), sin(2 * i * pi / n));
            }
            int m = w.size() / n;
            vector<cplx> res(n);
            for (int i = 0, j = 0; i < n; i++, j += m) res[i] = w[j];
            return res;
        }
    };
    vector<cplx> UnitRoot::w;
 
    void fft(vector<cplx> &p, const vector<cplx> &w) {
        int n = w.size();
        for (int i = 1, j = 0; i < n - 1; ++i) {
            int s = n;
            do {
                s >>= 1;
                j ^= s;
            } while (~j & s);
            if (i < j) {
                swap(p[i], p[j]);
            }
        }
        for (int d = 0; (1 << d) < n; ++d) {
            int m = 1 << d, m2 = m * 2, rm = n >> (d + 1);
            for (int i = 0; i < n; i += m2) {
                for (int j = 0; j < m; ++j) {
                    auto &p1 = p[i + j + m], &p2 = p[i + j];
                    auto t = w[rm * j] * p1;
                    p1 = p2 - t;
                    p2 = p2 + t;
                }
            }
        }
    }
    vector<long long> conv(const vector<long long> &a,const vector<long long> &b) {
        vector<cplx> w = UnitRoot::get_root(a.size() + b.size() - 1);
        int n = w.size();
        vector<cplx> A(n), B(n), C(n), D(n);
        for (int i = 0; i < a.size(); ++i) A[i] = cplx(a[i] >> len, a[i] & mask);
        for (int i = 0; i < b.size(); ++i) B[i] = cplx(b[i] >> len, b[i] & mask);
        fft(A, w), fft(B, w);
        for (int i = 0; i < n; ++i) {
            int j = (n - i) % n;
            cplx da = (A[i] - conj(A[j])) * cplx(0, -0.5),db = (A[i] + conj(A[j])) * cplx(0.5, 0),dc = (B[i] - conj(B[j])) * cplx(0, -0.5),dd = (B[i] + conj(B[j])) * cplx(0.5, 0);
            C[j] = da * dd + da * dc * cplx(0, 1);D[j] = db * dd + db * dc * cplx(0, 1);
        }
        fft(C, w), fft(D, w);
        vector<long long> res(a.size() + b.size() - 1);
        for (int i = 0; i < res.size(); ++i) {
            long long da = (long long)(C[i].imag() / n + 0.5) % mod,db = (long long)(C[i].real() / n + 0.5) % mod,dc = (long long)(D[i].imag() / n + 0.5) % mod,dd = (long long)(D[i].real() / n + 0.5) % mod;
            res[i] = ((dd << (len * 2)) + ((db + dc) << len) + da) % mod;
        }
        return res;
    }
};
using namespace polynomial;