cmake_minimum_required(VERSION 2.8)
cmake_policy(VERSION 2.8)
project(tetrinria)

set( CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Wall -Wextra" )

set(TETRINRIA_CORE_LIBRARY tetrinria_core)
set(TETRINRIA_CORE_INCLUDE ${CMAKE_SOURCE_DIR}/core)

add_subdirectory(core)
add_subdirectory(gtk)
