find_package(GTK2 2.6 REQUIRED gtk)
include_directories(
    ${GTK2_INCLUDE_DIRS}
    ${TETRIS_CORE_INCLUDE}
    ${TETRIS_GTK_INCLUDE}
)

#add_library(${TETRIS_GTK_LIBRARY} SHARED
#)
add_executable(tetris-gtk tetris-gtk.c gui.c window.c)
target_link_libraries(tetris-gtk 
    ${TETRIS_CORE_LIBRARY}
    #${TETRIS_GTK_LIBRARY}
    ${GTK2_LIBRARIES}
)

if(CMAKE_BUILD_TYPE MATCHES TEST)
    add_subdirectory(test)
endif(CMAKE_BUILD_TYPE MATCHES TEST)

