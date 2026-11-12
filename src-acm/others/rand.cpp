// 用法：
// int x = myRand(10);  // 随机整数 [0,9]，要求参数 B>0。
// int y = rnd(10);  // 同一接口的别名。
// rng 是全局 mt19937_64；需要标准库头文件与 using namespace std。
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int myRand(int B) { return (unsigned long long)rng() % B; }
int rnd(int B) { return myRand(B); }
