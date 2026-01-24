# Profiles

- `cross-ninja-llvm-build`

```ini
[settings]
os=Macos
arch=armv8
compiler=clang
compiler.version=20
compiler.cppstd=23
compiler.libcxx=libc++
build_type=Release

[conf]
tools.cmake.cmaketoolchain:generator=Ninja

[buildenv]
CC=/opt/homebrew/opt/llvm/bin/clang
CXX=/opt/homebrew/opt/llvm/bin/clang++
```

- `cross-ninja-llvm-host-win64`

```ini
[settings]
os=Windows
arch=x86_64
compiler=clang
compiler.version=20
compiler.cppstd=23
compiler.runtime=dynamic
build_type=Release

[conf]
tools.cmake.cmaketoolchain:generator=Ninja
tools.cmake.cmaketoolchain:system_name=Windows
```
