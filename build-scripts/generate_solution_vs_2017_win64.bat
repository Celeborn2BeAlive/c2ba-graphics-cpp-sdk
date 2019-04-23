set PATH_TO_ROOT=%~dp0..\

if defined CMAKE_BUILDS_ROOT (
    set PATH_TO_BUILD=%CMAKE_BUILDS_ROOT%\c2ba-graphics-cpp-sdk-build-vs-2017-win64
    set PATH_TO_INSTALL=%CMAKE_BUILDS_ROOT%\c2ba-graphics-cpp-sdk-install
) else (
    set PATH_TO_BUILD=%PATH_TO_ROOT%\cmake-build
    set PATH_TO_INSTALL=%PATH_TO_ROOT%\cmake-install
)

if not exist %PATH_TO_BUILD% mkdir %PATH_TO_BUILD%

pushd %PATH_TO_BUILD%

cmake -G "Visual Studio 15 2017 Win64" -DCMAKE_INSTALL_PREFIX=%PATH_TO_INSTALL% %PATH_TO_ROOT%

popd

pause