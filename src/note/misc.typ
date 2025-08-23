== 火车头
```cpp
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
```

== 编译参数
- `-D_GLIBCXX_DEBUG` `-D_GLIBCXX_DEBUG_PEDANTIC`: STL debug mode
- `-fsanitize=address` : 内存错误检查
- `-fsanitize=undefined` `-fno-sanitize-recover`: UB 检查
```sh
g++ -Wall -Wextra -pedantic -std=gnu++20 -O2 \
  -Wshadow -Wformat=2 -Wfloat-equal -Wconversion \
  -Wlogical-op -Wshift-overflow=2 \
  -Wduplicated-cond -Wcast-qual -Wcast-align \
  -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 \
  -fsanitize=address -fsanitize=undefined -fno-sanitize-recover \
  -fstack-protector
```
