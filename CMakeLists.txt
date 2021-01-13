cmake_minimum_required(VERSION 3.12)

project(multiconf VERSION 0.1)
#set(CMAKE_C_FLAGS "Wall Wextra Werror pedantic g")


add_executable(multiconf "")

#include dir
target_include_directories(multiconf PRIVATE "${CMAKE_SOURCE_DIR}/inc/")

#source file
set(SOURCE_FILES parser.cpp input.cpp rules.cpp main.cpp)
list(TRANSFORM SOURCE_FILES PREPEND "src/")
target_sources(multiconf PRIVATE ${SOURCE_FILES})

target_compile_options(multiconf PRIVATE -Wall -Wextra -Werror -pedantic -g -O2)


install(TARGETS multiconf)

