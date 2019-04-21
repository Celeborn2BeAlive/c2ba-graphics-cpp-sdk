set PATH_TO_CMAKE_SCRIPT=%~dp0build_third_party.cmake
set PATH_TO_VCPKG_ROOT=%~dp0..\third-party\vcpkg

cmake -DVCPKG_3RDPARTY_ROOT=%PATH_TO_VCPKG_ROOT% -DVCPKG_3RDPARTY_TRIPLET=x64-windows -P %PATH_TO_CMAKE_SCRIPT%

pause