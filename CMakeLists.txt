cmake_minimum_required(VERSION 3.5)
project(naive_c_compiler)

option(DEBUG                    "Enable Debug mode build"               OFF)
option(RELEASE                  "Enable Release mode build"             OFF)

# Base compilation flags.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -std=c++11 -Wall -Werror -Wextra")

# Build modes:
if(DEBUG)
    message("*** Building in DEBUG mode ... ***")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -march=native -fno-omit-frame-pointer")
elseif(RELEASE)
    message("*** Building in RELEASE mode ... ***")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -DNDEBUG")
endif()

file(GLOB HEADERS "include/*.h")
file(GLOB SOURCES "src/*.cpp")

add_executable(naive_c_compiler src/main.cpp ${HEADERS} ${SOURCES})
target_include_directories(naive_c_compiler PRIVATE include)
