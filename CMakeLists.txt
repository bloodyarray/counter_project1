cmake_minimum_required(VERSION 3.14)
project(counter_project)

set(CMAKE_CXX_STANDARD 17)

# runtime для MSVC
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebugDLL")

option(BUILD_TESTS "Build tests" ON)
option(BUILD_SHARED_LIBS "Build shared libs" OFF)

include_directories(include)

# 🔥 бібліотека
add_library(counter src/counter.cpp)

# 🔥 ВАЖЛИВО: щоб counter.cpp бачив тестовий хук
target_compile_definitions(counter PRIVATE BUILD_TESTS)

if(BUILD_TESTS)
    include(FetchContent)

    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/release-1.12.1.zip
    )

    FetchContent_MakeAvailable(googletest)

    enable_testing()

    add_executable(counter_tests tests/counter_test.cpp)

    target_link_libraries(counter_tests counter gtest_main)

    # 🔥 для тестів теж
    target_compile_definitions(counter_tests PRIVATE BUILD_TESTS)

    include(GoogleTest)
    gtest_discover_tests(counter_tests)
endif()