#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using u64 = uint64_t;
namespace cartesian {
#include "../src/data_structure/笛卡尔树.cpp"
}
namespace odt {
#define main example_main
#include "../src/data_structure/珂朵莉树.cpp"
#undef main
}  // namespace odt
namespace basis {
#include "../src/others/线性基.cpp"
}
namespace johnson {
const ll inf = 1LL << 50;
#include "../src/graph/johnson全源最短路.cpp"
}  // namespace johnson
namespace cycles {
#include "../src/graph/三四元环计数.cpp"
}
namespace mincycle {
#define main example_main
#include "../src/graph/最小环.cpp"
#undef main
}  // namespace mincycle
namespace runsimpl {
#include "../src/string/runs.cpp"
}
namespace dequehash {
#include "../src/string/dequehash.cpp"
}
#undef int
#undef sz
int checks = 0;
#define CHECK(e)                                               \
    do {                                                       \
        checks++;                                              \
        if (!(e)) {                                            \
            cerr << "FAIL " << __LINE__ << ": " << #e << '\n'; \
            exit(1);                                           \
        }                                                      \
    } while (0)
mt19937 rng(20261005);
int rnd(int lo, int hi) { return lo + rng() % (hi - lo + 1); }
template <class F>
string capture(const string& input, F f) {
    istringstream in(input);
    ostringstream out;
    auto* oldin = cin.rdbuf(in.rdbuf());
    auto* oldout = cout.rdbuf(out.rdbuf());
    cin.clear();
    f();
    cin.rdbuf(oldin);
    cout.rdbuf(oldout);
    cin.clear();
    return out.str();
}
void test_structures() {
    cartesian::n = 0;
    CHECK(cartesian::build() == -1);
    for (int trial = 0; trial < 150; trial++) {
        int n = rnd(1, 30);
        cartesian::n = n;
        for (int i = 0; i < n; i++) cartesian::a[i] = rnd(-10, 10);
        int root = cartesian::build();
        vector<int> order;
        function<void(int)> visit = [&](int x) {
            if (x == -1) return;
            int l = cartesian::ve[x][0], r = cartesian::ve[x][1];
            if (l != -1) CHECK(cartesian::a[x] <= cartesian::a[l]);
            if (r != -1) CHECK(cartesian::a[x] <= cartesian::a[r]);
            visit(l);
            order.push_back(x);
            visit(r);
        };
        visit(root);
        vector<int> want(n);
        iota(want.begin(), want.end(), 0);
        CHECK(order == want);
        odt::SegmentMap t(n);
        vector<int> a(n);
        for (int q = 0; q < 100; q++) {
            int l = rnd(0, n - 1), r = rnd(l, n - 1), v = rnd(0, 1000);
            if (q % 3) {
                t.update(l, r, [&](int) { return v; });
                fill(a.begin() + l, a.begin() + r + 1, v);
            } else {
                t.update(l, r, [](int x) { return int(sqrt(x)); });
                for (int i = l; i <= r; i++) a[i] = sqrt(a[i]);
            }
            CHECK(t.sum == accumulate(a.begin(), a.end(), 0));
            CHECK(t.ma.begin()->first == 0);
            CHECK(t.ma.rbegin()->first == n);
        }
        int count = rnd(0, 8);
        vector<ll> values(count);
        for (ll& x : values) x = rnd(0, 63);
        basis::LinearBasis b(values.data(), values.size());
        set<ll> reachable;
        for (int mask = 0; mask < (1 << count); mask++) {
            ll value = 0;
            for (int i = 0; i < count; i++)
                if (mask >> i & 1) value ^= values[i];
            reachable.insert(value);
        }
        CHECK(b.queryMax() == *reachable.rbegin());
        for (int v = 0; v < 64; v++)
            CHECK(b.query(v) == bool(reachable.count(v)));
    }
}
void test_graphs() {
    johnson::graph empty(0);
    CHECK(empty.init());
    johnson::graph negative(1);
    negative.adde(0, 0, -1);
    CHECK(!negative.init());
    for (int trial = 0; trial < 150; trial++) {
        int n = rnd(1, 8);
        johnson::graph t(n);
        vector<int> potential(n);
        for (int& v : potential) v = rnd(-10, 10);
        vector<vector<ll>> d(n, vector<ll>(n, johnson::inf));
        for (int i = 0; i < n; i++) d[i][i] = 0;
        for (int u = 0; u < n; u++)
            for (int v = 0; v < n; v++)
                if (rnd(0, 3) == 0) {
                    int w = rnd(0, 10) + potential[v] - potential[u];
                    t.adde(u, v, w);
                    d[u][v] = min(d[u][v], ll(w));
                }
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if (d[i][k] < johnson::inf && d[k][j] < johnson::inf)
                        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        CHECK(t.init());
        CHECK(t.e.size() == (size_t)n);
        for (int i = 0; i < n; i++) {
            auto result = t.query(i);
            for (int j = 0; j < n; j++)
                CHECK(d[i][j] < johnson::inf ? result[j] == d[i][j]
                                             : result[j] > johnson::inf / 2);
        }
        vector<vector<int>> a(n, vector<int>(n));
        vector<tuple<int, int, int>> edges;
        for (int u = 0; u < n; u++)
            for (int v = u + 1; v < n; v++)
                if (rnd(0, 1))
                    a[u][v] = a[v][u] = 1, edges.emplace_back(u, v, rnd(1, 9));
        ostringstream input;
        input << n << ' ' << edges.size() << '\n';
        for (auto [u, v, w] : edges) input << u << ' ' << v << '\n';
        int three = 0, four = 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                for (int k = j + 1; k < n; k++) {
                    three += a[i][j] && a[j][k] && a[k][i];
                    for (int l = k + 1; l < n; l++) {
                        four += a[i][j] && a[j][k] && a[k][l] && a[l][i];
                        four += a[i][j] && a[j][l] && a[l][k] && a[k][i];
                        four += a[i][k] && a[k][j] && a[j][l] && a[l][i];
                    }
                }
        istringstream output(capture(input.str(), [] { cycles::solve(); }));
        int got3, got4;
        output >> got3 >> got4;
        CHECK(got3 == three);
        CHECK(got4 == four);
        input.str("");
        input.clear();
        input << n << ' ' << edges.size() << '\n';
        for (auto [u, v, w] : edges) input << u << ' ' << v << ' ' << w << '\n';
        ll best = johnson::inf;
        for (int removed = 0; removed < (int)edges.size(); removed++) {
            auto [s, target, weight] = edges[removed];
            vector<ll> dist(n, johnson::inf);
            dist[s] = 0;
            for (int iter = 0; iter < n; iter++)
                for (int e = 0; e < (int)edges.size(); e++)
                    if (e != removed) {
                        auto [u, v, w] = edges[e];
                        dist[u] = min(dist[u], dist[v] + w);
                        dist[v] = min(dist[v], dist[u] + w);
                    }
            best = min(best, dist[target] + weight);
        }
        string result = capture(input.str(), [] { mincycle::example_main(); });
        CHECK(best >= johnson::inf ? result == "No solution."
                                   : stoll(result) == best);
    }
}
void test_runs() {
    for (int trial = 0; trial < 250; trial++) {
        string s;
        for (int n = rnd(0, 18); n--;) s += 'a' + rnd(0, 2);
        set<tuple<int, int, int>> want;
        for (int l = 0; l < (int)s.size(); l++)
            for (int r = l + 1; r < (int)s.size(); r++)
                for (int p = 1; 2 * p <= r - l + 1; p++) {
                    bool valid = true;
                    for (int i = l + p; i <= r; i++) valid &= s[i] == s[i - p];
                    if (!valid) continue;
                    for (int q = 1; q < p; q++) {
                        bool smaller = true;
                        for (int i = l + q; i <= r; i++)
                            smaller &= s[i] == s[i - q];
                        if (smaller) valid = false;
                    }
                    if (l && s[l - 1] == s[l - 1 + p]) valid = false;
                    if (r + 1 < (int)s.size() && s[r + 1] == s[r + 1 - p])
                        valid = false;
                    if (valid) want.emplace(l, r, p);
                }
        auto result = runsimpl::run(s);
        CHECK(
            (set<tuple<int, int, int>>(result.begin(), result.end()) == want));
    }
}
void test_deque_hash() {
    dequehash::init();
    auto hash = [](const vector<ll>& values, int l, int r) {
        ll result = 0, power = 1;
        for (int i = l; i <= r; i++) {
            result = (result + values[i] * power) % dequehash::mod;
            power = power * dequehash::base % dequehash::mod;
        }
        return result;
    };
    for (int trial = 0; trial < 100; trial++) {
        dequehash::extendable_sequence x, y;
        vector<ll> a, b;
        for (int step = 0; step < 10; step++) {
            vector<ll> v(rnd(0, 4));
            for (ll& value : v) value = rnd(1, 26);
            if (step % 2) {
                x.add_front(v);
                a.insert(a.begin(), v.begin(), v.end());
            } else {
                x.add_back(v);
                a.insert(a.end(), v.begin(), v.end());
            }
        }
        b.resize(rnd(0, 10));
        for (ll& value : b) value = rnd(1, 26);
        y.add_back(b);
        for (int i = 0; i < (int)a.size(); i++) CHECK(x[i + 1].second == a[i]);
        vector<ll> joined = a;
        joined.insert(joined.end(), b.begin(), b.end());
        for (int q = 0; q < 50 && !joined.empty(); q++) {
            int l = rnd(0, joined.size() - 1), r = rnd(l, joined.size() - 1);
            CHECK(dequehash::calc(x, y, l + 1, r + 1) == hash(joined, l, r));
            CHECK(dequehash::calc(x, y, l + 1) == joined[l]);
            if (r < (int)a.size()) CHECK(x.calc(l + 1, r + 1) == hash(a, l, r));
        }
    }
}
int main() {
    test_structures();
    test_graphs();
    test_runs();
    test_deque_hash();
    cout << "PASS: indexing migration, " << checks
         << " checks, seed 20261005\n";
}
