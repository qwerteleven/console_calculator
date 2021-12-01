cmake_minimum_required(VERSION 2.8)

project(mat_lib C CXX)


#message(STATUS "libraries:")
#
#message(STATUS "  'mat_lib' will be generated")

## mat_lib library 

add_library(
  mat_lib
  matrix.hpp 
)

set_target_properties(mat_lib PROPERTIES LINKER_LANGUAGE CXX)

message(STATUS "targets:")
# testing_mat_lib 

message(STATUS "  'testing_mat_lib' will be generated")

add_executable(
  testing_mat_lib 
  testing_mat_lib.cpp
)

