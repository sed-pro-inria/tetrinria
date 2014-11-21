add_executable(test_tetrinria_core test_tetrinria_core.c)
target_link_libraries(test_tetrinria_core ${TETRINRIA_CORE_LIBRARY} cunit)

add_test(test_tetrinria_core ${EXECUTABLE_OUTPUT_PATH}/test_tetrinria_core)
