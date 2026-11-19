// 用法：vector<Task> tasks = {{3,5}, {2,1}}; sort(tasks.begin(), tasks.end());
// 每项先消耗 a，再获得 b；按原规则排序，a<=b 的任务在前。
struct Task {
    int a, b;
};
bool operator<(const Task& x, const Task& y) {
    if ((x.a <= x.b) ^ (y.a <= y.b)) return x.a <= x.b;
    if (x.a <= x.b) return x.a == y.a ? x.b < y.b : x.a < y.a;
    return x.b == y.b ? x.a > y.a : x.b > y.b;
}
