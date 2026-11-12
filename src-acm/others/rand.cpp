// 手抄版：沿用原算法与类封装；//? 标记为按需抄写。
// 用法：
// rng 是全局 mt19937_64；需要标准库头文件与 using namespace std。
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int myRand(int B) { return (unsigned long long)rng() % B; }
int rnd(int B) { return myRand(B); }
