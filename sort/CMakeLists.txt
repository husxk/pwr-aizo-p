cmake_minimum_required(VERSION 3.13)

project(sort CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE RELEASE)

#add_compile_options(
#                -Wall -Wextra -fstack-protector-all -fsanitize=address
#        -g 
#        )
#
#add_link_options(
#                -fsanitize=address
#        )

file(GLOB src
     ./source/*.cpp
     )

add_executable(
        ${PROJECT_NAME}
        sort.cpp
        ${src}
        )

target_include_directories(
        ${PROJECT_NAME} PRIVATE
        ./include/
        )

