// 用法：
// 此片段应放在比较函数里；a,b 为当前任务属性，x.a/x.b 为另一任务。
// 用于先消耗 a、再获得 b 的任务排序，按 a<=b 分组后比较。
// 需自行提供任务 struct 与比较函数，不能直接放在文件全局作用域。
if ((a <= b) ^ (x.a <= x.b)) return a <= b;
if (a <= b) {
    if (a == x.a) return b < x.b;
    return a < x.a;
} else {
    if (b == x.b) return a > x.a;
    return b > x.b;
}