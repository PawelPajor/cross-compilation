#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <zlib.h>
#include <string>

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE,
    LPSTR,
    int)
{
    const char* input = "Hello from zlib!";
    const uLong input_len = static_cast<uLong>(strlen(input));

    uLongf compressed_len = compressBound(input_len);
    std::string compressed;
    compressed.resize(compressed_len);

    int res = compress(
        reinterpret_cast<Bytef*>(compressed.data()),
        &compressed_len,
        reinterpret_cast<const Bytef*>(input),
        input_len
    );

    char buffer[256];

    if (res == Z_OK)
    {
        wsprintfA(
            buffer,
            "zlib OK!\nOriginal: %lu bytes\nCompressed: %lu bytes",
            input_len,
            compressed_len
        );
    }
    else
    {
        wsprintfA(
            buffer,
            "zlib failed! Error code: %d",
            res
        );
    }

    MessageBoxA(
        nullptr,
        buffer,
        "Hello + zlib",
        MB_OK | MB_ICONINFORMATION
    );

    return 0;
}