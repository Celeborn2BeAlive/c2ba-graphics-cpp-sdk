# c2ba-graphics-cpp-sdk

My SDK for computer graphics applications in C++

# How to build

For now, only build scripts for windows have been written, but they are only calling cmake scripts with correct arguments so it should not be hard to write equivalent bash scripts.

## Building dependencies

Most of third party libraries are built with vcpkg. Run build-scripts/build_third_party_vs_2017_win64.bat (from inside the directory build-scripts) to build all dependencies. The vcpkg build tree is third-party/vcpkg.

## Creating/Updating the solution

Run the script build-scripts§generate_solution_vs_2017_win64.bat to generate the solution in the folder cmake-build at the repository root. You can also generate the solution manually with cmake. If you defined the environement variable CMAKE_BUILDS_ROOT, then the solution is created in %CMAKE_BUILDS_ROOT%\c2ba-graphics-cpp-sdk-build-vs-2017-win64 and the install path is set to %CMAKE_BUILDS_ROOT%\c2ba-graphics-cpp-sdk-install.

## Building

Just open the solution with Visual Studio and build the project.

# Todo

## Building

- Handle glsl file copy in CMakeLists.txt
- Handle newer version of Visual Studio
- Script to run the whole process: dependency building, solution generation, build and install

## Sample application

- display a cube with basic shader
- 2 camera: trackball and freefly, that can be selected from the GUI
- background color from GUI
