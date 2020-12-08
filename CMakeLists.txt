cmake_minimum_required(VERSION 3.0)

project(multiconf VERSION 0.1)
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -pedantic -g")

add_executable(multiconf src/main.cpp)
