cmake_minimum_required(VERSION 3.20)

project(architecture)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

include_directories(Signal)

add_executable(signal Signal/signal.hpp Signal/signal_test.cpp)
add_executable(signalEx Signal/signal_enhance_test.cpp Signal/signal_enhance.hpp)


