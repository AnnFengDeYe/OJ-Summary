# --- 项目基础设置 ---
cmake_minimum_required(VERSION 3.10)
project(DynamicStaticLib CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- 查找所有在当前根目录下的 .cpp 文件 (不包括子目录) ---
file(GLOB ROOT_SOURCE_FILES
        LIST_DIRECTORIES false
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

foreach(CPP_FILE ${ROOT_SOURCE_FILES})
    get_filename_component(EXECUTABLE_NAME ${CPP_FILE} NAME_WE)
    add_executable(${EXECUTABLE_NAME} ${CPP_FILE})
endforeach()


# --- 处理 StaticDemo_X 子目录 (自动创建静态库) ---
file(GLOB DEMO_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/StaticDemo_*")

foreach(DEMO_DIR ${DEMO_DIRS})
    get_filename_component(DEMO_NAME ${DEMO_DIR} NAME)
    set(LIB_NAME "${DEMO_NAME}_lib")
    set(EXE_NAME "${DEMO_NAME}_main")

    file(GLOB DEMO_ALL_SOURCES "${DEMO_DIR}/*.cpp")
    set(EXE_SOURCE "${DEMO_DIR}/main.cpp")
    set(LIB_SOURCES ${DEMO_ALL_SOURCES})
    list(REMOVE_ITEM LIB_SOURCES ${EXE_SOURCE}) # 从列表中移除 main.cpp

    add_library(${LIB_NAME} STATIC ${LIB_SOURCES})

    target_include_directories(${LIB_NAME} PUBLIC ${DEMO_DIR})

    add_executable(${EXE_NAME} ${EXE_SOURCE})

    target_link_libraries(${EXE_NAME} ${LIB_NAME})
endforeach()

# --- 处理 DynamicDemo_X 子目录 (自动创建动态库) ---
file(GLOB DYNAMIC_DEMO_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/DynamicDemo_*")

foreach(DEMO_DIR ${DYNAMIC_DEMO_DIRS})
    get_filename_component(DEMO_NAME ${DEMO_DIR} NAME)
    set(LIB_NAME "${DEMO_NAME}_lib")
    set(EXE_NAME "${DEMO_NAME}_main")

    file(GLOB DEMO_ALL_SOURCES "${DEMO_DIR}/*.cpp")
    set(EXE_SOURCE "${DEMO_DIR}/main.cpp")
    set(LIB_SOURCES ${DEMO_ALL_SOURCES})
    list(REMOVE_ITEM LIB_SOURCES ${EXE_SOURCE}) # 从列表中移除 main.cpp

    # 使用 SHARED 关键字替代 STATIC
    add_library(${LIB_NAME} SHARED ${LIB_SOURCES})

    target_include_directories(${LIB_NAME} PUBLIC ${DEMO_DIR})

    add_executable(${EXE_NAME} ${EXE_SOURCE})

    target_link_libraries(${EXE_NAME} ${LIB_NAME})
endforeach()