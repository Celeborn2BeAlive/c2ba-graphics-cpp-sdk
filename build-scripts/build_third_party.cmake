# Specify third party libraries to build with vcpkg. Should be run with cmake -P. Variables VCPKG_3RDPARTY_ROOT and VCPKG_3RDPARTY_TRIPLET must be defined.

include(cmake/Vcpkg3rdParty.cmake)

vcpkg_init()

# GLFW for window management
vcpkg_require(
    PACKAGE glfw3
    VERSION 3.2.1-3
)

# Dear ImGui for graphical user interface
vcpkg_require(
    PACKAGE imgui
    VERSION 1.69
)

# Nlhohmann Json to handle simple input and output files
vcpkg_require(
    PACKAGE nlohmann-json
    VERSION 3.6.1
)

# GLM for mathematics
vcpkg_require(
    PACKAGE glm
    VERSION 0.9.9.4
)

# stb for loading images
vcpkg_require(
    PACKAGE stb
    VERSION 2018-03-02
)

# fmt for formatting output
vcpkg_require(
    PACKAGE fmt
    VERSION 5.3.0-1
)

vcpkg_require(
    PACKAGE cxxopts
    VERSION 2.1.1
)

vcpkg_install()