
cmake_minimum_required(VERSION 3.20)

project(shell++
    VERSION 1.0
    LANGUAGES CXX

)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(shell++
    src/main.cpp
    src/Shell.cpp
)

target_include_directories(shell++ PRIVATE include)