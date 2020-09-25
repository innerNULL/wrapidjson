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


include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/src/)
include_directories(${PROJECT_SOURCE_DIR}/include/)


set(CHECKER_DEMO demo/checker_demo.cpp)
add_executable(checker_demo ${CHECKER_DEMO})
set(HANDLER_N_QUERIER_DEMO demo/handler_n_querier_demo.cpp)
add_executable(handler_n_querier_demo ${HANDLER_N_QUERIER_DEMO})
set(IO_HELPER_DEMO demo/io_helper_demo.cpp)
add_executable(io_helper_demo ${IO_HELPER_DEMO})

