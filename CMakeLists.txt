cmake_minimum_required(VERSION 3.17)
project(clang_astmatcher_play LANGUAGES CXX)

# Find CMake file for Clang and GTest
find_package(Clang REQUIRED)
find_package(GTest REQUIRED)

# Add path to LLVM modules
set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  "${LLVM_CMAKE_DIR}"
)

# import LLVM CMake functions
include(AddLLVM)

include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${CLANG_INCLUDE_DIRS})
include_directories(${GTEST_INCLUDE_DIRS})

add_definitions(${LLVM_DEFINITIONS})
add_definitions(${CLANG_DEFINITIONS})

enable_testing()

add_llvm_executable(myTool main.cpp)
set_property(TARGET myTool PROPERTY CXX_STANDARD 17)

include(GoogleTest)
target_link_libraries(myTool 
                      PRIVATE clangTooling
                      PRIVATE GTest::gtest_main)
gtest_discover_tests(myTool)

