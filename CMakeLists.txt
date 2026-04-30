cmake_minimum_required(VERSION 3.14)
project(counter_project)

set(CMAKE_CXX_STANDARD 17)

# 🔥 фікс runtime
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebugDLL")

option(BUILD_TESTS "Build tests" ON)

include_directories(include)

add_library(counter STATIC src/counter.cpp)

if(BUILD_TESTS)
    include(FetchContent)

    # 🔥 критично для gtest
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/release-1.12.1.zip
    )

    FetchContent_MakeAvailable(googletest)

    enable_testing()

    add_executable(counter_tests tests/counter_test.cpp)

    target_link_libraries(counter_tests counter gtest_main)

    include(GoogleTest)
    gtest_discover_tests(counter_tests)
endif()