// 用法：
// int start = getMin("baca");  // 最小循环表示起点为 3（0base）。
// string s = "baca";
// string result = s.substr(start) + s.substr(0, start);  // "abac"。
// 返回起点而非字符串；输入非空串。
int getMin(string s) {
    int i = 0, j = 1, k = 0;
    int len = s.length();
    while (i < len && j < len && k < len) {
        int tmp = s[(i + k) % len] - s[(j + k) % len];
        if (tmp == 0)
            k++;
        else {
            if (tmp > 0)
                i += k + 1;
            else
                j += k + 1;
            if (i == j) j++;
            k = 0;
        }
    }
    return min(i, j);
}