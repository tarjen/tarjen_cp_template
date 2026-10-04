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

在仓库根目录运行回归测试（需要Python 3和g++）：

```powershell
python tests/run_template_refactor.py
```
