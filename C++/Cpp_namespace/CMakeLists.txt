cmake_minimum_required(VERSION 3.12)
project(Cpp_namespace CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_BUILD_RPATH "@loader_path")
set(CMAKE_INSTALL_RPATH "@loader_path")

add_library(MyLib_v1 SHARED lib_v1/my_math.cpp)
target_include_directories(MyLib_v1 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib_v1)

add_executable(app_v1 app_v1/main.cpp)
target_link_libraries(app_v1 PRIVATE MyLib_v1)

add_library(MyLib_v2 SHARED lib_v2/my_math.cpp)
target_include_directories(MyLib_v2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib_v2)

add_executable(app_v2 app_v2/main.cpp)
target_link_libraries(app_v2 PRIVATE MyLib_v2)


file(GLOB MAIN_FILES "${CMAKE_CURRENT_SOURCE_DIR}/main*.cpp")

foreach(CPP_FILE ${MAIN_FILES})
    get_filename_component(EXECUTABLE_NAME ${CPP_FILE} NAME_WE)
    add_executable(${EXECUTABLE_NAME} ${CPP_FILE})
endforeach()