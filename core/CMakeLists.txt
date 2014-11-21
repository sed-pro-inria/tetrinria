include_directories(${TETRIS_CORE_INCLUDE})

add_library(${TETRIS_CORE_LIBRARY} SHARED
    rgb_color.c
    piece.c
    tetromino.c
    tetromino_srs.c
    positionInGrid.c
    grid.c
    game.c
)

if(CMAKE_BUILD_TYPE MATCHES TEST)
    add_subdirectory(test)
endif(CMAKE_BUILD_TYPE MATCHES TEST)
