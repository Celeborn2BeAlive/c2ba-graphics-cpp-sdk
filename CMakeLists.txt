cmake_minimum_required(VERSION 3.14)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/third-party/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

if (NOT EXISTS ${CMAKE_TOOLCHAIN_FILE})
    message(FATAL_ERROR "CMake toolchain file for vcpkg not found. Run the script to setup third parties first.")
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(c2ba-graphics-cpp-sdk)

find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(cxxopts CONFIG REQUIRED)

# Glad library 

file(
    GLOB_RECURSE
    GLAD_SRC_FILES
    third-party/glad/*.c third-party/glad/*.h
)

add_library(
    glad
	STATIC
    ${GLAD_SRC_FILES}
)

target_include_directories(
    glad
    PUBLIC
    third-party/glad/include
)

# List of all third party libraries to link to c2ba

set(
    THIRD_PARTY_LIBRARIES
    glad
    OpenGL::GL
    glfw
    imgui::imgui
    nlohmann_json nlohmann_json::nlohmann_json
    glm
    fmt::fmt
    fmt::fmt-header-only
    cxxopts::cxxopts
)

# c2ba library, to share code between apps

file(
    GLOB_RECURSE
    C2BA_SRC_FILES
    libs/c2ba/*.cpp libs/c2ba/*.hpp
	third-party/imgui_impl/*.cpp third-party/imgui_impl/*.h 
)

add_library(
	c2ba
	STATIC
	${C2BA_SRC_FILES}
)

target_include_directories(
	c2ba
	PUBLIC
	libs/c2ba/include
    ${OPENGL_INCLUDE_DIR}
	PRIVATE
	libs/c2ba/src
	third-party/imgui_impl
)

target_link_libraries(
	c2ba
	PUBLIC
	${THIRD_PARTY_LIBRARIES}
)

target_compile_definitions(
	c2ba
	PUBLIC
	IMGUI_IMPL_OPENGL_LOADER_GLAD
)

install(
	TARGETS c2ba
	LIBRARY DESTINATION lib
)

install(DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>/
	DESTINATION bin
	FILES_MATCHING PATTERN "*.dll"
 )

# Applications

file(GLOB APP_DIRECTORIES "apps/*")
foreach(DIR ${APP_DIRECTORIES})
    get_filename_component(APP ${DIR} NAME)

    file(
        GLOB_RECURSE
        SRC_FILES
        apps/${APP}/*.cpp apps/${APP}/*.hpp apps/${APP}/*.glsl apps/${APP}/assets/*
    )

    add_executable(
        ${APP}
        ${SRC_FILES}
    )

    target_link_libraries(
        ${APP}
        PRIVATE
        c2ba
    )

    install(
        TARGETS ${APP}
        RUNTIME DESTINATION bin
    )

    # c2ba_add_shader_directory(${DIR}/shaders ${SHADER_OUTPUT_PATH}/${APP})
    # c2ba_add_assets_directory(${DIR}/assets ${ASSET_OUTPUT_PATH}/${APP})

    # install(
    #     DIRECTORY ${DIR}/shaders/
    #     DESTINATION shaders/${APP}
    #     FILES_MATCHING PATTERN "*.glsl"
    # )
endforeach()