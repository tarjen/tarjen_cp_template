#include "variants.h"

using ll = long long;
using Clock = chrono::steady_clock;
volatile uint64_t sink = 0;
int checks = 0;
void check_impl(bool ok, int line) {
    ++checks;
    if (!ok) throw runtime_error("optimization correctness mismatch at line " + to_string(line));
}
#define check(x) check_impl((x), __LINE__)
mt19937 rng(20261007);
string groups;

vector<tuple<int, int, ll>> make_tree(int n, int shape) {
    vector<tuple<int, int, ll>> e;
    for (int v = 2; v <= n; ++v) {
        int u = shape == 0 ? v - 1 : shape == 1 ? 1 :
                shape == 2 ? v / 2 : 1 + rng() % (v - 1);
        e.emplace_back(u, v, rng() % 100);
    }
    return e;
}
ll diameter(int n, const vector<tuple<int, int, ll>>& e) {
    vector<vector<pair<int, ll>>> g(n + 1);
    for (auto [u, v, w] : e) g[u].push_back({v, w}), g[v].push_back({u, w});
    ll best = 0;
    for (int s = 1; s <= n; ++s) {
        vector<tuple<int, int, ll>> todo{{s, 0, 0}};
        while (!todo.empty()) {
            auto [u, p, d] = todo.back(); todo.pop_back(); best = max(best, d);
            for (auto [v, w] : g[u]) if (v != p) todo.push_back({v, u, d + w});
        }
    }
    return best;
}
void verify() {
    for (int n : {1, 2, 3, 7, 32}) {
        old_pst::Persistent_SegmentTree a(n); new_pst::Persistent_SegmentTree b(n);
        vector<vector<ll>> oracle(1, vector<ll>(n + 1));
        for (int k = 0; k < 160; ++k) {
            int x = rng() % oracle.size(), y = rng() % oracle.size();
            if (k % 3) {
                int l = rng() % n + 1, r = rng() % n + 1; if (l > r) swap(l, r);
                ll w = int(rng() % 21) - 10;
                auto v = oracle[x]; for (int i = l; i <= r; ++i) v[i] += w;
                oracle.push_back(v); a.append(x, l, r, w); b.append(x, l, r, w);
            } else {
                int p = rng() % (n + 1); auto v = oracle[x];
                for (int i = p + 1; i <= n; ++i) v[i] = oracle[y][i];
                oracle.push_back(v); a.splice(x, y, p); b.splice(x, y, p);
            }
            for (int v = 0; v < (int)oracle.size(); ++v)
                for (int i = 1; i <= n; ++i) {
                    check(a.query(v, i) == oracle[v][i]); check(b.query(v, i) == oracle[v][i]);
                }
            check(b.a.size() <= a.a.size());
        }
        check(a.val(a.root.back(), 0) == b.val(b.root.back(), 0));
        check(a.val(a.root.back(), n + 1) == b.val(b.root.back(), n + 1));
    }
    for (int n : {0, 1, 2, 17, 100}) {
        vector<ll> v(n + 1); for (auto& x : v) x = int(rng() % 101) - 50;
        old_bit::RangeTreearray a(v); new_bit::RangeTreearray b(v);
        for (int i = 0; i <= n; ++i) { check(a.tree1[i] == b.tree1[i]); check(a.tree2[i] == b.tree2[i]); }
        for (int k = 0; n && k < 300; ++k) {
            int l = rng() % n + 1, r = rng() % n + 1; if (l > r) swap(l, r);
            ll w = int(rng() % 21) - 10; a.update(l, r, w); b.update(l, r, w);
            for (int i = l; i <= r; ++i) v[i] += w;
            for (int i = 1; i <= n; ++i) check(b.getsum(i) == accumulate(v.begin() + 1, v.begin() + i + 1, 0LL));
        }
    }
    for (int n : {1, 2, 13, 63}) {
        old_odt::SegmentMap a(n); new_odt::SegmentMap b(n); vector<int> v(n);
        for (int k = 0; k < 500; ++k) {
            int l = rng() % n, r = rng() % n; if (l > r) swap(l, r);
            int shape = k % 3, w = int(rng() % 21) - 10;
            auto f = [=](int x) {return shape == 0 ? w : shape == 1 ? x + w : (x * x + 3) % 31;};
            a.update(l, r, f); b.update(l, r, f); for (int i = l; i <= r; ++i) v[i] = f(v[i]);
            check(a.ma == b.ma); check(a.sum == b.sum); check(b.sum == accumulate(v.begin(), v.end(), 0));
        }
    }
    for (int n : {1, 2, 3, 17, 64}) for (int shape = 0; shape < 4; ++shape) {
        auto e = make_tree(n, shape);
        old_diam::DynamicTreeDiameter<> a(n, e); new_diam::DynamicTreeDiameter<> b(n, e);
        check(a.query() == diameter(n, e)); check(b.query() == a.query()); check(a.L == b.L && a.R == b.R && a.child == b.child);
        for (int k = 0; n > 1 && k < 100; ++k) {
            int id = rng() % (n - 1); ll w = k % 5 == 0 ? 0 : rng() % 100;
            get<2>(e[id]) = w; a.update(id, w); b.update(id, w);
            check(a.query() == diameter(n, e)); check(b.query() == a.query());
        }
    }
    old_hash::init(); new_hash::init();
    for (int i = 0; i < old_hash::maxn; ++i) {
        check(old_hash::p[i] == new_hash::p[i]); check(old_hash::ip[i] == new_hash::ip[i]);
    }
    old_hash::extendable_sequence a; new_hash::extendable_sequence b; vector<ll> v;
    for (int k = 0; k < 100; ++k) {
        vector<ll> vals{ll(rng() % 100 + 1), ll(rng() % 100 + 1)};
        if (k & 1) a.add_front(vals), b.add_front(vals), v.insert(v.begin(), vals.begin(), vals.end());
        else a.add_back(vals), b.add_back(vals), v.insert(v.end(), vals.begin(), vals.end());
        for (int l = 1; l <= (int)v.size(); ++l) {
            int r = l + rng() % (v.size() - l + 1); ll h = 0, pw = 1;
            for (int i = l - 1; i < r; ++i) {h = (h + v[i] * pw) % new_hash::mod; pw = pw * new_hash::base % new_hash::mod;}
            check(a.calc(l, r) == h); check(b.calc(l, r) == h);
        }
    }
    for (int n = 0; n <= 9; ++n) {
        vector<unsigned> v(1 << n); for (auto& x : v) x = rng();
        auto a = v, b = v; old_sos::run(a, n); new_sos::run(b, n); check(a == b);
        for (int mask = 0; mask < (1 << n); ++mask) {
            unsigned s = v[0]; for (int sub = mask; sub; sub = (sub - 1) & mask) s += v[sub];
            check(b[mask] == s);
        }
    }
    cout << "PASS correctness checks=" << checks << " seed=20261007\n";
}

template<class F> double measure(F f, int loops) {
    auto start = Clock::now(); for (int i = 0; i < loops; ++i) sink = f();
    return chrono::duration<double, milli>(Clock::now() - start).count();
}
template<class F, class G> void bench(string name, int n, string shape, F old, G proposed) {
    if (!groups.empty() && groups.find(name) == string::npos) return;
    check(old() == proposed()); int loops = 1;
    while (loops < (1 << 22) && measure(old, loops) < 50) loops *= 2;
    vector<double> a, b;
    for (int k = 0; k < 7; ++k) {
        double x, y;
        if (k & 1) y = measure(proposed, loops), x = measure(old, loops);
        else x = measure(old, loops), y = measure(proposed, loops);
        a.push_back(x); b.push_back(y);
    }
    sort(a.begin(), a.end()); sort(b.begin(), b.end());
    cout << name << ',' << n << ',' << shape << ',' << loops << ',' << a[3] << ',' << b[3] << ',' << a[3] / b[3] << '\n' << flush;
}
struct POp {int kind, x, y, l, r; ll w;};
template<class T> uint64_t persistent(int n, const vector<POp>& ops) {
    T tr(n); uint64_t s = 0;
    for (auto o : ops) {
        if (o.kind == 0) tr.append(o.x, o.l, o.r, o.w);
        else if (o.kind == 1) tr.splice(o.x, o.y, o.l);
        else s += tr.query(o.x, o.l);
    }
    return s;
}
template<class T> uint64_t bitinit(const vector<ll>& v) {
    T t(v); return t.tree1.back() + t.tree2.back();
}
struct OOp {int l, r, kind, w;};
template<class T> uint64_t odt(int n, const vector<OOp>& ops) {
    T tr(n); uint64_t s = 0;
    for (auto o : ops) {
        tr.update(o.l, o.r, [=](int x) {
            if (o.kind == 0) return o.w;
            if (o.kind == 1) return x + o.w;
            for (int i = 0; i < 8; ++i) x = (x * 17 + 13) % 1009;
            return x;
        });
        s += tr.sum;
    }
    return s;
}
template<class T> uint64_t diam(int n, const vector<tuple<int, int, ll>>& e, int ops) {
    T t(n, e); uint64_t s = t.query();
    for (int k = 0; n > 1 && k < ops; ++k) t.update(k % (n - 1), k % 101), s += t.query();
    return s;
}
int main(int argc, char** argv) {
    if (argc > 1) groups = argv[1];
    verify(); cout << fixed << setprecision(4);
    cout << "template,n,shape,loops,old_ms,new_ms,speedup\n";
    for (int n : {1, 2, 17, 1024, 100000}) for (int shape = 0; shape < 5; ++shape) {
        vector<POp> ops; int versions = 1;
        for (int k = 0; k < 500; ++k) {
            int kind = shape == 0 ? 0 : shape == 1 ? 1 : shape == 2 ? 2 : k % 3;
            int l = rng() % n + 1, r = rng() % n + 1; if (l > r) swap(l, r);
            int x = rng() % versions, y = rng() % versions;
            if (shape == 4) l = (k & 1) ? 0 : n;
            if (kind == 2) l = rng() % n + 1;
            ops.push_back({kind, x, y, l, r, ll(rng() % 21)}); if (kind != 2) ++versions;
        }
        bench("persistent", n, to_string(shape), [&]{return persistent<old_pst::Persistent_SegmentTree>(n, ops);}, [&]{return persistent<new_pst::Persistent_SegmentTree>(n, ops);});
        bench("clone_only", n, to_string(shape), [&]{return persistent<old_pst::Persistent_SegmentTree>(n, ops);}, [&]{return persistent<clone_pst::Persistent_SegmentTree>(n, ops);});
        bench("query_only", n, to_string(shape), [&]{return persistent<old_pst::Persistent_SegmentTree>(n, ops);}, [&]{return persistent<query_pst::Persistent_SegmentTree>(n, ops);});
    }
    for (int n : {0, 1, 2, 17, 1024, 100000}) for (int shape = 0; shape < 3; ++shape) {
        vector<ll> v(n + 1); for (int i = 1; i <= n; ++i) v[i] = shape == 0 ? 0 : shape == 1 ? i % 100 : int(rng() % 201) - 100;
        bench("bit_init", n, to_string(shape), [&]{return bitinit<old_bit::RangeTreearray>(v);}, [&]{return bitinit<new_bit::RangeTreearray>(v);});
    }
    for (int n : {1, 2, 17, 1024, 100000}) for (int shape = 0; shape < 4; ++shape) {
        vector<OOp> ops;
        for (int k = 0; k < 1000; ++k) {int l = rng() % n, r = rng() % n; if (l > r) swap(l, r); if (shape == 0) l = 0, r = n - 1; if (shape == 1) r = l; ops.push_back({l,r,shape == 3 ? 2 : k & 1,k % 5});}
        bench("odt", n, to_string(shape), [&]{return odt<old_odt::SegmentMap>(n, ops);}, [&]{return odt<new_odt::SegmentMap>(n, ops);});
    }
    for (int n : {1, 2, 17, 1024, 10000}) for (int shape = 0; shape < 4; ++shape) {
        auto e = make_tree(n, shape);
        for (int count : {0, 1000}) bench("diameter", n, to_string(shape)+"_"+to_string(count), [&]{return diam<old_diam::DynamicTreeDiameter<>>(n,e,count);}, [&]{return diam<new_diam::DynamicTreeDiameter<>>(n,e,count);});
    }
    bench("dequehash", old_hash::maxn, "init", []{old_hash::init();return old_hash::ip[old_hash::maxn-1];}, []{new_hash::init();return new_hash::ip[new_hash::maxn-1];});
    for (int n : {0,1,2,4,10,16,20}) for (int shape = 0; shape < 2; ++shape) {
        vector<unsigned> v(1 << n); for (auto& x:v) x=shape?rng():0;
        bench("sos",n,to_string(shape),[&]{auto a=v;old_sos::run(a,n);return a.back();},[&]{auto a=v;new_sos::run(a,n);return a.back();});
    }
}
