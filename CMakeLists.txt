# 2020-07-25

cmake_minimum_required(VERSION 3.12.4)
project(wrapidjson C CXX)
enable_testing()
set(CMAKE_MACOSX_RPATH 1)


if(UNIX AND NOT APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
elseif(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif()


# Download cmakeup as pkg management.
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/build/main.zip")
    message(STATUS "cmakeup has been downloaded.")
else()
    execute_process(
        COMMAND wget https://github.com/innerNULL/cmakeup/archive/refs/heads/main.zip
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
    execute_process(
        COMMAND unzip main.zip WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
endif()


set(CMKAEUP_ROOT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/build/cmakeup-main/cmakeup")
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMKAEUP_ROOT_PATH}/module")
include(cmakeup)
cmakeup_init("${CMAKE_CURRENT_SOURCE_DIR}/build/_cmakeup_hub" "https://ghproxy.com/https://github.com")
cmakeup_root_path_register(${CMKAEUP_ROOT_PATH})

cmakeup_pkg_cmake_importer("Tencent" "rapidjson")
cmakeup_integrate_Tencent_rapidjson("master" "null" "global")


#include_directories(${PROJECT_SOURCE_DIR}/include/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)


set(CHECKER_DEMO demo/checker_demo.cpp)
add_executable(checker_demo ${CHECKER_DEMO})
set(HANDLER_N_QUERIER_DEMO demo/handler_n_querier_demo.cpp)
add_executable(handler_n_querier_demo ${HANDLER_N_QUERIER_DEMO})
set(IO_HELPER_DEMO demo/io_helper_demo.cpp)
add_executable(io_helper_demo ${IO_HELPER_DEMO})

