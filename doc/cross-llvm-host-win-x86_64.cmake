set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

set(CMAKE_C_COMPILER   /opt/homebrew/opt/llvm/bin/clang-cl)
set(CMAKE_CXX_COMPILER /opt/homebrew/opt/llvm/bin/clang-cl)
set(CMAKE_RC_COMPILER  /opt/homebrew/opt/llvm/bin/llvm-rc)

set(CMAKE_C_COMPILER_TARGET   x86_64-pc-windows-msvc)
set(CMAKE_CXX_COMPILER_TARGET x86_64-pc-windows-msvc)

set(WINSDK_ROOT /Users/pawel/SDKs/Win/10)
set(MSVC_ROOT   /Users/pawel/SDKs/MSVC/14.39.33519)

set(WINSDK_VER 10.0.22621.0)

set(WINSDK_INCLUDE
    ${MSVC_ROOT}/include
    ${WINSDK_ROOT}/Include/${WINSDK_VER}/ucrt
    ${WINSDK_ROOT}/Include/${WINSDK_VER}/shared
    ${WINSDK_ROOT}/Include/${WINSDK_VER}/um
    ${WINSDK_ROOT}/Include/${WINSDK_VER}/winrt
)

set(WINSDK_LIB
    ${MSVC_ROOT}/lib/x64
    ${WINSDK_ROOT}/Lib/${WINSDK_VER}/ucrt/x64
    ${WINSDK_ROOT}/Lib/${WINSDK_VER}/um/x64
)

include_directories(SYSTEM ${WINSDK_INCLUDE})
link_directories(${WINSDK_LIB})
