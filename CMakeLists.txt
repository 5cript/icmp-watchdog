# Version check
cmake_minimum_required (VERSION 3.0)

# Project
project(icmp-scan)

# Add files
file(GLOB sources "*.cpp")

# Set static
SET(CMAKE_EXE_LINKER_FLAGS "-static")

# Add executable
add_executable(icmp-scan ${sources})

# Compiler Options
target_compile_options(icmp-scan PRIVATE -fexceptions -std=c++14 -O2 -Wall -pedantic-errors -pedantic)

# Linker Options
target_link_libraries(icmp-scan PRIVATE ws2_32 iphlpapi)
