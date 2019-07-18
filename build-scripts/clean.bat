set PATH_TO_ROOT=%~dp0..\

rmdir /s /q %PATH_TO_ROOT%cmake-build
rmdir /s /q %PATH_TO_ROOT%cmake-install
rmdir /s /q %PATH_TO_ROOT%third-party\vcpkg