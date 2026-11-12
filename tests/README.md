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
| `template_refactor.cpp` | 36 个模板，覆盖树状数组、线段树、字符串、图论等；另运行 76 组非法线段树输入检查断言 |
| `template_refactor_third.cpp` | 27 个模板，覆盖可持久化结构、节点池扩容、树结构、数论、矩阵、递推、费用流等 |
| `template_indexing.cpp` | 8 个模板的下标迁移、边界与朴素结果对照 |
| `template_dynamic_diameter.cpp` | 动态树直径与朴素全点对距离对照 |
| `handcopy_fixed_types.cpp` | 手抄版固定 ll 的左偏树与优先队列对拍，point_t 几何接口及 vector 存储检查 |

六个测试文件直接引用 74 份完整源码。这些是有限的随机、边界与回归验证；两个目录共有 127 份 C++ 模板，并非每份旧片段、每个扩展接口均有测试。线性基旧 `Kth_Max` 存在越界且未规约，源码已标注请勿使用，不属于受支持接口。

## 单独验证

```powershell
python tests/run_template_refactor.py
python tests/run_acm_variants.py
```

手抄版先用 `-DACM_VARIANT` 直接测试 `template_core.cpp`、`poly_pow_n2.cpp` 和 `handcopy_fixed_types.cpp`；再原样复制 `src-acm/` 到临时目录以复用现有相对路径，执行原有六个回归文件。测试调用通过 `template_variant_types.h` 选择完整版的类型参数或手抄版的普通类名，并相应使用 int / ll 测试数据；测试不修改受测源码。已知有误的线性基旧 `Kth_Max` 不收入手抄版。

Linux / 支持对应运行库的编译器可额外启用内存和未定义行为检查：

```sh
python3 tests/run_all.py --sanitize
```

GitHub Actions 对两版分别执行这一检查，并检查手抄源码是否与生成器一致。

## 维护与性能实验

修改完整源码后同步手抄版：

```powershell
python tools/build_acm_sources.py
python tests/run_all.py
```

`run_template_optimization.py` 和 `run_range_add_sum_benchmark.py` 是按需运行的性能实验，不属于默认正确性测试。前者读取历史提交 `592e414`，需要保留该历史的 Git 检出。
