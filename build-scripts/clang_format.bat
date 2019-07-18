set PATH_TO_ROOT=%~dp0..\
set PATH_TO_CMAKE_SCRIPT=%~dp0clang_format.cmake

cmake -DSRC_PATH=%PATH_TO_ROOT%apps -P %PATH_TO_CMAKE_SCRIPT%
cmake -DSRC_PATH=%PATH_TO_ROOT%libs -P %PATH_TO_CMAKE_SCRIPT%

pause