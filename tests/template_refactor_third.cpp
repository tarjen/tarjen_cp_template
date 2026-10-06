#include <bits/stdc++.h>
using namespace std;
using ll = long long;
namespace dynamicseg {
#include "../src/data_structure/动态开点线段树.cpp"
}
namespace ptrie {
#include "../src/data_structure/可持久化01trie.cpp"
}
namespace chairman {
#include "../src/data_structure/主席树.cpp"
}
namespace persistent {
#include "../src/data_structure/可持久化线段树.cpp"
}
namespace lct {
#include "../src/data_structure/LCT维护联通性.cpp"
}
namespace treap {
#include "../src/data_structure/Splay.cpp"
}
namespace virtualtree {
#include "../src/data_structure/虚树xushu.cpp"
}
namespace comb {
#include "../src/math/组合数带模运算ca.cpp"
}
namespace comb2 {
#include "../src/math/组合数带模运算CA(ll).cpp"
}
namespace lagrange {
#include "../src/math/拉格朗日插值.cpp"
}
namespace primes {
#include "../src/math/线性筛质数.cpp"
}
namespace mobius {
#include "../src/math/mob莫比乌斯反演.cpp"
}
namespace matrix {
#include "../src/math/matrix.cpp"
}
namespace gauss {
#include "../src/math/高斯消元(浮点数).cpp"
}
namespace modgauss {
#include "../src/math/高斯消元(模意义).cpp"
}
namespace bitsetimpl {
#include "../src/others/bitset手写.cpp"
}
namespace bounded {
#include "../src/graph/带负环最小费用最大流.cpp"
}
namespace centroid {
#include "../src/data_structure/点分治.cpp"
}
namespace dominance {
#include "../src/data_structure/三维偏序cdq.cpp"
}
namespace mo {
#include "../src/data_structure/莫队mo.cpp"
}
namespace dynamic_scc {
#include "../src/graph/有向图动态加边缩点.cpp"
}
namespace min25impl {
#include "../src/math/min25(质数幂次和).cpp"
}
namespace dujiao {
#include "../src/math/杜教筛.cpp"
}
namespace primecounter {
#include "../src/math/Meissel-Lehmer(求1-n质数数量).cpp"
}
namespace recurrence {
#include "../src/math/线性递推.cpp"
}
namespace ancestor {
#include "../src/data_structure/树上k级祖先.cpp"
}
namespace mergeimpl {
#include "../src/data_structure/线段树合并.cpp"
}
uint64_t checks = 0;
#define CHECK(expr)                                                    \
    do {                                                               \
        ++checks;                                                      \
        if (!(expr)) {                                                 \
            cerr << "FAIL line " << __LINE__ << ": " << #expr << "\n"; \
            exit(1);                                                   \
        }                                                              \
    } while (0)
mt19937 rng(20261004);
int rnd(int l, int r) { return l + rng() % (r - l + 1); }

void test_persistence() {
    for (int trial = 0; trial < 100; trial++) {
        int n = rnd(1, 25);
        persistent::Persistent_SegmentTree t(n);
        vector<vector<ll>> versions(1, vector<ll>(n + 1));
        for (int q = 0; q < 100; q++) {
            int old = rnd(0, q), l = rnd(1, n), r = rnd(l, n);
            ll w = rnd(-100000000, 100000000);
            auto copy = versions[old];
            if (q % 3) {
                CHECK(t.append(old, l, r, w) == q + 1);
                for (int i = l; i <= r; i++) copy[i] += w;
            } else {
                int other = rnd(0, q), p = rnd(0, n);
                CHECK(t.splice(old, other, p) == q + 1);
                for (int i = p + 1; i <= n; i++) copy[i] = versions[other][i];
            }
            versions.push_back(copy);
            for (int i = 0; i <= q + 1; i++) {
                int x = rnd(1, n);
                CHECK(t.query(i, x) == versions[i][x]);
            }
        }
        ptrie::Persistent_Trie tr;
        chairman::Persistent_SegmentTree ct(0, 1000);
        vector<int> values(1);
        for (int i = 1; i <= 200; i++) {
            values.push_back(rnd(0, 1000));
            CHECK(tr.append(values.back()) == i);
            CHECK(ct.append(values.back()) == i);
        }
        for (int q = 0; q < 300; q++) {
            int l = rnd(1, 200), r = rnd(l, 200), x = rnd(0, 1023),
                low = rnd(0, 1000), high = rnd(low, 1000);
            vector<int> v(values.begin() + l, values.begin() + r + 1);
            sort(v.begin(), v.end());
            int best = 0, count = 0;
            ll sum = 0;
            for (int val : v) {
                best = max(best, val ^ x);
                if (low <= val && val <= high) count++, sum += val;
            }
            CHECK(tr.max_xor(l, r, x) == best);
            CHECK(ct.getcnt(l, r, low, high) == count);
            CHECK(ct.getsum(l, r, low, high) == sum);
            int k = rnd(1, (int)v.size() + 2);
            ll small = 0, large = 0;
            for (int i = 0; i < min(k, (int)v.size()); i++)
                small += v[i], large += v[v.size() - 1 - i];
            CHECK((ct.kth_min(l, r, k) ==
                   pair<int, ll>{k <= (int)v.size() ? v[k - 1] : -1, small}));
            CHECK((ct.kth_max(l, r, k) ==
                   pair<int, ll>{k <= (int)v.size() ? v[v.size() - k] : -1,
                                 large}));
            auto upper = lower_bound(v.begin(), v.end(), x),
                 lower = upper_bound(v.begin(), v.end(), x);
            CHECK(ct.get_upper(l, r, x) == (upper == v.end() ? -1 : *upper));
            CHECK(ct.get_lower(l, r, x) ==
                  (lower == v.begin() ? -1 : *prev(lower)));
        }
    }
    chairman::Persistent_SegmentTree large(1, 1000000000);
    for (int i = 0; i < 5; i++) large.append(1000000000);
    CHECK(large.getsum(1, 5, 1, 1000000000) == 5000000000LL);
    cout << "persistent trees / trie / version immutability OK\n";
}

void test_dynamic_segment() {
    for (int trial = 0; trial < 100; trial++) {
        int n = 30;
        dynamicseg::DynamicSegmentTree t(n), other(n);
        vector<ll> a(n + 1);
        for (int q = 0; q < 300; q++) {
            int x = rnd(1, n), l = rnd(1, n), r = rnd(l, n);
            ll delta = rnd(0, 50);
            if (q % 3)
                t.update(x, delta), a[x] += delta;
            else {
                ll expected = accumulate(a.begin() + l, a.begin() + r + 1, 0LL);
                CHECK(t.query(l, r) == expected);
                int separated = t.split(l, r);
                CHECK(t.query_root(separated, l, r) == expected);
                CHECK(t.query(l, r) == 0);
                t.root = t.merge(t.root, separated);
                CHECK(t.query(l, r) == expected);
            }
            ll up = rnd(0, 10000), prefix = 0;
            optional<int> expected;
            for (int i = 1; i <= n; i++)
                if ((prefix += a[i]) + i > up) {
                    expected = i;
                    break;
                }
            CHECK(t.query1(up) == expected);
            CHECK(other.query(1, n) == 0);
        }
    }
    dynamicseg::DynamicSegmentTree negative(-100, 100);
    negative.update(-1, 7);
    CHECK(negative.query(-5, 0) == 7);
    cout << "dynamic segment tree / split / merge OK\n";
}

vector<int> reach(const vector<vector<int>>& g, int start) {
    vector<int> vis(g.size()), todo{start};
    vis[start] = 1;
    for (int i = 0; i < (int)todo.size(); i++)
        for (int v : g[todo[i]])
            if (!vis[v]) vis[v] = 1, todo.push_back(v);
    return vis;
}
void test_dynamic_structures() {
    for (int trial = 0; trial < 100; trial++) {
        int n = 15;
        lct::LCT t(n), other(n);
        vector<vector<int>> g(n + 1);
        for (int q = 0; q < 300; q++) {
            int u = rnd(1, n), v = rnd(1, n);
            bool connected = reach(g, u)[v];
            if (q % 3 == 0 && u != v) {
                t.addedge(u, v);
                if (!connected) g[u].push_back(v), g[v].push_back(u);
            }
            if (q % 3 == 1 && u != v) {
                t.deledge(u, v);
                auto erase = [&](int a, int b) {
                    auto it = find(g[a].begin(), g[a].end(), b);
                    if (it != g[a].end()) g[a].erase(it);
                };
                erase(u, v);
                erase(v, u);
            }
            CHECK(t.query(u, v) == bool(reach(g, u)[v]));
            CHECK(other.query(u, v) == (u == v));
        }
        treap::Splay tr;
        multiset<int> data;
        for (int q = 0; q < 1000; q++) {
            int v = q % 50 == 0   ? INT_MIN
                    : q % 51 == 0 ? INT_MAX
                                  : rnd(-40, 40);
            if (q % 3)
                tr.insert(v), data.insert(v);
            else {
                tr.del(v);
                auto it = data.find(v);
                if (it != data.end()) data.erase(it);
            }
            CHECK(tr.siz[tr.r] == (int)data.size());
            CHECK(tr.queryrk(v) ==
                  distance(data.begin(), data.lower_bound(v)) + 1);
            auto p = data.lower_bound(v), s = data.upper_bound(v);
            optional<int> pred, succ;
            if (p != data.begin()) pred = *prev(p);
            if (s != data.end()) succ = *s;
            CHECK(tr.query_pre(v) == pred);
            CHECK(tr.query_suf(v) == succ);
            if (!data.empty()) {
                int k = rnd(1, data.size());
                CHECK(tr.querynum(k) == *next(data.begin(), k - 1));
            }
        }
    }
    cout << "LCT / Treap / extreme values OK\n";
}

void test_virtual_centroid_ancestor() {
    for (int trial = 0; trial < 120; trial++) {
        int n = rnd(1, 35), root = rnd(1, n);
        virtualtree::XS xs(n, root);
        centroid::CentroidDecomposition cd(n);
        vector<vector<pair<int, ll>>> g(n + 1);
        vector<int> parent(n + 1);
        for (int u = 2; u <= n; u++) {
            int v = rnd(1, u - 1);
            ll w = rnd(0, 100);
            parent[u] = v;
            xs.add(u, v, w);
            cd.addedge(u, v, w);
            g[u].push_back({v, w});
            g[v].push_back({u, w});
        }
        ancestor::KthAncestor anc(parent);
        xs.build();
        vector<vector<ll>> distance(n + 1, vector<ll>(n + 1));
        for (int s = 1; s <= n; s++) {
            vector<tuple<int, int, ll>> todo{{s, 0, 0}};
            for (int i = 0; i < (int)todo.size(); i++) {
                auto [u, p, d] = todo[i];
                distance[s][u] = d;
                for (auto [v, w] : g[u])
                    if (v != p) todo.push_back({v, u, d + w});
            }
            for (int k = 0; k <= n; k++) {
                int u = s;
                for (int i = 0; i < k && u; i++) u = parent[u];
                CHECK(anc.ask(s, k) == u);
            }
        }
        for (int q = 0; q < 30; q++) {
            vector<int> keys;
            for (int u = 1; u <= n; u++)
                if (rnd(0, 2) == 0) keys.push_back(u), keys.push_back(u);
            auto nodes = xs.build_virtual(keys);
            CHECK(!nodes.empty());
            vector<char> present(n + 1);
            for (int u : nodes) present[u] = 1;
            for (int u = 1; u <= n; u++) {
                CHECK(bool(xs.b[u]) ==
                      (find(keys.begin(), keys.end(), u) != keys.end()));
                if (!present[u]) CHECK(xs.ve2[u].empty());
            }
            int edge_count = 0;
            for (int u : nodes) edge_count += xs.ve2[u].size();
            CHECK(edge_count == 2 * ((int)nodes.size() - 1));
            for (int s : keys) {
                vector<tuple<int, int, ll>> todo{{s, 0, 0}};
                for (int i = 0; i < (int)todo.size(); i++) {
                    auto [u, p, d] = todo[i];
                    CHECK(distance[s][u] == d);
                    for (auto e : xs.ve2[u])
                        if (e.to != p) todo.push_back({e.to, u, d + e.len});
                }
                CHECK(todo.size() == nodes.size());
            }
        }
        vector<int> visited(n + 1);
        auto callback = [&](int c, const auto& branches) {
            CHECK(!visited[c]);
            visited[c] = 1;
            int size = 1, largest = 0;
            for (auto& branch : branches) {
                size += branch.size();
                largest = max(largest, (int)branch.size());
                for (auto [u, d] : branch) CHECK(d == distance[c][u]);
            }
            CHECK(largest <= size / 2);
        };
        cd.build(callback);
        CHECK(accumulate(visited.begin(), visited.end(), 0) == n);
        cd.build();  // 构建工作状态可重复初始化。
    }
    int n = 100000;
    vector<int> parent(n + 1);
    virtualtree::XS xs(n);
    centroid::CentroidDecomposition cd(n);
    for (int i = 2; i <= n; i++)
        parent[i] = i - 1, xs.add(i, i - 1, 1), cd.addedge(i, i - 1, 1);
    ancestor::KthAncestor a(parent);
    CHECK(a.ask(n, n - 1) == 1);
    xs.build();
    CHECK(xs.getlen(1, n) == n - 1);
    xs.build_virtual({1, n});
    CHECK(xs.vis.size() == 2);
    cd.build();
    CHECK(count(cd.vis.begin(), cd.vis.end(), true) == n);
    cout << "virtual tree / centroid / O(1) ancestor / long chain OK\n";
}

void test_number_theory() {
    for (int prime : vector<int>{101, 998244353, 1000000007}) {
        comb::Comb c(60, prime);
        comb2::Comb c2(60, prime);
        vector<vector<int>> pascal(61, vector<int>(61));
        pascal[0][0] = 1;
        for (int n = 1; n <= 60; n++) {
            pascal[n][0] = 1;
            for (int k = 1; k <= n; k++)
                pascal[n][k] =
                    ((ll)pascal[n - 1][k] + pascal[n - 1][k - 1]) % prime;
        }
        for (int n = 0; n <= 60; n++)
            for (int k = 0; k <= n + 1; k++) {
                CHECK(c.C(n, k) == (k <= n ? pascal[n][k] : 0));
                CHECK(c2.C(n, k) == c.C(n, k));
                ll expected = 1;
                for (int i = 0; i < k; i++)
                    expected = expected * (n - i) % prime;
                CHECK(c.A(n, k) == expected);
                CHECK(c.C(n, -1) == 0);
            }
    }
    primes::PrimeSieve sieve(10000);
    mobius::MobiusSieve mob(10000);
    for (int x = 1; x <= 10000; x++) {
        bool prime = x >= 2;
        int remaining = x, mu = 1, phi = x;
        for (int d = 2; d * d <= x; d++)
            if (x % d == 0) prime = false;
        for (int d = 2; d * d <= remaining; d++)
            if (remaining % d == 0) {
                int exponent = 0;
                while (remaining % d == 0) remaining /= d, exponent++;
                mu = exponent > 1 ? 0 : -mu;
                phi = phi / d * (d - 1);
            }
        if (remaining > 1) mu = -mu, phi = phi / remaining * (remaining - 1);
        CHECK(sieve.is_prime(x) == prime);
        CHECK(mob.mul[x] == mu);
        CHECK(mob.phi[x] == phi);
    }
    primecounter::PrimeCounter counter(400);
    primes::PrimeSieve full(100000);
    int pi = 0;
    for (int x = 0; x <= 100000; x++) {
        pi += full.is_prime(x);
        if (x < 1000 || x % 97 == 0) {
            CHECK(counter.lehmer_pi(x) == pi);
            CHECK(counter.getpi(x) == pi);
        }
    }
    vector<ll> prefix(101);
    for (int i = 1; i <= 100; i++) prefix[i] = prefix[i - 1] + mob.phi[i];
    dujiao::DuJiaoSieve d(
        prefix, [](ll n) { return n * (n + 1) / 2; }, [](ll n) { return n; });
    ll phisum = 0;
    for (int x = 0; x <= 5000; x++) {
        if (x) phisum += mob.phi[x];
        CHECK(d.F(x) == phisum);
    }
    for (int trial = 0; trial < 150; trial++) {
        int degree = rnd(0, 8), prime = trial % 2 ? 101 : 998244353;
        lagrange::LR lr(degree, prime);
        vector<int> coef(degree + 1), ys(degree + 1), xs(degree + 1);
        for (int& c : coef) c = rnd(0, 100);
        auto eval = [&](ll x) {
            x = lr.norm(x);
            ll r = 0;
            for (int i = degree; i >= 0; i--) r = (r * x + coef[i]) % prime;
            return r;
        };
        for (int i = 0; i <= degree; i++) ys[i] = eval(i), xs[i] = i;
        for (int q = 0; q < 30; q++) {
            ll x = rnd(-1000, 1000);
            CHECK(lr.inpo(ys, x) == eval(x));
            CHECK(lr.cal(xs, ys, x) == eval(x));
        }
    }
    for (int n = 1; n <= 600; n += rnd(1, 10)) {
        min25impl::min25 m(n);
        array<ll, 4> expected{};
        for (ll w : m.w) {
            expected = {};
            for (int p : full.p)
                if (p <= w) {
                    ll power = 1;
                    for (int k = 0; k < 4; k++)
                        expected[k] = (expected[k] + power) % m.mod,
                        power = power * p % m.mod;
                }
            CHECK(m.cal0(w) == expected[0]);
            CHECK(m.cal1(w) == expected[1]);
            CHECK(m.cal2(w) == expected[2]);
            CHECK(m.cal3(w) == expected[3]);
        }
        m.build_multiplicative({-1, 1, 0, 0}, [&](ll p, ll e) {
            return m.powmod(p, e - 1) * (p - 1) % m.mod;
        });
        for (ll w : m.w) {
            ll sum = 0;
            for (int i = 1; i <= w; i++) sum += mob.phi[i];
            CHECK(m.get(w) == sum);
        }
        m.build_multiplicative({2, 0, 0, 0}, [](ll, ll e) { return e + 1; });
        for (ll w : m.w) {
            ll count = 0;
            for (int i = 1; i <= w; i++)
                for (int j = 1; j <= i; j++) count += i % j == 0;
            CHECK(m.get(w) == count);
        }
    }
    cout << "combinations / sieves / interpolation / Min25 / Du Jiao / prime "
            "counting OK\n";
}

void test_matrices_gauss() {
    for (int trial = 0; trial < 100; trial++) {
        int n = rnd(0, 5), mod = rnd(2, 1000);
        matrix::Matrix a(n, mod), b(n, mod);
        for (auto& row : a.a)
            for (int& x : row) x = rnd(0, mod - 1);
        for (auto& row : b.a)
            for (int& x : row) x = rnd(0, mod - 1);
        auto c = a * b;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                ll expected = 0;
                for (int k = 0; k < n; k++) expected += a.a[i][k] * b.a[k][j];
                CHECK(c.a[i][j] == expected % mod);
            }
        auto power = matrix::Matrix::identity(n, mod);
        for (int k = 0; k <= 8; k++) {
            CHECK(a.pow(k).a == power.a);
            power = power * a;
        }
        matrix::Matrix determinant(n, 101);
        for (auto& row : determinant.a)
            for (int& value : row) value = rnd(0, 100);
        vector<int> permutation(n);
        iota(permutation.begin(), permutation.end(), 0);
        ll expected_det = 0;
        do {
            ll product = 1;
            int inversions = 0;
            for (int i = 0; i < n; i++) {
                product = product * determinant.a[i][permutation[i]] % 101;
                for (int j = i + 1; j < n; j++)
                    inversions += permutation[i] > permutation[j];
            }
            expected_det =
                (expected_det + (inversions % 2 ? -product : product) + 101) %
                101;
        } while (next_permutation(permutation.begin(), permutation.end()));
        auto original_matrix = determinant.a;
        CHECK(determinant.det() == expected_det);
        CHECK(determinant.a == original_matrix);
        int equ = rnd(0, 3), var = rnd(0, 3);
        modgauss::Gauss g(equ, var, 5);
        for (auto& row : g.a)
            for (int& x : row) x = rnd(-5, 5);
        for (int& x : g.rhs) x = rnd(-5, 5);
        int solutions = 0;
        vector<int> solution(var);
        function<void(int)> brute = [&](int index) {
            if (index == var) {
                for (int i = 0; i < equ; i++) {
                    ll result = 0;
                    for (int j = 0; j < var; j++)
                        result += g.a[i][j] * solution[j];
                    if (g.norm(result) != g.norm(g.rhs[i])) return;
                }
                solutions++;
                return;
            }
            for (int x = 0; x < 5; x++) solution[index] = x, brute(index + 1);
        };
        brute(0);
        auto status = g.solve();
        CHECK(status == (solutions == 0 ? 0 : solutions == 1 ? 1 : 2));
        CHECK(g.solve() == status);
        if (solutions)
            for (int i = 0; i < equ; i++) {
                ll result = 0;
                for (int j = 0; j < var; j++) result += g.a[i][j] * g.x[j];
                CHECK(g.norm(result) == g.norm(g.rhs[i]));
            }
        gauss::Gauss floating(4, 3);
        vector<double> x(3);
        for (double& value : x) value = rnd(-20, 20);
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 3; j++)
                floating.a[i][j] = i == j ? 1 : i == 3 ? rnd(-5, 5) : 0;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 3; j++)
                floating.rhs[i] += floating.a[i][j] * x[j];
        CHECK(floating.solve() == gauss::Gauss::unique);
        for (int i = 0; i < 3; i++) CHECK(abs(floating.x[i] - x[i]) < 1e-7);
    }
    gauss::Gauss multi(1, 2);
    multi.a[0] = {0, 1};
    multi.rhs[0] = 3;
    CHECK(multi.solve() == gauss::Gauss::infinite);
    CHECK(multi.x[1] == 3);
    gauss::Gauss none(2, 1);
    none.a = {{1}, {1}};
    none.rhs = {1, 2};
    CHECK(none.solve() == gauss::Gauss::no_solution);
    cout << "matrix / Gaussian elimination OK\n";
}

void test_bitset_recurrence() {
    for (int trial = 0; trial < 200; trial++) {
        int n = rnd(0, 200);
        bitsetimpl::Bitset a(n), b(n);
        vector<int> x(n), y(n);
        for (int i = 0; i < n; i++) {
            x[i] = rnd(0, 1);
            y[i] = rnd(0, 1);
            a.setBit(i, x[i]);
            b.setBit(i, y[i]);
        }
        CHECK(a.count() == accumulate(x.begin(), x.end(), 0));
        auto shifted = a;
        shifted.shift1();
        for (int i = 0; i < n; i++)
            CHECK(shifted.getBit(i) == bool(i ? x[i - 1] : 0));
        bitsetimpl::Bitset added(n);
        for (int i = 0; i < n; i++)
            if (x[i]) added.add(i);
        CHECK(added.v == a.v);
        for (int shift : vector<int>{0, 1, 63, 64, 65, n, n + 10}) {
            auto left = a << shift, right = a >> shift;
            for (int i = 0; i < n; i++) {
                CHECK(left.getBit(i) == (i >= shift ? x[i - shift] : 0));
                CHECK(right.getBit(i) == (i + shift < n ? x[i + shift] : 0));
            }
        }
        auto Or = a | b, And = a & b, Xor = a ^ b, sub = a - b;
        int borrow = 0;
        for (int i = 0; i < n; i++) {
            CHECK(Or.getBit(i) == bool(x[i] | y[i]));
            CHECK(And.getBit(i) == bool(x[i] & y[i]));
            CHECK(Xor.getBit(i) == bool(x[i] ^ y[i]));
            int result = x[i] - y[i] - borrow;
            CHECK(sub.getBit(i) == bool(result & 1));
            borrow = result < 0;
        }
    }
    bitsetimpl::Bitset a(128), b(128);
    a.setBit(0);
    for (int i = 0; i < 64; i++) b.setBit(i);
    auto sub = a - b;
    CHECK(sub.v[0] == 2);
    CHECK(sub.v[1] == ULLONG_MAX);
    for (int trial = 0; trial < 100; trial++) {
        int order = rnd(1, 8);
        vector<int> c(order), initial(order), sequence(150);
        for (int i = 0; i < order; i++)
            c[i] = rnd(0, 10), initial[i] = sequence[i] = rnd(0, 100);
        for (int i = order; i < (int)sequence.size(); i++) {
            ll value = 0;
            for (int j = 0; j < order; j++)
                value = (value + 1LL * c[j] * sequence[i - j - 1]) % 1000000007;
            sequence[i] = value;
        }
        recurrence::LinearRecurrence r(c, initial),
            bm(vector<int>(sequence.begin(),
                           sequence.begin() + 2 * order + 10));
        for (int i = 0; i < (int)sequence.size(); i++) {
            CHECK(r.nth(i) == sequence[i]);
            CHECK(bm.nth(i) == sequence[i]);
        }
    }
    recurrence::LinearRecurrence zero(vector<int>(20));
    CHECK(zero.nth(1000000000000LL) == 0);
    recurrence::LinearRecurrence one(vector<int>{1}, vector<int>{7});
    CHECK(one.nth(LLONG_MAX) == 7);
    cout << "dynamic bitset / BM / recurrence OK\n";
}

void test_specialized() {
    for (int trial = 0; trial < 150; trial++) {
        int n = rnd(0, 35);
        vector<tuple<int, int, int>> points;
        for (int i = 0; i < n; i++)
            points.emplace_back(rnd(-3, 3), rnd(-3, 3), rnd(-3, 3));
        dominance::Dominance3D cdq(points);
        vector<int> counts(n);
        for (int i = 0; i < n; i++) {
            auto [x, y, z] = points[i];
            int count = 0;
            for (int j = 0; j < n; j++)
                if (i != j) {
                    auto [xx, yy, zz] = points[j];
                    count += xx <= x && yy <= y && zz <= z;
                }
            counts[count]++;
        }
        CHECK(cdq.cnt == counts);
        n = rnd(1, 35);
        mo::Mo m(n);
        vector<int> a(n), frequency(n + 1);
        for (int i = 0; i < n; i++) a[i] = rnd(1, n);
        vector<int> expected;
        for (int q = 0; q < 50; q++) {
            int l = rnd(0, n - 1), r = rnd(l, n - 1);
            m.add_query(l, r);
            set<int> unique(a.begin() + l, a.begin() + r + 1);
            expected.push_back(unique.size());
        }
        int current = 0;
        auto run = [&] {
            return m.solve(
                [&] {
                    fill(frequency.begin(), frequency.end(), 0);
                    current = 0;
                },
                [&](int i) { current += frequency[a[i]]++ == 0; },
                [&](int i) {
                    CHECK(frequency[a[i]] > 0);
                    current -= --frequency[a[i]] == 0;
                },
                [&] { return current; });
        };
        CHECK(run() == expected);
        CHECK(run() == expected);
        int vertices = rnd(1, 8), q = rnd(0, 25);
        vector<pair<int, int>> edges;
        vector<ll> expected_scc;
        vector<vector<int>> g(vertices + 1);
        for (int i = 0; i < q; i++) {
            int u = rnd(1, vertices), v = rnd(1, vertices);
            edges.push_back({u, v});
            g[u].push_back(v);
            vector<vector<int>> reachable(vertices + 1);
            for (int x = 1; x <= vertices; x++) reachable[x] = reach(g, x);
            vector<int> seen(vertices + 1);
            ll result = 0;
            for (int x = 1; x <= vertices; x++)
                if (!seen[x]) {
                    int size = 0;
                    for (int y = 1; y <= vertices; y++)
                        if (reachable[x][y] && reachable[y][x])
                            seen[y] = 1, size++;
                    if (size > 1) result += size * size;
                }
            expected_scc.push_back(result);
        }
        dynamic_scc::IncrementalSCC ds(vertices, edges);
        CHECK(ds.anss == expected_scc);
    }
    mergeimpl::SegmentTree t(50);
    vector<int> roots;
    for (int x = 1; x <= 50; x++) {
        int p = t.update(0, 1, 50, x, x);
        CHECK(t.a[p].res0 == x);
        roots.push_back(p);
    }
    ll answer = 0;
    CHECK(t.merge(0, 0, 1, 50, 5, 5, answer) == 0);
    // 原专用合并的两棵树占据不同位置：核对最大值及跨左右子树的候选贡献。
    for (int i = 0; i < 200; i++) {
        mergeimpl::SegmentTree tree(50);
        int x = rnd(1, 49), y = rnd(x + 1, 50), vx = rnd(0, 100),
            vy = rnd(0, 100);
        int a = tree.update(0, 1, 50, x, vx), b = tree.update(0, 1, 50, y, vy);
        ll best = 0;
        int merged = tree.merge(a, b, 1, 50, 0, 0, best);
        CHECK(tree.a[merged].res0 == max(vx, vy));
        CHECK(best == vx);
        CHECK(tree.a[0].res0 == 0);
        CHECK(tree.a[0].res1 == 0);
    }
    cout << "CDQ / Mo / incremental SCC / specialized merge OK\n";
}

void test_bounded_flow() {
    for (int trial = 0; trial < 300; trial++) {
        int n = rnd(2, 4), m = rnd(0, 6);
        bounded::bounded_flow f(n, 0, n - 1);
        vector<tuple<int, int, int, int, int>> edges;
        for (int i = 0; i < m; i++) {
            int u = rnd(0, n - 1), v = rnd(0, n - 1), hi = rnd(0, 2),
                lo = rnd(0, hi), cost = rnd(-5, 5);
            if (trial % 2) lo = 0;
            f.add_bounds(u, v, lo, hi, cost);
            edges.emplace_back(u, v, lo, hi, cost);
        }
        optional<pair<ll, ll>> best;
        vector<int> balance(n);
        function<void(int, ll)> brute = [&](int i, ll cost) {
            if (i == m) {
                for (int u = 1; u < n - 1; u++)
                    if (balance[u]) return;
                if (balance[0] < 0 || balance[0] != -balance[n - 1]) return;
                pair<ll, ll> value{balance[0], cost};
                if (!best || value.first > best->first ||
                    (value.first == best->first && value.second < best->second))
                    best = value;
                return;
            }
            auto [u, v, lo, hi, c] = edges[i];
            for (int x = lo; x <= hi; x++) {
                balance[u] += x;
                balance[v] -= x;
                brute(i + 1, cost + x * c);
                balance[u] -= x;
                balance[v] += x;
            }
        };
        brute(0, 0);
        CHECK(f.mincost() == best);
        CHECK(f.mincost() == best);
    }
    cout << "bounded flow / negative cycles / feasibility OK\n";
}

int main() {
    test_persistence();
    test_dynamic_segment();
    test_dynamic_structures();
    test_virtual_centroid_ancestor();
    test_number_theory();
    test_matrices_gauss();
    test_bitset_recurrence();
    test_specialized();
    test_bounded_flow();
    cout << "PASS: third batch 27 templates, " << checks
         << " checks, seed 20261004\n";
}
