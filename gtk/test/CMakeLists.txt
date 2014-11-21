add_executable(test_tetrinria_gtk test_tetrinria_gtk.c)
target_link_libraries(test_tetrinria_gtk 
    ${TETRINRIA_CORE_LIBRARY}
    #${TETRINRIA_GTK_LIBRARY}
    cunit
)

add_test(test_tetrinria_gtk ${EXECUTABLE_OUTPUT_PATH}/test_tetrinria_gtk)
