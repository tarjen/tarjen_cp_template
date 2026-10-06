# tarjen cp template

[![Build Typst document](https://github.com/tarjen/tarjen_cp_template/actions/workflows/build.yml/badge.svg)](https://github.com/tarjen/tarjen_cp_template/actions/workflows/build.yml)

特此鸣谢cubercsl提供的typst模板

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

本机安装位置为 `C:\Users\tarjen\AppData\Local\Programs\Typst\typst.exe`，桌面原模板库路径与 `code/tarjen_cp_template` 子模块指向同一份代码。

GitHub Actions 在 Ubuntu 24.04 上安装 Noto CJK 与 Liberation 字体，使用同一 Typst 版本编译；PDF 可在每次成功构建的 `template-pdf` artifact 中下载，推送标签时也会上传到 Release。

2026年10月6日修复了 `NTT.cpp` 与实际文件 `ntt.cpp` 的大小写不一致，更新了已停用的 artifact 下载步骤，并固定构建系统与编译器版本。
