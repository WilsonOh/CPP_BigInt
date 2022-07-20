cmake_minimum_required(VERSION 3.23.2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(bigint VERSION 1.0.0 LANGUAGES CXX)

add_executable(${PROJECT_NAME} BigInt.cpp BigInt.hpp main.cpp)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Wshadow -g) # -fsanitize=bounds -fsanitize=leak -fsanitize=address)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})
