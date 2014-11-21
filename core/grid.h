#ifndef TRN_GRID_H
#define TRN_GRID_H

#include <stdbool.h>

#include "tetromino.h"
#include "piece.h"

typedef struct grid {
    TetrominoType** tetrominoTypes;
    unsigned int numberOfRows;
    unsigned int numberOfColumns;
} Grid;

Grid* tetris_grid_new(unsigned int numberOfRows, unsigned int numberOfColumns);
void tetris_grid_destroy(Grid* grid);

void tetris_grid_clear(Grid* grid);
void tetris_grid_set_cell(Grid* grid, PositionInGrid pos, TetrominoType type);
TetrominoType tetris_grid_get_cell(Grid* grid, PositionInGrid pos);
void tetris_grid_setCellsWithPiece(Grid* grid, Piece* piece, TetrominoType type);

bool tetris_grid_cellIsInGrid(Grid* grid, PositionInGrid pos);

bool tetris_grid_cellIsInGridAndIsVoid(Grid* grid, PositionInGrid pos);
bool tetris_grid_canSetCellsWithPiece(Grid* grid, Piece* piece);

bool tetris_grid_sameGrids(Grid const * const left, Grid const * const right);

void tetris_grid_print(Grid const * const grid);

bool tetris_is_last_row_complete(Grid const * const grid);

#endif
