if (NOT SRC_PATH)
    message(FATAL_ERROR "Please provide SRC_PATH argument.")
endif()

find_program(CLANG_PROGRAM clang-format)

if (NOT CLANG_PROGRAM)
    message(FATAL_ERROR "clang-format not found on this system.")
endif()

file(GLOB_RECURSE SRC_FILES ${SRC_PATH}/*.cpp ${SRC_PATH}/*.hpp ${SRC_PATH}/*.c ${SRC_PATH}/*.h ${SRC_PATH}/*.glsl)

foreach (FILE ${SRC_FILES})
    message("Formatting file ${FILE}...")
    execute_process(COMMAND ${CLANG_PROGRAM} -i ${FILE})
endforeach()
