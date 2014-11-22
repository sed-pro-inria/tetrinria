#ifndef TRN_GRID_H
#define TRN_GRID_H

#include <stdbool.h>

#include "tetromino.h"
#include "piece.h"

typedef struct grid {
    TrnTetrominoType** tetrominoTypes;
    unsigned int numberOfRows;
    unsigned int numberOfColumns;
} TrnGrid;

TrnGrid* trn_grid_new(unsigned int numberOfRows, unsigned int numberOfColumns);
void trn_grid_destroy(TrnGrid* grid);

void trn_grid_clear(TrnGrid* grid);
void trn_grid_set_cell(TrnGrid* grid, TrnPositionInGrid pos, TrnTetrominoType type);
TrnTetrominoType trn_grid_get_cell(TrnGrid* grid, TrnPositionInGrid pos);
void trn_grid_set_cells_with_piece(TrnGrid* grid, TrnPiece* piece, TrnTetrominoType type);

bool trn_grid_cell_is_in_grid(TrnGrid* grid, TrnPositionInGrid pos);

bool trn_grid_cell_is_in_grid_and_is_void(TrnGrid* grid, TrnPositionInGrid pos);
bool trn_grid_can_set_cells_with_piece(TrnGrid* grid, TrnPiece* piece);

bool trn_grid_equal(TrnGrid const * const left, TrnGrid const * const right);

void trn_grid_print(TrnGrid const * const grid);

bool trn_grid_is_row_complete(TrnGrid const * const grid, int rowIndex);

void trn_grid_copy_row_bellow(TrnGrid* grid, int rowIndex);

void trn_grid_pop_row_and_make_above_fall(TrnGrid* grid, int rowIndexToPop);

size_t trn_grid_pop_first_complete_rows_block();

int tnr_grid_find_last_complete_row_index(TrnGrid* grid);

void trn_grid_clear_row(TrnGrid* grid, int rowIndex);

#endif
