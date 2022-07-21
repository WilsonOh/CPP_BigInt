cmake_minimum_required(VERSION 3.23.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(ENABLE_TESTING "Enable Tests" OFF)

project(bigint VERSION 1.0.0 LANGUAGES CXX)

add_library(${PROJECT_NAME} BigInt.cpp BigInt.hpp)

if (ENABLE_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Wshadow -g)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})
