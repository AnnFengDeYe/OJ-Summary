cmake_minimum_required(VERSION 3.10)
project(Cpp_SmartPtrs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# 遍历每一个找到的源文件
foreach(CPP_FILE ${SOURCE_FILES})
    get_filename_component(EXECUTABLE_NAME ${CPP_FILE} NAME_WE)
    add_executable(${EXECUTABLE_NAME} ${CPP_FILE})
endforeach()
