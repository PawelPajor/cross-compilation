from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout

class HelloGuiConan(ConanFile):
    name = "hello_gui"
    version = "0.1"
    settings = "os", "arch", "compiler", "build_type"
    requires = "sdl/3.2.20"
    generators = "CMakeToolchain", "CMakeDeps"

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
