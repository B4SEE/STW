cmake_minimum_required(VERSION 3.10)

# Set the project name
project(STW)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the library
add_library(matrix_operations SHARED lab3/matrix_operations.cpp)
target_compile_definitions(matrix_operations PRIVATE MATRIXOPERATIONS_EXPORTS)

# Add the executable
add_executable(STW_lab1 lab1/main.cpp)

add_executable(STW_lab2 lab2/main.cpp)
add_executable(child1 lab2/child1.cpp)
add_executable(child2 lab2/child2.cpp)

add_executable(STW_lab3 lab3/main.cpp)
target_link_libraries(STW_lab3 PRIVATE matrix_operations)