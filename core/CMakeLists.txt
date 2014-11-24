include_directories(${TETRINRIA_CORE_INCLUDE})

add_library(${TETRINRIA_CORE_LIBRARY} SHARED
    color.c
    piece.c
    tetromino.c
    position_in_grid.c
    grid.c
    game.c
    init.c
)
