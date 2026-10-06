#include <bits/stdc++.h>
using namespace std;

namespace bit_template {
#include "../src/data_structure/树状数组.cpp"
}
namespace seg_template {
#include "../src/data_structure/线段树区间加区间求和getsum.cpp"
}

using BIT = bit_template::RangeTreearray;
using SEG = seg_template::SegmentTree<>;
using Clock = chrono::steady_clock;
volatile uint64_t benchmark_sink = 0;

struct Operation {
    int l, r;
    long long delta;
    bool update;
};

vector<Operation> generate(int n, int count, int shape, uint64_t seed) {
    mt19937_64 rng(seed);
    vector<Operation> ops;
    ops.reserve(count);
    for (int i = 0; i < count; ++i) {
        int l = int(rng() % n) + 1;
        int r = int(rng() % n) + 1;
        if (shape == 0) {
            if (l > r) swap(l, r);
        } else if (shape == 1) {
            r = l + int(rng() % min(64, n - l + 1));
        } else if (shape == 2) {
            r = l;
        } else {
            l = 1;
            r = n;
        }
        ops.push_back({l, r, static_cast<long long>(rng() % 2001) - 1000,
                       bool(rng() & 1)});
    }
    return ops;
}

void verify_small() {
    // Independent naive oracle; include negatives, boundaries and all shapes.
    for (int n : {1, 2, 17, 128}) {
        for (int shape = 0; shape < 4; ++shape) {
            BIT bit(n);
            SEG seg(n - 1);
            vector<long long> a(n + 1);
            auto ops = generate(n, 5000, shape, 20261005 + n * 4 + shape);
            for (const auto& op : ops) {
                if (op.update) {
                    bit.update(op.l, op.r, op.delta);
                    seg.update(op.l - 1, op.r - 1, op.delta);
                    for (int i = op.l; i <= op.r; ++i) a[i] += op.delta;
                } else {
                    long long want =
                        accumulate(a.begin() + op.l, a.begin() + op.r + 1, 0LL);
                    if (bit.query(op.l, op.r) != want ||
                        seg.query(op.l - 1, op.r - 1) != want)
                        throw runtime_error("naive oracle mismatch");
                }
            }
        }
    }
}

void verify_pair(int n, const vector<Operation>& ops) {
    BIT bit(n);
    SEG seg(n - 1);
    for (const auto& op : ops) {
        if (op.update) {
            bit.update(op.l, op.r, op.delta);
            seg.update(op.l - 1, op.r - 1, op.delta);
        } else if (bit.query(op.l, op.r) != seg.query(op.l - 1, op.r - 1)) {
            throw runtime_error("benchmark query mismatch");
        }
    }
}

struct Timing {
    double init_ms, operations_ms;
    uint64_t checksum;
};

template <class Tree>
Timing measure(int n, const vector<Operation>& ops) {
    auto start = Clock::now();
    constexpr int offset = is_same_v<Tree, SEG> ? 1 : 0;
    Tree tree(n - offset);
    auto initialized = Clock::now();
    uint64_t checksum = 0;
    // Both manage n elements; operations are 1base and segment indices are
    // 0base.
    for (const auto& op : ops) {
        if (op.update)
            tree.update(op.l - offset, op.r - offset, op.delta);
        else
            checksum +=
                static_cast<uint64_t>(tree.query(op.l - offset, op.r - offset));
    }
    auto finished = Clock::now();
    benchmark_sink = checksum;
    return {chrono::duration<double, milli>(initialized - start).count(),
            chrono::duration<double, milli>(finished - initialized).count(),
            checksum};
}

double median(vector<double> values) {
    sort(values.begin(), values.end());
    size_t m = values.size() / 2;
    return values.size() % 2 ? values[m] : (values[m - 1] + values[m]) / 2;
}

int main(int argc, char** argv) {
    try {
        if (argc < 4) throw runtime_error("usage: benchmark ops repeats n...");
        int count = stoi(argv[1]), repeats = stoi(argv[2]);
        if (count < 1 || repeats < 1) throw runtime_error("invalid arguments");
        verify_small();
        cout
            << "n,operations,scenario,updates,queries,bit_ms,segment_ms,"
               "speedup,"
               "bit_init_ms,segment_init_ms,bit_bytes,segment_bytes,checksum\n";
        const char* names[] = {"random", "short_1_to_64", "point", "full"};
        cout << fixed << setprecision(3);
        for (int arg = 3; arg < argc; ++arg) {
            int n = stoi(argv[arg]);
            if (n < 1) throw runtime_error("n must be positive");
            for (int shape = 0; shape < 4; ++shape) {
                auto ops =
                    generate(n, count, shape, 20261005ULL + n * 4ULL + shape);
                verify_pair(n, ops);
                // One untimed warm-up per implementation; alternate timed
                // order.
                measure<BIT>(n, ops);
                measure<SEG>(n, ops);
                vector<double> bt, st, bi, si;
                uint64_t checksum = 0;
                for (int trial = 0; trial < repeats; ++trial) {
                    Timing b, s;
                    if (trial % 2 == 0) {
                        b = measure<BIT>(n, ops);
                        s = measure<SEG>(n, ops);
                    } else {
                        s = measure<SEG>(n, ops);
                        b = measure<BIT>(n, ops);
                    }
                    if (b.checksum != s.checksum)
                        throw runtime_error("timed checksum mismatch");
                    bt.push_back(b.operations_ms);
                    st.push_back(s.operations_ms);
                    bi.push_back(b.init_ms);
                    si.push_back(s.init_ms);
                    checksum = b.checksum;
                }
                size_t updates =
                    count_if(ops.begin(), ops.end(),
                             [](const Operation& op) { return op.update; });
                BIT bit(n);
                SEG seg(n - 1);
                size_t bit_bytes =
                    (bit.tree1.capacity() + bit.tree2.capacity()) *
                    sizeof(long long);
                size_t seg_bytes = seg.a.capacity() * sizeof(SEG::Node);
                cout << n << ',' << count << ',' << names[shape] << ','
                     << updates << ',' << count - updates << ',' << median(bt)
                     << ',' << median(st) << ',' << median(st) / median(bt)
                     << ',' << median(bi) << ',' << median(si) << ','
                     << bit_bytes << ',' << seg_bytes << ',' << checksum
                     << endl;
            }
        }
    } catch (const exception& e) {
        cerr << e.what() << '\n';
        return 1;
    }
}
