#import "template.typ": *

// Take a look at the file `template.typ` in the file panel
// to customize this template and discover how it works.
#show: project.with(
  title: "Standard Code Library",
  authors: (
    "牛逼大学 塔尖",
  ),
  logo: "logo.png",
)

// auto pagebreak after each section
#show heading.where(level: 1): it => {
  pagebreak(weak: true)
  it
}

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

= 第一章
== 第一节
#import_code("src/example.cc")

== 第二节
#import_code("src/example.py")

= 第二章
== 第一节
#import_code("src/example.cc")

== 第二节
#import_code("src/example.py")
