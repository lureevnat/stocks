project(stocks)
cmake_minimum_required(VERSION 3.10)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)

# Specify the source files
set(SOURCES src/main.cc src/exchange.cc src/stock.cc src/agent.cc)

# Add the executable
add_executable(stocks ${SOURCES})

# Include specific compile options
target_compile_options(stocks PRIVATE -Wall -Wextra)

# Include directories
target_include_directories(stocks PRIVATE src include)