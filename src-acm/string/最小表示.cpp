// 手抄版：沿用原算法与类封装；//? 标记为按需抄写。
// 用法：
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
