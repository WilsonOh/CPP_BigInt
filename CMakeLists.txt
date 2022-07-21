cmake_minimum_required(VERSION 3.23.2)

enable_testing()

set(CMAKE_CXX_STANDARD 20)

project(bigint VERSION 1.0.0 LANGUAGES CXX)

add_library(${PROJECT_NAME} BigInt.cpp BigInt.hpp)

add_subdirectory(tests)

# add_executable(${PROJECT_NAME} BigInt.cpp BigInt.hpp main.cpp)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Wshadow -g) # -fsanitize=bounds -fsanitize=leak -fsanitize=address)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

add_custom_command(
  TARGET ${PROJECT_NAME}
  COMMENT "Run Tests"
  POST_BUILD
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> --output-on-failures
)
