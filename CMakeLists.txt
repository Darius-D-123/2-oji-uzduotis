cmake_minimum_required(VERSION 3.14)
project(studentu_rusiavimas)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1")

include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.11.0
)
FetchContent_MakeAvailable(Catch2)

file(GLOB CORE_SOURCES CONFIGURE_DEPENDS "src/*.cpp")

list(REMOVE_ITEM CORE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

add_library(core ${CORE_SOURCES})
target_include_directories(core PUBLIC src)

add_executable(studentu_rusiavimas src/main.cpp)
target_link_libraries(studentu_rusiavimas PRIVATE core)

add_executable(tests testavimai/testai_studentas.cpp)
target_link_libraries(tests PRIVATE core Catch2::Catch2WithMain)

