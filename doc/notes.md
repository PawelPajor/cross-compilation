# Notes

- [Notes](#notes)
  - [With cmake (1st attempt)](#with-cmake-1st-attempt)
  - [Manual](#manual)
    - [Compilation](#compilation)
    - [Linking](#linking)
      - [Static CRT](#static-crt)
      - [Dynamic RT](#dynamic-rt)
      - [Clear](#clear)
    - [Resource compilation](#resource-compilation)
    - [Win32 code compilation](#win32-code-compilation)
    - [Linking Win32 oobjects](#linking-win32-oobjects)
      - [Dynamic](#dynamic)
  - [With cmake (2nd attempt)](#with-cmake-2nd-attempt)
  - [With conan](#with-conan)
  - [Profiles](#profiles)
  - [Toolchains](#toolchains)


## With cmake (1st attempt)

```sh
# clean
rm -rf cmake-build-win

# run once
conan install . \
  --profile:build=cross-ninja-llvm-build \
  --profile:host=cross-ninja-llvm-win64 \
  --output-folder=cmake-build-win \
  --build=missing

# run when cmake needs updatind
cmake --preset conan-release

# build
cmake --build cmake-build-win
```


```sh
rm -rf cmake-build-win
conan install . \
  --profile:build=cross-ninja-llvm-build \
  --profile:host=cross-ninja-llvm-win64 \
  --output-folder=cmake-build-win \
  --build=missing
cmake --preset conan-release
cmake --build cmake-build-win

```

Failing

## Manual

### Compilation

Set path

```sh
export PATH=\
/opt/homebrew/opt/llvm/bin:\
/opt/homebrew/bin:\
/opt/homebrew/sbin:\
/usr/local/bin:\
/System/Cryptexes/App/usr/bin:\
/usr/bin:\
/bin:\
/usr/sbin:\
/sbin:\
/Library/Apple/usr/bin
```

```sh
clang++ \
  --target=x86_64-pc-windows-msvc \
  -std=c++23 \
  -O2 \
  -nostdinc++ \
  -isystem /Users/pawel/SDKs/MSVC/14.39.33519/include \
  -isystem /Users/pawel/SDKs/Win/10/Include/10.0.22621.0/ucrt \
  -isystem /Users/pawel/SDKs/Win/10/Include/10.0.22621.0/shared \
  -isystem /Users/pawel/SDKs/Win/10/Include/10.0.22621.0/um \
  -isystem /opt/homebrew/opt/llvm/include/c++/v1 \
  -c main.cpp \
  -o main.obj

alias cmpl='clang++ --target=x86_64-pc-windows-msvc -std=c++23 -O2 -nostdinc++ -isystem /Users/pawel/SDKs/MSVC/14.39.33519/include -isystem /Users/pawel/SDKs/Win/10/Include/10.0.22621.0/ucrt -isystem /Users/pawel/SDKs/Win/10/Include/10.0.22621.0/shared -isystem /Users/pawel/SDKs/Win/10/Include/10.0.22621.0/um -isystem /opt/homebrew/opt/llvm/include/c++/v1 -c main.cpp -o main.obj'
```

### Linking

#### Static CRT

```sh
lld-link \
  /subsystem:console \
  /entry:mainCRTStartup \
  /out:hello_s.exe \
  main.obj \
  /libpath:/Users/pawel/SDKs/MSVC/14.39.33519/lib/x64 \
  /libpath:/Users/pawel/SDKs/Win/10/Lib/10.0.22621.0/ucrt/x64 \
  /libpath:/Users/pawel/SDKs/Win/10/Lib/10.0.22621.0/um/x64 \
  libcmt.lib \
  libcpmt.lib \
  kernel32.lib

alias ln_s='lld-link /subsystem:console /entry:mainCRTStartup /out:hello_s.exe main.obj /libpath:/Users/pawel/SDKs/MSVC/14.39.33519/lib/x64 /libpath:/Users/pawel/SDKs/Win/10/Lib/10.0.22621.0/ucrt/x64 /libpath:/Users/pawel/SDKs/Win/10/Lib/10.0.22621.0/um/x64 libcmt.lib libcpmt.lib kernel32.lib'

```

#### Dynamic RT

```sh
lld-link \
  /subsystem:console \
  /entry:mainCRTStartup \
  /out:hello_d.exe \
  main.obj \
  /libpath:/Users/pawel/SDKs/MSVC/14.39.33519/lib/x64 \
  /libpath:/Users/pawel/SDKs/Win/10/Lib/10.0.22621.0/ucrt/x64 \
  /libpath:/Users/pawel/SDKs/Win/10/Lib/10.0.22621.0/um/x64 \
  msvcrt.lib \
  vcruntime.lib \
  ucrt.lib \
  kernel32.lib

alias ln_d='lld-link /subsystem:console /entry:mainCRTStartup /out:hello_d.exe main.obj /libpath:/Users/pawel/SDKs/MSVC/14.39.33519/lib/x64 /libpath:/Users/pawel/SDKs/Win/10/Lib/10.0.22621.0/ucrt/x64 /libpath:/Users/pawel/SDKs/Win/10/Lib/10.0.22621.0/um/x64 msvcrt.lib vcruntime.lib ucrt.lib kernel32.lib'
```

#### Clear

...


### Resource compilation

```sh
llvm-rc \
  -Wno-nonportable-include-path \
  -I /Users/pawel/SDKs/Win/10/Include/10.0.22621.0/ucrt \
  -I /Users/pawel/SDKs/Win/10/Include/10.0.22621.0/shared \
  -I /Users/pawel/SDKs/Win/10/Include/10.0.22621.0/um \
  -fo app.res \
  app.rc
```

### Win32 code compilation

```sh
clang++ \
  --target=x86_64-pc-windows-msvc \
  -std=c++23 \
  -O2 \
  -DNDEBUG \
  -fno-exceptions \
  -fno-rtti \
  -nostdinc++ \
  -isystem /Users/pawel/SDKs/MSVC/14.39.33519/include \
  -isystem /Users/pawel/SDKs/Win/10/Include/10.0.22621.0/ucrt \
  -isystem /Users/pawel/SDKs/Win/10/Include/10.0.22621.0/shared \
  -isystem /Users/pawel/SDKs/Win/10/Include/10.0.22621.0/um \
  -isystem /opt/homebrew/opt/llvm/include/c++/v1 \
  -c win-main.cpp \
  -o win-main.obj
```

### Linking Win32 oobjects

#### Dynamic

```sh
lld-link \
  /subsystem:windows \
  /entry:WinMainCRTStartup \
  /out:hello_gui_d.exe \
  win-main.obj \
  app.res \
  /libpath:/Users/pawel/SDKs/MSVC/14.39.33519/lib/x64 \
  /libpath:/Users/pawel/SDKs/Win/10/Lib/10.0.22621.0/ucrt/x64 \
  /libpath:/Users/pawel/SDKs/Win/10/Lib/10.0.22621.0/um/x64 \
  msvcrt.lib \
  vcruntime.lib \
  ucrt.lib \
  user32.lib \
  kernel32.lib
```

```
.
├── CMakeLists.txt
├── toolchains
│   └── windows-llvm.cmake
├── win-main.cpp
├── app.rc
└── app.manifest
```

## With cmake (2nd attempt)

- Configure

```sh
cmake -S . -B build-win \
  -G Ninja \
  -DCMAKE_TOOLCHAIN_FILE=toolchains/windows-llvm.cmake \
  -DCMAKE_BUILD_TYPE=Release

alias configure='cmake -S . -B build-win -G Ninja -DCMAKE_TOOLCHAIN_FILE=toolchains/windows-llvm.cmake -DCMAKE_BUILD_TYPE=Release'
```

- Build

```sh
cmake --build build-win

alias build='cmake --build build-win'
```

## With conan

- Install

```sh
conan install . \
  --profile:build=cross-ninja-llvm-build \
  --profile:host=cross-ninja-llvm-host-win64 \
  --build=missing
```

- Configure

```sh
cmake --preset conan-release
```

- Build

```sh
cmake --build --preset conan-release
```

## Profiles

- `~/.conan2/profiles/cross-ninja-llvm-host-win64`
- `~/.conan2/profiles/cross-ninja-llvm-build`

## Toolchains

- `~/.cmake_toolchains/windows-llvm.cmake`