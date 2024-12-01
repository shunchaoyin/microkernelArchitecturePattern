cmake_minimum_required(VERSION 3.20)

project(architecture)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

include_directories(Signal)
include_directories(Plugin)

# Add executables
add_executable(signal Signal/signal.hpp Signal/signal_test.cpp)
add_executable(signalEx Signal/signal_enhance_test.cpp Signal/signal_enhance.hpp)

# Add MyPlugin shared library
add_library(MyPlugin SHARED Plugin/MyPlugin.cpp)
add_library(HerPlugin SHARED Plugin/HerPlugin.cpp)

# Add main executable
add_executable(main_exec Plugin/Core/main.cpp Plugin/Core/Core.cpp Plugin/Plugin.cpp)

# Link MyPlugin to main_exec
target_link_libraries(main_exec MyPlugin)

# Set the output directories for MyPlugin
set_target_properties(MyPlugin PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)