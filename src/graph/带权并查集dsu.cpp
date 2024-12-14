const int maxn = 1e5 + 10;
int f[maxn], dis[maxn];
int getf(int x) {
    if (x == f[x]) return x;
    int z = getf(f[x]);
    dis[x] += dis[f[x]];
    return f[x] = z;
}
void unit(int i, int j, int len) {
    int x = getf(i), y = getf(j);
    f[x] = y;
    // 在赋值之前因为x是头节点所以dis一定等于0
    dis[x] = dis[j] - dis[i] + len;
}