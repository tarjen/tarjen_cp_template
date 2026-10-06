// 用法：
// LR tr;
// int value = tr.inter(vector<int>{0,1,4}, 3);  // 以 f(0),f(1),f(2) 插值得到 9。
// 当前文件缺少结尾的 };，须先补齐；该版本用 int 运算，只适合不溢出的数据。
struct LR {
    int inter(std::vector<int> vec, int x) {
        int n = vec.size() - 1;
        int ans = 0;
        for (int i = 0; i <= n; ++i) {
            int div = 1;
            for (int j = 0; j <= n; ++j) {
                if (i != j) div *= (i - j);
            }
            bool flag = div < 0;
            div = std::abs(div);
            int prod = vec[i];
            for (int j = 0; j <= n; ++j) {
                if (i == j) continue;
                int gcd = std::abs(std::__gcd(x - j, div));
                prod *= (x - j) / gcd;
                div /= gcd;
            }
            ans += flag ? -prod : prod;
        }
        return ans;
    }