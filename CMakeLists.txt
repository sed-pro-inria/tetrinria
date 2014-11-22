cmake_minimum_required(VERSION 2.8)
cmake_policy(VERSION 2.8)
project(tetrinria)

set( CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Wall -Wextra" )

# TEST build type: 
#    - Add -DWITH_MOCK to C flags: replace C fonction with its mock
#    (currently, only core/game.c:getRandomTrnTetrominoType is mocked)
#    - Turn on compilation of CUnit main files are compiled
#    - Add to Makefile the rule 'make test'.
# Other build type are for example DEBUG or REALEASE.
SET(CMAKE_C_FLAGS_TEST "-DWITH_MOCK -g")

if(CMAKE_BUILD_TYPE MATCHES TEST)
    enable_testing()
endif(CMAKE_BUILD_TYPE MATCHES TEST)

set(TETRINRIA_CORE_LIBRARY tetrinria_core)
set(TETRINRIA_CORE_INCLUDE ${CMAKE_SOURCE_DIR}/core)

set(TETRINRIA_GTK_LIBRARY tetrinria_gtk)
set(TETRINRIA_GTK_INCLUDE ${CMAKE_SOURCE_DIR}/gtk)

add_subdirectory(core)
add_subdirectory(gtk)
