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