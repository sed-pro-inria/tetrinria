cmake_minimum_required(VERSION 2.8)
cmake_policy(VERSION 2.8)
project(tetris)

set( CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Wall -Wextra" )

# TEST build type: 
#    - Add -DWITH_MOCK to C flags: replace C fonction with its mock
#    (currently, only core/game.c:getRandomTetrominoType is mocked)
#    - Turn on compilation of CUnit main files are compiled
#    - Add to Makefile the rule 'make test'.
# Other build type are for example DEBUG or REALEASE.
SET(CMAKE_C_FLAGS_TEST "-DWITH_MOCK")

if(CMAKE_BUILD_TYPE MATCHES TEST)
    enable_testing()
endif(CMAKE_BUILD_TYPE MATCHES TEST)

set(TETRIS_CORE_LIBRARY tetris_core)
set(TETRIS_CORE_INCLUDE ${CMAKE_SOURCE_DIR}/core)

set(TETRIS_GTK_LIBRARY tetris_gtk)
set(TETRIS_GTK_INCLUDE ${CMAKE_SOURCE_DIR}/gtk)

add_subdirectory(core)
add_subdirectory(gtk)
