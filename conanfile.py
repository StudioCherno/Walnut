from conans import ConanFile, CMake


class Walnut(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = ("glfw/3.3.2", "stb/20200203", "imgui/latest@nisaldilshan/docking", "glm/0.9.9.8", "moltenvk/1.2.2")
    generators = "cmake"
    build_policy = "missing"