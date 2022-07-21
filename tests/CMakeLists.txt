add_executable(tests bigint_test.cpp)
add_executable(main main.cpp)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

FetchContent_MakeAvailable(googletest)
target_link_libraries(tests GTest::gtest_main bigint)
target_link_libraries(main bigint)
include(GoogleTest)
gtest_discover_tests(tests)
