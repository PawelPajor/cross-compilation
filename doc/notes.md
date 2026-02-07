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
  - [Win arm64 + x86\_64](#win-arm64--x86_64)
  - [Build files](#build-files)
    - [Toolchains](#toolchains)
    - [Profiles](#profiles-1)
  - [Toolchains](#toolchains-1)


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
conan create sdl \
  --profile:build=cross-ninja-llvm-build \
  --profile:host=cross-ninja-llvm-host-win64 \
  --version=3.2.20 \
  --build=missing

conan cache path sdl/3.2.20

conan download sdl/3.2.20 -r=conancenter --only-recipe

conan remove sdl/3.2.20 -c

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

- `~/.conan2/profiles/cross-ninja-llvm-host-arm64`
- `~/.conan2/profiles/cross-ninja-llvm-host-win64`
- `~/.conan2/profiles/cross-ninja-llvm-build`

## Win arm64 + x86_64

```sh

# Base:

# supported values: `ninja`
export GENERATOR=ninja

# supported values: `llvm`
export COMPILER=llvm

# supported values: `win`
export OS=win

# supported values: `arm64`, `x86_64`
export ARCH=arm64

# supported values: `release`, `debug`
export BLD_TYPE=release

# Build aliases:

alias arm='export ARCH=arm64'
alias x64='export ARCH=x86_64'
alias dbg='export BLD_TYPE=debug'
alias rel='export BLD_TYPE=release'

alias inst='conan install . --profile:build=cross-${GENERATOR}-${COMPILER}-build --profile:host=cross-${GENERATOR}-${COMPILER}-host-${OS}-${ARCH}-${BLD_TYPE} --output-folder=cmake-build-${OS}-${ARCH}-${BLD_TYPE} --build=missing'
alias cmk='cmake --preset conan-${OS}-${ARCH}-${BLD_TYPE}'
alias bld='cmake --build cmake-build-${OS}-${ARCH}-${BLD_TYPE} --preset conan-${OS}-${ARCH}-${BLD_TYPE}'
alias cln='rm -rf cmake-build-* CMakeUserPresets.json'

# Git aliases

alias ga='git add .'
alias gb='git checkout -b'
alias gcm='git commit -m'
alias gca='git commit --amend --no-edit'
alias gl='git log --oneline'
alias gp='git push'
alias gs='git status'

```

## Build files

### Toolchains

- [cross-llvm-host-win-arm64.cmake](cross-llvm-host-win-arm64.cmake)
- [cross-llvm-host-win-x86_64.cmake](cross-llvm-host-win-x86_64.cmake)

### Profiles

- [cross-ninja-llvm-build](cross-ninja-llvm-build)
- [cross-ninja-llvm-host-win-arm64-debug](cross-ninja-llvm-host-win-arm64-debug)
- [cross-ninja-llvm-host-win-arm64-release](cross-ninja-llvm-host-win-arm64-release)
- [cross-ninja-llvm-host-win-x86_64-debug](cross-ninja-llvm-host-win-x86_64-debug)
- [cross-ninja-llvm-host-win-x86_64-release](cross-ninja-llvm-host-win-x86_64-release)

## Toolchains

- `~/.cmake_toolchains/windows-llvm.cmake`