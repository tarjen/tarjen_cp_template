// 用法：
// 本板是完整程序：输入 n，然后 n-1 条无向边 u v；节点 1base。
// getHash(1,0) 以节点 1 为根，hash[u] 是该根下 u 的子树哈希。
// 程序输出不同有根子树哈希值的数量；不求无根树的同构编号。
// 使用带时间种子的随机映射，哈希值不能跨进程直接比较。
#include <cctype>
#include <chrono>
#include <cstdio>
#include <random>
#include <set>
#include <vector>

typedef unsigned long long ull;

const ull mask = std::chrono::steady_clock::now().time_since_epoch().count();

ull h(ull x) { return x * x * x * 1237123 + 19260817; }
ull f(ull x) {
    ull cur = h(x & ((1 << 31) - 1)) + h(x >> 31);
    return cur;
}
ull shift(ull x) {
    x ^= mask;
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    x ^= mask;
    return x;
}

const int N = 1e6 + 10;

int n;
ull hash[N];
std::vector<int> edge[N];
std::set<ull> trees;

void getHash(int x, int p) {
    hash[x] = 1;
    for (int i : edge[x]) {
        if (i == p) {
            continue;
        }
        getHash(i, x);
        hash[x] += shift(hash[i]);
    }
    trees.insert(hash[x]);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    getHash(1, 0);
    printf("%lu", trees.size());
}
