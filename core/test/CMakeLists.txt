add_executable(test_tetris_core test_tetris_core.c)
target_link_libraries(test_tetris_core ${TETRIS_CORE_LIBRARY} cunit)

add_test(test_tetris_core ${EXECUTABLE_OUTPUT_PATH}/test_tetris_core)
