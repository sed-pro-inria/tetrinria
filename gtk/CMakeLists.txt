find_package(GTK2 2.6 REQUIRED gtk)

include_directories(
    ${GTK2_INCLUDE_DIRS}
    ${TETRINRIA_CORE_INCLUDE}
)
add_executable(tetrinria-gtk tetrinria-gtk.c gui.c window.c)

target_link_libraries(tetrinria-gtk 
    ${TETRINRIA_CORE_LIBRARY}
    ${GTK2_LIBRARIES}
)
