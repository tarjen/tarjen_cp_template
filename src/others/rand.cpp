mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int myRand(int B) { return (unsigned long long)rng() % B; }