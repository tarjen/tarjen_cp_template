# tarjen cp template

[![Build Typst document](https://github.com/tarjen/tarjen_cp_template/actions/workflows/build.yml/badge.svg)](https://github.com/tarjen/tarjen_cp_template/actions/workflows/build.yml)

特此鸣谢cubercsl提供的typst模板

## 两个源码目录

两版放在同一分支，按用途选择目录：

| 用途 | 源码目录 | PDF 入口 |
| --- | --- | --- |
| 完整封装版：保留完整接口、断言、使用示例及回归测试 | [`src/`](src/) | `main-copy.typ`（`main.typ` 兼容同一内容） |
| 赛时手抄版：结构体使用固定值类型，保留 vector、说明注释与压行 | [`src-acm/`](src-acm/) | `main-acm.typ` |

两目录现有 126 份 C++ 模板一一对应；手抄 PDF 与完整版完整收录同一目录，包含全部模板、工具和笔记。具体差异见[版本说明](版本说明.md)和[源码改动清单](ACM源码改动清单.md)。

一条命令验证两版（Python 3、g++，C++17）：

```powershell
python tests/run_all.py
```

对拍统一使用 [`src/prepare/duipai.py`](src/prepare/duipai.py)，两版目录共用此脚本，旧 C++、BAT 版本已移除。
先编译生成器、标程和待测程序，然后在程序所在目录运行：

```powershell
python <模板库路径>/src/prepare/duipai.py
```

默认运行 `testin`、`abiaocheng`、`nedtest`（Windows 自动加 `.exe`），最多 100000 组，单次超时 2 秒。
脚本共 10 行；程序名直接改三条运行命令，组数和超时直接改常数。
忽略空白差异，WA 时停止并保留 `data.txt`、`biaoda.txt`、`aatest.txt`；程序报错或超时直接抛出异常停止。

测试范围和单独运行方法见 [tests/README.md](tests/README.md)。维护时先修改 `src/`，再运行 `python tools/build_acm_sources.py` 同步手抄版，最后运行测试。

## 左右分屏查看代码

双击仓库根目录的 `查看模板对照.bat`，或运行：

```powershell
python tools/build_compare_view.py --open
```

离线页面左侧显示完整封装版，右侧显示赛时手抄版，支持模板搜索、差异对齐、同步滚动、复制源码和调节分屏宽度。启动时自动生成最新快照，修改源码后重新运行即可更新。详细操作见 [viewer/README.md](viewer/README.md)。

= 第零章

- 安装 `typst`:
  - Linux, macOS, WSL

    ```bash
    curl -fsSL https://typst.community/typst-install/install.sh | sh
    ```
  - Windows

    ```ps1
    irm https://typst.community/typst-install/install.ps1 | iex
    ```

- 安装 VSCode 插件 `tinymist`:
  - 打开 VSCode
  - 搜索 `tinymist` 安装插件

## 模板改造与验证

2026年10月4日同步完成63个模板的对象封装与动态存储改造。完整文件清单、构造方式、接口变化和使用条件见[模板改造说明](模板改造说明.md)。新增模板已加入Typst目录。

120 份算法文件开头已补使用说明：先看 `// 用法：` 中的创建对象、调用示例、下标约定和返回值。题目片段及旧代码的缺失接口也会注明；本轮文件清单与验证范围见[模板改造说明](模板改造说明.md)。

在仓库根目录运行回归测试（需要Python 3和g++）：

```powershell
python tests/run_template_refactor.py
```

## 编译 PDF

构建使用 Typst 0.15.1，在模板库根目录执行：

```powershell
typst compile main.typ main.pdf
```

请先将 Typst 加入 PATH，再执行上述命令。

GitHub Actions 在 Ubuntu 24.04 上安装 Noto CJK 与 Liberation 字体，使用同一 Typst 版本编译三份 PDF；可在每次成功构建的 `template-pdf` artifact 中下载，推送标签时也会上传到 Release。独立测试工作流会分别验证完整版和手抄版，并启用 AddressSanitizer / UndefinedBehaviorSanitizer。

2026年10月6日修复了 `NTT.cpp` 与实际文件 `ntt.cpp` 的大小写不一致，更新了已停用的 artifact 下载步骤，并固定构建系统与编译器版本。

## 两种模板版本

- `main-copy.typ`：复制黏贴版，完整收录当前模板目录；原有 `main.typ` 保持兼容。
- `main-acm.typ`：ACM 赛时抄写版，完整收录全部模板、赛前工具与笔记，目录顺序与完整版一致。

```powershell
typst compile main-copy.typ main-copy.pdf
typst compile main-acm.typ main-acm.pdf
```

两版共用 `template.typ`；复制黏贴版读取 `src/`，赛时抄写版读取一一对应的 `src-acm/`。赛时版保留原有接口、断言和说明注释，合并相邻同类调用，并省略非必要的显式构造与内联修饰。
