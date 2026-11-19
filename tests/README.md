# 模板验证

在仓库根目录运行，需要 Python 3 与支持 C++17 的 g++：

```powershell
python tests/run_all.py
```

该入口依次执行完整封装版与赛时手抄版的正确性测试。所有可执行文件和手抄源码副本均位于系统临时目录，运行结束自动清理，不改写两个源码目录。

入口先执行 Python 生成器测试，检查手抄版用法注释保留、同类调用压行、接口可直接使用，以及对照页数据生成。可单独运行 `python -m unittest discover -s tests -p "test_*.py"`。

## 测试范围

| 测试文件 | 验证内容 |
| --- | --- |
| `template_core.cpp` | 默认线段树操作、Hash 编译与长短字符串重复初始化、线性基清空后重新使用 |
| `poly_pow_n2.cpp` | 多项式 k 次幂与朴素卷积求幂对拍，500 组随机数据及边界 |
| `line_container.cpp` | 动态直线凸包单点最小值与枚举对拍，300 组随机插入/查询及同斜率、重复直线、负数交点和清空重用 |
| `hk.cpp`| HK 与朴素增广路对拍，穷举至多 3x3 的图、2000 个随机图、重边、重复求解、加边重算及 100000 左点的交替路 |
| `bct.cpp` | 圆方树与枚举顶点子集的点双判据对拍，穷举至多 5 点的图、500 个随机多重图，覆盖非连通、孤立点、重复构建、加边重建和 100000 点链 |
| `euler.cpp` | 欧拉路径按顶点序列字典序最小，枚举 3 点且至多 5 条边的多重图、400 个随机图，含自环、指定起点、非连通和重复使用 |
| `lcs_bitset.cpp` | 通用 Bitset 与 LCS 片段直接拼接，和普通 DP 对拍，覆盖 500 个随机串、机器字边界、3010 长串与重复调用 |
| `relu.cpp` | 截断线性函数复合，穷举小范围函数对、10000 组随机三函数，覆盖常量、int 极值及流输出 |
| `xor_equations.cpp` | 异或方程组与枚举赋值对拍，穷举至多 3 个未知量、3 个方程及 1000 组随机数据，覆盖增量加方程、重复求解、清空、空方程与 bitset 容量边界 |
| `line_abc.cpp` | 整数两点求直线的系数归一化，10000 组随机点对、同线换点、方向翻转、平移、水平/竖直线与 ±1e9 坐标边界 |
| `test_duipai.py` | 10 行 Python 对拍的多轮运行、忽略空白、WA 反例保存、程序报错、超时及含空格路径 |
| `template_refactor.cpp` | 36 个模板，覆盖树状数组、线段树、字符串、图论等；另运行 76 组非法线段树输入检查断言 |
| `template_refactor_third.cpp` | 26 个模板，覆盖可持久化结构、节点池扩容、树结构、数论、矩阵、递推、费用流等 |
| `template_indexing.cpp` | 8 个模板的下标迁移、边界与朴素结果对照 |
| `template_dynamic_diameter.cpp` | 动态树直径与朴素全点对距离对照 |
| `handcopy_fixed_types.cpp` | 手抄版固定 ll 的左偏树与优先队列对拍，pt 几何接口及 vector 存储检查 |
| `test_int128_io.py` / `int128_io.cpp` | 两版 Int128 的 cin/cout 读写，覆盖正负边界、显式符号、前导零、EOF 和 300 个随机整数 |

十四个回归测试文件直接引用 81 份完整源码。这些是有限的随机、边界与回归验证；两个目录共有 126 份 C++ 模板，并非每份旧片段、每个扩展接口均有测试。线性基旧 `Kth_Max` 存在越界且未规约，源码已标注请勿使用，不属于受支持接口。

## 单独验证

```powershell
python tests/run_template_refactor.py
python tests/run_acm_variants.py
```

手抄版先用 `-DACM_VARIANT` 直接测试 `template_core.cpp`、`poly_pow_n2.cpp`、`handcopy_fixed_types.cpp`、`hk.cpp`、`bct.cpp`、`euler.cpp`、`lcs_bitset.cpp`、`relu.cpp`、`xor_equations.cpp` 和 `line_abc.cpp`；再原样复制 `src-acm/` 到临时目录以复用现有相对路径，执行回归文件。测试调用通过 `template_variant_types.h` 选择完整版的类型参数或手抄版的普通类名，并相应使用 int / ll 测试数据；测试不修改受测源码。已知有误的线性基旧 `Kth_Max` 不收入手抄版。

Linux / 支持对应运行库的编译器可额外启用内存和未定义行为检查：

```sh
python3 tests/run_all.py --sanitize
```

GitHub Actions 对两版分别执行这一检查，并检查手抄源码是否与生成器一致。

## 维护与性能实验

HK 与仓库 Dinic 的可选性能对比：`python tests/run_hk_benchmark.py`。
两者使用相同的固定种子图，覆盖稀疏、稠密、两侧不平衡、瓶颈和长交替路；
交替运行顺序，热身后取 7 次中位数，分别输出求解时间与包含构图的总时间。
HK 计入返回全部匹配边的开销，Dinic 只返回匹配数；生成输入图的时间不计入。
结果用于本机比较，不设置跨机器的速度断言。

DC3 与倍增 SA 的长串对比：`python tests/run_suffix_benchmark.py --output tests/suffix_benchmark.csv`。
覆盖 120 万、200 万、500 万字符的 26 字母随机串、二元随机串、全同串及 13 字符周期串；
预热后轮换顺序，取 5 次构造耗时中位数，逐项核对全部 `sa/rk/ht`，生成输入、核对和析构不计时。
同时测现成倍增模板（含 ST）及仅在临时副本移除 ST 构建的倍增版本，原模板不修改。

修改完整源码后同步手抄版：

```powershell
python tools/build_acm_sources.py
python tests/run_all.py
```

`run_template_optimization.py` 和 `run_range_add_sum_benchmark.py` 是按需运行的性能实验，不属于默认正确性测试。前者读取历史提交 `592e414`，需要保留该历史的 Git 检出。
