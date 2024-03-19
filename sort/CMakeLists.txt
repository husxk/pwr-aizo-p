cmake_minimum_required(VERSION 3.13)

project(sort CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_BUILD_TYPE RELEASE)

add_compile_options(
        "-Wall"
        )

add_executable(
        ${PROJECT_NAME}
        sort.cpp
        )

target_include_directories(
        sort PRIVATE
        include/
        source/
        )
