cmake_minimum_required(VERSION 3.10)

project(TTable VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.76.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")

#add_executable(progname file1.cxx file2.cxx)
if(Boost_FOUND)
else()
    MESSAGE(FATAL_ERROR "cannot find boost")
endif()

add_subdirectory(ttable)
add_subdirectory(tests)
add_subdirectory(external)
add_subdirectory(benchmark)
