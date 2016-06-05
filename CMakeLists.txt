# Version check
cmake_minimum_required (VERSION 3.0)

# Project
project(icmp-watchdog)

# Add files
file(GLOB sources "*.cpp")

# Set static
SET(CMAKE_EXE_LINKER_FLAGS "-static")

# Add executable
add_executable(icmp-watchdog ${sources})

# Compiler Options
target_compile_options(icmp-watchdog PRIVATE -fexceptions -std=c++14 -O2 -Wall -pedantic-errors -pedantic)

# Linker Options
target_link_libraries(icmp-watchdog PRIVATE ws2_32 iphlpapi)
