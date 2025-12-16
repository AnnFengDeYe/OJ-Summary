cmake_minimum_required(VERSION 3.10)
project(CppTutorial)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

foreach(CPP_FILE ${SOURCE_FILES})
    get_filename_component(EXECUTABLE_NAME ${CPP_FILE} NAME_WE)
    add_executable(${EXECUTABLE_NAME} ${CPP_FILE})

endforeach()