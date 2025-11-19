cmake_minimum_required(VERSION 3.10)
project(studentu_rusiavimas)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-O1")

file(GLOB SOURCES "src/*.cpp")

add_executable(studentu_rusiavimas ${SOURCES})

target_include_directories(studentu_rusiavimas PRIVATE src)
