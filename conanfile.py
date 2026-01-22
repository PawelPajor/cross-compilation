from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout

class HelloGuiConan(ConanFile):
    name = "hello_gui"
    version = "0.1"

    settings = "os", "arch", "compiler", "build_type"

    requires = (
        "zlib/1.3.1",
    )

    generators = (
        "CMakeToolchain",
        "CMakeDeps",
    )

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
