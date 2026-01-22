cmake_minimum_required(VERSION 3.26)

project(hello_gui
    LANGUAGES CXX RC
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Release by default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()

add_executable(hello_gui WIN32
    win-main.cpp
)

set_target_properties(hello_gui PROPERTIES
    WIN32_EXECUTABLE TRUE
    CMAKE_MSVC_RUNTIME_LIBRARY ""
)

target_link_directories(hello_gui PRIVATE
    /Users/pawel/SDKs/MSVC/14.39.33519/lib/x64
    /Users/pawel/SDKs/Win/10/Lib/10.0.22621.0/ucrt/x64
    /Users/pawel/SDKs/Win/10/Lib/10.0.22621.0/um/x64
)

# Release semantics
target_compile_definitions(hello_gui PRIVATE
    NDEBUG
)

# Include paths (match manual build)
target_include_directories(hello_gui SYSTEM PRIVATE
    /Users/pawel/SDKs/MSVC/14.39.33519/include
    /Users/pawel/SDKs/Win/10/Include/10.0.22621.0/ucrt
    /Users/pawel/SDKs/Win/10/Include/10.0.22621.0/shared
    /Users/pawel/SDKs/Win/10/Include/10.0.22621.0/um
    /opt/homebrew/opt/llvm/include/c++/v1
)

# Match your manual compile flags
target_compile_options(hello_gui PRIVATE
    -O2
    -fno-exceptions
    -fno-rtti
    -nostdinc++
)

# Linker options
target_link_options(hello_gui PRIVATE
    "LINKER:/entry:WinMainCRTStartup"
)

find_package(ZLIB CONFIG REQUIRED)

# Libraries (dynamic CRT)
target_link_libraries(hello_gui PRIVATE
    user32
    kernel32
    vcruntime
    ucrt
    msvcrt
    ZLIB::ZLIB
)
