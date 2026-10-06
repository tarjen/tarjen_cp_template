// 用法：
// gettime timer; 放在一个作用域内，析构时输出 CPU 用时（秒）。
// 文件已有全局 tim，会在程序退出时输出；不要重复创建计时器。
// 当前 main 的 tim.begin()/tim.end() 不存在，使用时去掉该演示 main。
struct gettime {
    clock_t star, ends;
    gettime() { star = clock(); }
    ~gettime() {
        ends = clock();
        cout << "Running Time : " << (double)(ends - star) / CLOCKS_PER_SEC
             << endl;
    }
} tim;
int main() {
    tim.begin();
    tim.end();
    return 0;
}