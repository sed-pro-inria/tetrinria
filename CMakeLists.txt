cmake_minimum_required(VERSION 2.8)
cmake_policy(VERSION 2.8)
project(tetrinria)

set( CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Wall -Wextra" )

# TEST build type: 
#    - Add -DWITH_MOCK to C flags: replace C fonction with its mock
#    (currently, only core/game.c:getRandomTrnTetrominoType is mocked)
#    - Turn on compilation of CUnit main files are compiled
# Other build type are for example DEBUG or REALEASE.
SET(CMAKE_C_FLAGS_TEST "-DWITH_MOCK -g")

enable_testing()

set(TETRINRIA_CORE_LIBRARY tetrinria_core)
set(TETRINRIA_CORE_INCLUDE ${CMAKE_SOURCE_DIR}/core)

add_subdirectory(core)
add_subdirectory(gtk)
add_subdirectory(kwstyle)
