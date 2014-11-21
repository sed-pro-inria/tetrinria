find_package(GTK2 2.6 REQUIRED gtk)
include_directories(
    ${GTK2_INCLUDE_DIRS}
    ${TETRINRIA_CORE_INCLUDE}
    ${TETRINRIA_GTK_INCLUDE}
)

#add_library(${TETRINRIA_GTK_LIBRARY} SHARED
#)
add_executable(tetrinria-gtk tetrinria-gtk.c gui.c window.c)
target_link_libraries(tetrinria-gtk 
    ${TETRINRIA_CORE_LIBRARY}
    #${TETRINRIA_GTK_LIBRARY}
    ${GTK2_LIBRARIES}
)

if(CMAKE_BUILD_TYPE MATCHES TEST)
    add_subdirectory(test)
endif(CMAKE_BUILD_TYPE MATCHES TEST)

